#include "SoulGraphicsPCH.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Device.h"


SoulGraphics::Texture::Texture(ResourceManager* resMgr)
	: Resource(resMgr)
	, _shaderResourceView(nullptr)
{}

SoulGraphics::Texture::~Texture()
{
	SAFE_RELEASE(_shaderResourceView);
}

void SoulGraphics::Texture::LoadTexture(const std::filesystem::path& path)
{
	assert(_shaderResourceView == nullptr);

	auto extension = path.extension();

	auto device = GetResourceManager()->GetDevice()->GetDevice();
	auto deviceContext = GetResourceManager()->GetDevice()->GetDeviceContext();

	if (extension == ".dds")
	{
		HR_T(DirectX::CreateDDSTextureFromFile(device
			, path.c_str()
			, nullptr
			, &_shaderResourceView));
	}
	else 
	{
		HR_T(DirectX::CreateWICTextureFromFile(device,
			deviceContext,
			path.c_str(),
			nullptr, &_shaderResourceView));
	}
}

void SoulGraphics::Texture::SetTexture(UINT slot)
{
	auto deviceContext = GetResourceManager()->GetDevice()->GetDeviceContext();

	deviceContext->PSSetShaderResources(slot, 1, &_shaderResourceView);
}

