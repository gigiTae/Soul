#include "SoulGraphicsPCH.h"
#include "GeometryBuffer.h"
#include "ResourceManager.h"
#include "Device.h"

SoulGraphics::GeometryBuffer::GeometryBuffer(ResourceManager* resMgr)
	:Resource(resMgr)
	, _meshSize(0)
	, _vertexType(Vertex::Type::MeshVertex)
	, _vertexSizes{}
	, _indexSizes{}
	, _vertexBuffers{}
	, _indexBuffers{}
	,_vertexBufferStride{}
	,_vertexBufferOffset(0)
{

}

SoulGraphics::GeometryBuffer::~GeometryBuffer()
{}

void SoulGraphics::GeometryBuffer::Load(const aiScene* scene, Vertex::Type type)
{
	_vertexType = type;

	_meshSize = scene->mNumMeshes;

	ProcessNode(scene->mRootNode, scene);
}


void SoulGraphics::GeometryBuffer::BindVertexAndIndexBuffer(size_t index)
{
	auto deviceContext = GetResourceManager()->GetDevice()->GetDeviceContext();

	deviceContext->IASetIndexBuffer(_indexBuffers[index], DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetVertexBuffers(0, 1, &_vertexBuffers[index], &_vertexBufferStride, &_vertexBufferOffset);
}

void SoulGraphics::GeometryBuffer::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (UINT i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		ProcessMesh(mesh, scene);
	}

	for (UINT i = 0; i < node->mNumChildren; i++) {
		ProcessNode(node->mChildren[i], scene);
	}
}

void SoulGraphics::GeometryBuffer::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	auto device = GetResourceManager()->GetDevice()->GetDevice();
	std::vector<UINT> indices;

	switch (_vertexType)
	{
	case SoulGraphics::Vertex::Type::PosColor:
		break;
	case SoulGraphics::Vertex::Type::PosTex:
		break;
	case SoulGraphics::Vertex::Type::PosNormal:
		break;
	case SoulGraphics::Vertex::Type::MeshVertex:
	{
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

		D3D11_BUFFER_DESC vbd;
		vbd.Usage = D3D11_USAGE_IMMUTABLE;
		vbd.ByteWidth = static_cast<UINT>(sizeof(Vertex::MeshVertex) * vertices.size());
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags = 0;
		vbd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = &vertices[0];

		ID3D11Buffer* vertexBuffer = nullptr;
		ID3D11Buffer* indexBuffer = nullptr;

		HR_T(device->CreateBuffer(&vbd, &initData, &vertexBuffer));

		D3D11_BUFFER_DESC ibd;
		ibd.Usage = D3D11_USAGE_IMMUTABLE;
		ibd.ByteWidth = static_cast<UINT>(sizeof(UINT) * indices.size());
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.CPUAccessFlags = 0;
		ibd.MiscFlags = 0;

		initData.pSysMem = &indices[0];

		HR_T(device->CreateBuffer(&ibd, &initData, &indexBuffer));

		_vertexBufferStride = sizeof(Vertex::MeshVertex);
		_vertexSizes.push_back(vertices.size());
		_indexSizes.push_back(indices.size());
		_vertexBuffers.push_back(vertexBuffer);
		_indexBuffers.push_back(indexBuffer);
	}
	break;
	case SoulGraphics::Vertex::Type::SkinnedVertex:
	{
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


		D3D11_BUFFER_DESC vbd;
		vbd.Usage = D3D11_USAGE_IMMUTABLE;
		vbd.ByteWidth = static_cast<UINT>(sizeof(Vertex::SkinnedVertex) * vertices.size());
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags = 0;
		vbd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = &vertices[0];

		ID3D11Buffer* vertexBuffer = nullptr;
		ID3D11Buffer* indexBuffer = nullptr;

		HR_T(device->CreateBuffer(&vbd, &initData, &vertexBuffer));

		D3D11_BUFFER_DESC ibd;
		ibd.Usage = D3D11_USAGE_IMMUTABLE;
		ibd.ByteWidth = static_cast<UINT>(sizeof(UINT) * indices.size());
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.CPUAccessFlags = 0;
		ibd.MiscFlags = 0;

		initData.pSysMem = &indices[0];

		HR_T(device->CreateBuffer(&ibd, &initData, &indexBuffer));

		_vertexBufferStride = sizeof(Vertex::MeshVertex);
		_vertexSizes.push_back(vertices.size());
		_indexSizes.push_back(indices.size());
		_vertexBuffers.push_back(vertexBuffer);
		_indexBuffers.push_back(indexBuffer);
	}
		break;
	default:
		break;
	}


}

