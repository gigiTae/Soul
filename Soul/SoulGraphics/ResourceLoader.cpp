#include "SoulGraphicsPCH.h"
#include "ResourceLoader.h"
#include "ResourceManager.h"
#include "Device.h"
#include "Texture.h"
#include "Shader.h"
#include "Animator.h"
#include "AnimaitonClip.h"
#include "GeometryBuffer.h"

SoulGraphics::ResourceLoader::ResourceLoader()
	:_device(nullptr), _resourceManager(nullptr)
{}

void SoulGraphics::ResourceLoader::Initialize(ResourceManager* resMgr, std::shared_ptr<Device> device)
{
	_resourceManager = resMgr;
	_device = device;
}

std::shared_ptr<SoulGraphics::Texture> SoulGraphics::ResourceLoader::LoadTexture(const std::wstring& path)
{
	std::filesystem::path p(path);
	auto extension = p.extension();

	auto device = _device->GetDXDevice();
	auto deviceContext = _device->GetDXDeviceContext();

	ID3D11ShaderResourceView* shaderResourceView = nullptr;

	// 리소스 로드
	if (extension == ".dds")
	{
		HR_T(DirectX::CreateDDSTextureFromFile(device
			, path.c_str()
			, nullptr
			, &shaderResourceView));
	}
	else
	{
		HR_T(DirectX::CreateWICTextureFromFile(device,
			deviceContext,
			path.c_str(),
			nullptr, &shaderResourceView));
	}

	return std::make_shared<Texture>(_resourceManager, shaderResourceView);
}

std::shared_ptr<SoulGraphics::Shader> SoulGraphics::ResourceLoader::LoadShader(const std::wstring& vs
	, const std::wstring& ps
	, const D3D11_INPUT_ELEMENT_DESC* desc
	, UINT descSize)
{
	auto dxDevice = _device->GetDXDevice();
	auto dxDeviceContext = _device->GetDXDeviceContext();

	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11InputLayout* inputLayout;

	ID3D10Blob* vertexShaderBuffer = nullptr;	// 정점 셰이더 코드가 저장될 버퍼.
	HR_T(CompileShaderFromFile(vs.c_str(), "main", "vs_5_0", &vertexShaderBuffer));

	// InputLayout 생성
	HR_T(dxDevice->CreateInputLayout(desc, descSize,
		vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &inputLayout));

	// VS생성
	HR_T(dxDevice->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(), NULL, &vertexShader));

	SAFE_RELEASE(vertexShaderBuffer);

	// PS생성
	ID3D10Blob* pixelShaderBuffer = nullptr;	// 픽셀 셰이더 코드가 저장될 버퍼.
	HR_T(CompileShaderFromFile(ps.c_str(), "main", "ps_5_0", &pixelShaderBuffer));
	HR_T(dxDevice->CreatePixelShader(
		pixelShaderBuffer->GetBufferPointer(),
		pixelShaderBuffer->GetBufferSize(), NULL, &pixelShader));
	SAFE_RELEASE(pixelShaderBuffer);


	return std::make_shared<Shader>(_resourceManager, vertexShader, pixelShader, inputLayout);
}

std::shared_ptr<SoulGraphics::GeometryBuffer> SoulGraphics::ResourceLoader::LoadGeometryBuffer(const aiScene* scene, Vertex::Type type)
{
	auto geometryBuffer = std::make_shared<GeometryBuffer>(_resourceManager, type);

	ProcessNode(geometryBuffer.get(), scene->mRootNode, scene);

	return geometryBuffer;
}

std::shared_ptr<SoulGraphics::GeometryBuffer> SoulGraphics::ResourceLoader::LoadGeometryBufferAndAnimator(const aiScene* scene, Animator* animator)
{
	auto geometryBuffer = std::make_shared<GeometryBuffer>(_resourceManager, Vertex::Type::SkinnedVertex);

	ProcessNode(geometryBuffer.get(), scene->mRootNode, scene, animator, nullptr);

	return geometryBuffer;
}

std::shared_ptr<SoulGraphics::AnimaitonClip> SoulGraphics::ResourceLoader::LoadAnimationClip(const aiAnimation* animation, const aiScene* scene)
{
	auto clip = std::make_shared<AnimaitonClip>();

	clip->_name = animation->mName.C_Str();
	clip->_duration = static_cast<float>(animation->mDuration);
	clip->_ticksPerSecond = static_cast<float>(animation->mTicksPerSecond);

	UINT numChannels = animation->mNumChannels;
	auto& boneAnimations = clip->_boneAnimations;

	boneAnimations.resize(numChannels);

	for (UINT i = 0; i < numChannels; ++i)
	{
		auto& boneAnimation = boneAnimations[i];
		const auto* aniNode = animation->mChannels[i];

		boneAnimation.boneName = aniNode->mNodeName.C_Str();

		UINT numKeys = aniNode->mNumPositionKeys;

		boneAnimation.bonePoses.resize(numKeys);

		for (UINT j = 0; j < numKeys; j++)
		{
			const auto& pos = aniNode->mPositionKeys[j].mValue;
			const auto& rot = aniNode->mRotationKeys[j].mValue;
			const auto& scale = aniNode->mScalingKeys[j].mValue;

			boneAnimation.bonePoses[j].position = SM::Vector3{ pos.x, pos.y, pos.z };
			boneAnimation.bonePoses[j].rotation = SM::Quaternion{ rot.x,rot.y,rot.z,rot.w };
			boneAnimation.bonePoses[j].scale = SM::Vector3{ scale.x,scale.y,scale.z };

			auto transM = SM::Matrix::CreateTranslation(boneAnimation.bonePoses[j].position);
			auto rotM = SM::Matrix::CreateFromQuaternion(boneAnimation.bonePoses[j].rotation);
			auto scaleM = SM::Matrix::CreateScale(boneAnimation.bonePoses[j].scale);
			
			boneAnimation.bonePoses[j].transformation = scaleM * rotM *transM;
		}
	}

	return clip;
}


void SoulGraphics::ResourceLoader::ProcessNode(GeometryBuffer* buffer
	, const aiNode* node
	, const aiScene* scene)
{
	for (UINT i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		ProcessMesh(buffer, mesh, scene);
	}

	for (UINT i = 0; i < node->mNumChildren; i++) {
		ProcessNode(buffer, node->mChildren[i], scene);
	}
}

void SoulGraphics::ResourceLoader::ProcessMesh(GeometryBuffer* buffer
	, const aiMesh* mesh
	, const aiScene* scene
	, Animator* animator)
{
	auto dxDevice = _device->GetDXDevice();
	std::vector<UINT> indices;
	std::vector<Vertex::SkinnedVertex> vertices;

	for (UINT i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex::SkinnedVertex v{};
		v.pos.x = mesh->mVertices[i].x;
		v.pos.y = mesh->mVertices[i].y;
		v.pos.z = mesh->mVertices[i].z;

		if (mesh->HasNormals())
		{
			v.normal.x = mesh->mNormals[i].x;
			v.normal.y = mesh->mNormals[i].y;
			v.normal.z = mesh->mNormals[i].z;
		}

		if (mesh->mTextureCoords[0])
		{
			v.tex.x = mesh->mTextureCoords[0][i].x;
			v.tex.y = mesh->mTextureCoords[0][i].y;
		}

		if (mesh->HasTangentsAndBitangents())
		{
			v.tangent.x = mesh->mTangents[i].x;
			v.tangent.y = mesh->mTangents[i].y;
			v.tangent.z = mesh->mTangents[i].z;
		}

		vertices.push_back(v);
	}

	for (UINT i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (UINT j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	UINT meshBoneCount = mesh->mNumBones;
	UINT boneIndexCounter = 0;
	animator->_skelton.bones.resize(meshBoneCount);

	std::map<std::string, UINT>& boneMapping = animator->_boneMapping;

	for (UINT i = 0; i < meshBoneCount; ++i)
	{
		aiBone* bone = mesh->mBones[i];
		std::string boneName = bone->mName.C_Str();
		UINT boneIndex = 0;
		if (boneMapping.find(boneName) == boneMapping.end())
		{
			boneIndex = boneIndexCounter;
			boneIndexCounter++;
			animator->_skelton.bones[boneIndex].inverseBindPose = SM::Matrix(&bone->mOffsetMatrix.a1).Transpose();
			animator->_skelton.bones[boneIndex].name = boneName;
			boneMapping[boneName] = boneIndex;
		}
		else boneIndex = boneMapping[boneName];

		// Vertex Bone 정보 
		for (UINT j = 0; j < bone->mNumWeights; ++j)
		{
			UINT vertexID = bone->mWeights[j].mVertexId;
			float weight = bone->mWeights[j].mWeight;
			vertices[vertexID].AddBoneDate(boneIndex, weight);
		}
	}

	buffer->CreateVertexAndIndex(vertices, indices);
}

void SoulGraphics::ResourceLoader::ProcessMesh(GeometryBuffer* buffer
	, const aiMesh* mesh
	, const aiScene* scene)
{
	auto dxDevice = _device->GetDXDevice();
	std::vector<UINT> indices;

	std::vector<Vertex::MeshVertex> vertices;

	for (UINT i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex::MeshVertex v{};
		v.pos.x = mesh->mVertices[i].x;
		v.pos.y = mesh->mVertices[i].y;
		v.pos.z = mesh->mVertices[i].z;

		if (mesh->HasNormals())
		{
			v.normal.x = mesh->mNormals[i].x;
			v.normal.y = mesh->mNormals[i].y;
			v.normal.z = mesh->mNormals[i].z;
		}

		if (mesh->mTextureCoords[0])
		{
			v.tex.x = mesh->mTextureCoords[0][i].x;
			v.tex.y = mesh->mTextureCoords[0][i].y;
		}

		if (mesh->HasTangentsAndBitangents())
		{
			v.tangent.x = mesh->mTangents[i].x;
			v.tangent.y = mesh->mTangents[i].y;
			v.tangent.z = mesh->mTangents[i].z;
		}

		vertices.push_back(v);
	}

	for (UINT i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (UINT j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	buffer->CreateVertexAndIndex(vertices, indices);
}

void SoulGraphics::ResourceLoader::ProcessNode(GeometryBuffer* buffer
	, const aiNode* node
	, const aiScene* scene
	, Animator* animator
	, Node* parent
)
{
	animator->_nodeMap.insert({ node->mName.C_Str(), {} });

	Node* childNode = &animator->_nodeMap[node->mName.C_Str()];
	childNode->parent = parent;
	childNode->worldMatrix = SM::Matrix(&node->mTransformation.a1).Transpose();
	
	childNode->name = node->mName.C_Str();

	if (parent != nullptr)
	{
		parent->children.push_back(childNode);
	}
	else
	{
		assert(!animator->_root);
		animator->_root = childNode;
	}

	for (UINT i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		ProcessMesh(buffer, mesh, scene, animator);
	}

	for (UINT i = 0; i < node->mNumChildren; i++) {
		ProcessNode(buffer, node->mChildren[i], scene, animator, childNode);
	}

}
