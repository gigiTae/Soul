#include "SoulGraphicsPCH.h"
#include "ResourceManager.h"

#include "Texture.h"
#include "Shader.h"
#include "GeometryBuffer.h"

SoulGraphics::ResourceManager::ResourceManager()
	:_device(nullptr)
	, _impoter(std::make_unique<Assimp::Importer>())
	, _shaerMap{}
	, _textureMap{}
{}

SoulGraphics::ResourceManager::~ResourceManager()
{}

void SoulGraphics::ResourceManager::Initialize(const std::shared_ptr<Device>& device)
{
	_device = device;

}

void SoulGraphics::ResourceManager::Finalize()
{
	_textureMap.clear();
	_shaerMap.clear();
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

	return iter->second;
}
