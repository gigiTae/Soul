#include "SoulGraphicsPCH.h"
#include "ResourceLoader.h"
#include "ResourceManager.h"
#include "Device.h"

SoulGraphics::ResourceLoader::ResourceLoader()
	:_device(nullptr)
{}

void SoulGraphics::ResourceLoader::Initialize(ResourceManager* resMgr, std::shared_ptr<Device> device)
{
	_resourceManager = resMgr;
	_device = device;
}

std::shared_ptr<SoulGraphics::Texture> SoulGraphics::ResourceLoader::LoadTexture(const std::wstring path)
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
}
