#include "SoulGraphicsPCH.h"
#include "ResourceManager.h"

#include "Texture.h"
#include "Shader.h"
#include "GeometryBuffer.h"
#include "ConstantBuffer.h"
#include "AnimaitonClip.h"
#include "ResourceLoader.h"
#include "Animator.h"

SoulGraphics::ResourceManager::ResourceManager()
	:_device(nullptr)
	, _loader(nullptr)
	, _shaderMap{}
	, _textureMap{}
	, _constantBuffer{}
	,_impoter(nullptr)
{}

SoulGraphics::ResourceManager::~ResourceManager()
{}

void SoulGraphics::ResourceManager::Initialize(const std::shared_ptr<Device>& device)
{
	_device = device;
	_impoter = std::make_unique<Assimp::Importer>();
	_loader = std::make_unique<ResourceLoader>();
	_constantBuffer = std::make_shared<ConstantBuffer>(this);

	_loader->Initialize(this, _device);
	_constantBuffer->Initialize();
}

void SoulGraphics::ResourceManager::Finalize()
{
	_textureMap.clear();
	_shaderMap.clear();
	_geometryMap.clear();
	_animationClipMap.clear();
}

std::shared_ptr<SoulGraphics::Texture> SoulGraphics::ResourceManager::LoadTexture(const std::wstring& path)
{
	// �ߺ� ���ҽ� �ε� ����
	if (auto iter = _textureMap.find(path); iter != _textureMap.end())
	{
		return iter->second;
	}

	auto texture = _loader->LoadTexture(path);
	_textureMap.insert({ path, texture });

	return texture;
}

std::shared_ptr<SoulGraphics::GeometryBuffer> SoulGraphics::ResourceManager::LoadGeometryBuffer(const std::wstring& path, Vertex::Type type)
{
	if (auto iter = _geometryMap.find(path); iter != _geometryMap.end())
	{
		return iter->second;
	}

	std::filesystem::path fbxPath = path;
	assert(std::filesystem::exists(fbxPath));

	const aiScene* scene = _impoter->ReadFile(fbxPath.string(),
		aiProcess_Triangulate |			// �ﰢ����ȯ
		aiProcess_GenUVCoords |			// UV ����
		aiProcess_GenNormals |			// �븻 ����
		aiProcess_CalcTangentSpace |	// ź��Ʈ ����
		aiProcess_LimitBoneWeights |	// ������ ����޴� ���� �ִ� ���� 4���� ����
		aiProcess_ConvertToLeftHanded); // �޼���ǥ��� ��ȯ

	assert(scene);

	auto buffer = _loader->LoadGeometryBuffer(scene, type);

	return buffer;
}


std::shared_ptr<SoulGraphics::GeometryBuffer> SoulGraphics::ResourceManager::LoadGeometryBufferAndAnimator(const std::wstring& path, Animator* animator)
{
	if (auto iter = _geometryMap.find(path); iter != _geometryMap.end())
	{
		return iter->second;
	}

	std::filesystem::path fbxPath = path;
	assert(std::filesystem::exists(fbxPath));

	const aiScene* scene = _impoter->ReadFile(fbxPath.string(),
		aiProcess_Triangulate |			// �ﰢ����ȯ
		aiProcess_GenUVCoords |			// UV ����
		aiProcess_GenNormals |			// �븻 ����
		aiProcess_CalcTangentSpace |	// ź��Ʈ ����
		aiProcess_LimitBoneWeights |	// ������ ����޴� ���� �ִ� ���� 4���� ����
		aiProcess_ConvertToLeftHanded); // �޼���ǥ��� ��ȯ

	assert(scene);

	std::map<std::string, int> boneMapping;

	auto buffer = _loader->LoadGeometryBufferAndAnimator(scene,animator);

	return buffer;
}

std::shared_ptr<SoulGraphics::AnimaitonClip> SoulGraphics::ResourceManager::LoadAnimationClip(const std::wstring& path)
{
	if (auto iter = _animationClipMap.find(path); iter != _animationClipMap.end())
	{
		return iter->second;
	}

	std::filesystem::path fbxPath = path;
	assert(std::filesystem::exists(fbxPath));

	return nullptr;
}

std::shared_ptr<SoulGraphics::Shader> SoulGraphics::ResourceManager::LoadShader(const std::wstring& vs
	, const std::wstring& ps
	, const D3D11_INPUT_ELEMENT_DESC* desc
	, UINT descSize)
{
	if (auto iter = _shaderMap.find(vs); iter != _shaderMap.end())
	{
		return iter->second;
	}

	auto shader = _loader->LoadShader(vs, ps, desc, descSize);
	_shaderMap.insert({ vs, shader });

	return shader;
}
