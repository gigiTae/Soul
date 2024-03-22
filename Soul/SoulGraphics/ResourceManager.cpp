#include "SoulGraphicsPCH.h"
#include "ResourceManager.h"

#include "Texture.h"
#include "Shader.h"
#include "GeometryBuffer.h"
#include "ConstantBuffer.h"
#include "AnimaitonClip.h"
#include "ResourceLoader.h"

SoulGraphics::ResourceManager::ResourceManager()
	:_device(nullptr)
	, _loader(nullptr)
	, _shaderMap{}
	, _textureMap{}
	, _constantBuffer{}
{}

SoulGraphics::ResourceManager::~ResourceManager()
{}

void SoulGraphics::ResourceManager::Initialize(const std::shared_ptr<Device>& device)
{
	_device = device;
	_loader = std::make_unique<ResourceLoader>();
	_constantBuffer = std::make_shared<ConstantBuffer>(this);

	_loader->Initialize(this, _device);
	_constantBuffer->Initialize();
}

void SoulGraphics::ResourceManager::Finalize()
{
	_textureMap.clear();
	_shaderMap.clear();
}

std::shared_ptr<SoulGraphics::Texture> SoulGraphics::ResourceManager::LoadTexture(const std::wstring& path)
{
	// 중복 리소스 로드 방지
	if (auto iter = _textureMap.find(path); iter != _textureMap.end())
	{
		return iter->second;
	}

	auto texture = _loader->LoadTexture(path);
	_textureMap.insert({ path, texture });

	return texture;
}

std::shared_ptr<SoulGraphics::GeometryBuffer> SoulGraphics::ResourceManager::LoadFBX(const std::wstring& path, Vertex::Type type)
{
	if (auto iter = _geometryMap.find(path); iter != _geometryMap.end())
	{
		return iter->second;
	}

	std::filesystem::path fbxPath = path;
	assert(std::filesystem::exists(fbxPath));

	auto iter = _geometryMap.find(path);

	auto buffer = _loader->LoadGeometryBuffer(path, type);

	return buffer;
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
