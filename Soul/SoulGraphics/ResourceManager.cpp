#include "SoulGraphicsPCH.h"
#include "ResourceManager.h"

#include "Texture.h"
#include "Shader.h"
#include "GeometryBuffer.h"
#include "ConstantBuffer.h"
#include "AnimaitonClip.h"

SoulGraphics::ResourceManager::ResourceManager()
	:_device(nullptr)
	, _impoter(std::make_unique<Assimp::Importer>())
	, _shaderMap{}
	, _textureMap{}
	, _constantBuffer{}
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

std::shared_ptr<SoulGraphics::GeometryBuffer> SoulGraphics::ResourceManager::LoadFBX(const std::wstring& path, Vertex::Type type)
{
	if (auto iter = _geometryMap.find(path); iter != _geometryMap.end())
	{
		return iter->second;
	}

	std::filesystem::path fbxPath = path;
	assert(std::filesystem::exists(fbxPath));

	const aiScene* scene = _impoter->ReadFile(fbxPath.string(),
		aiProcess_Triangulate |			// 삼각형변환
		aiProcess_GenUVCoords |			// UV 생성
		aiProcess_GenNormals |			// 노말 생성
		aiProcess_CalcTangentSpace |	// 탄젠트 생성
		aiProcess_LimitBoneWeights |	// 정점이 영향받는 본의 최대 개수 4개로 제한
		aiProcess_ConvertToLeftHanded); // 왼손좌표계로 변환

	assert(scene);

	_geometryMap.insert({ path, std::make_shared<GeometryBuffer>(this) });

	auto iter = _geometryMap.find(path);

	iter->second->Load(scene, type);

	return iter->second;
}

std::shared_ptr<SoulGraphics::AnimaitonClip> SoulGraphics::ResourceManager::LoadAnimation(const std::wstring& path)
{
	if (auto iter = _animationClipMap.find(path); iter != _animationClipMap.end())
	{
		return iter->second;
	}

	std::filesystem::path fbxPath = path;
	assert(std::filesystem::exists(fbxPath));

	const aiScene* scene = _impoter->ReadFile(fbxPath.string(),
		aiProcess_Triangulate |			// 삼각형변환
		aiProcess_GenUVCoords |			// UV 생성
		aiProcess_GenNormals |			// 노말 생성
		aiProcess_CalcTangentSpace |	// 탄젠트 생성
		aiProcess_LimitBoneWeights |	// 정점이 영향받는 본의 최대 개수 4개로 제한
		aiProcess_ConvertToLeftHanded); // 왼손좌표계로 변환

	assert(scene);

	_animationClipMap.insert({ path, std::make_shared<AnimaitonClip>() });

	auto iter = _animationClipMap.find(path);

	//iter->second->Load(scene);
	iter->second->LoadAnimation(scene->mAnimations[0]);

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
