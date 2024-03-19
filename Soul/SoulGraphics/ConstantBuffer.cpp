#include "SoulGraphicsPCH.h"
#include "ConstantBuffer.h"
#include "ConstantBufferStruct.h"
#include "ResourceManager.h"
#include "Device.h"

SoulGraphics::ConstantBuffer::ConstantBuffer(ResourceManager* resMgr)
	:Resource(resMgr),
	_constantBuffers{}
{}

SoulGraphics::ConstantBuffer::~ConstantBuffer()
{}

void SoulGraphics::ConstantBuffer::Initialize()
{
	auto resMgr = GetResourceManager();
	auto device = resMgr->GetDevice()->GetDevice();

	// Matrix Buffer
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(CB::Matrix);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	HR_T(device->CreateBuffer(&bd, nullptr, &_constantBuffers[static_cast<size_t>(Type::Matrix)]));

	// Light
	bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(CB::Light);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	HR_T(device->CreateBuffer(&bd, nullptr, &_constantBuffers[static_cast<size_t>(Type::Light)]));
}

void SoulGraphics::ConstantBuffer::SetMatrixCB(const SM::Matrix& world, const SM::Matrix& view, const SM::Matrix& proj) const
{
	auto deviceContext = GetResourceManager()->GetDevice()->GetDeviceContext();

	CB::Matrix cb;
	cb.world = DirectX::XMMatrixTranspose(world);
	cb.view = DirectX::XMMatrixTranspose(view);
	cb.projection = DirectX::XMMatrixTranspose(proj);

	deviceContext->UpdateSubresource(_constantBuffers[static_cast<size_t>(Type::Matrix)],
		0, nullptr, &cb, 0, 0);

	deviceContext->VSSetConstantBuffers(0, 1, &_constantBuffers[static_cast<size_t>(Type::Matrix)]);
}

void SoulGraphics::ConstantBuffer::Finalize()
{
	for (auto buffer : _constantBuffers)
	{
		SAFE_RELEASE(buffer);
	}
}