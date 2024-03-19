#include "SoulGraphicsPCH.h"
#include "ResourceManager.h"

#include "Texture.h"
#include "Shader.h"
#include "GeometryBuffer.h"
#include "ConstantBuffer.h"

SoulGraphics::ResourceManager::ResourceManager()
	:_device(nullptr)
	, _impoter(std::make_unique<Assimp::Importer>())
	, _shaderMap{}
	, _textureMap{}
	,_constantBuffer{}
{}

SoulGraphics::ResourceManager::~ResourceManager()
{}

void SoulGraphics::ResourceManager::Initialize(const std::shared_ptr<Device>& device)
{
	_device = device;

	_constantBuffer = std::make_shared<ConstantBuffer>(this);
	_constantBuffer->Initialize();
}

void SoulGraphics::ResourceManager::Finalize()
{
	_textureMap.clear();
	_shaderMap.clear();
}

std::shared_ptr<SoulGraphics::Texture> SoulGraphics::ResourceManager::LoadTexture(const std::wstring& path)
{
	if (auto iter = _textureMap.find(path); iter != _textureMap.end())
	{
		return iter->second;
	}

	_textureMap.insert({ path, std::make_shared<Texture>(this) });

	auto iter = _textureMap.find(path);

	iter->second->LoadTexture(path);

	return iter->second;
}


std::shared_ptr<SoulGraphics::GeometryBuffer> SoulGraphics::ResourceManager::LoadFBX(const std::wstring& path)
{
	if (auto iter = _geometryMap.find(path); iter != _geometryMap.end())
	{
		return iter->second;
	}

	std::filesystem::path fbxPath = path;
	assert(std::filesystem::exists(fbxPath));

	const aiScene* scene = _impoter->ReadFile(fbxPath.string(),
		aiProcess_Triangulate |
		aiProcess_GenUVCoords |
		aiProcess_GenNormals |
		aiProcess_CalcTangentSpace |
		aiProcess_ConvertToLeftHanded);

	assert(scene);

	_geometryMap.insert({ path, std::make_shared<GeometryBuffer>(this) });

	auto iter = _geometryMap.find(path);

	iter->second->Load(scene, Vertex::Type::MeshVertex);

	return iter->second;
}

std::shared_ptr<SoulGraphics::Shader> SoulGraphics::ResourceManager::LoadShader(const std::wstring& vs, const std::wstring& ps)
{
	if (auto iter = _shaderMap.find(vs); iter != _shaderMap.end())
	{
		return iter->second;
	}

	_shaderMap.insert({ vs, std::make_shared<Shader>(this) });
	auto iter = _shaderMap.find(vs);

	iter->second->LoadShader(vs, ps);

	return iter->second;
}
