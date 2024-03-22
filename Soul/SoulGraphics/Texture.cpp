#include "SoulGraphicsPCH.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Device.h"

SoulGraphics::Texture::Texture(ResourceManager* resMgr, ID3D11ShaderResourceView* view)
	:Resource(resMgr),_shaderResourceView(view)
{}

SoulGraphics::Texture::~Texture()
{
	SAFE_RELEASE(_shaderResourceView);
}

void SoulGraphics::Texture::BindTexture(UINT slot)
{
	auto deviceContext = GetResourceManager()->GetDevice()->GetDXDeviceContext();

	deviceContext->PSSetShaderResources(slot, 1, &_shaderResourceView);
}

