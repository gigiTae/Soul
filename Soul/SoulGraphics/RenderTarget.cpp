#include "SoulGraphicsPCH.h"
#include "RenderTarget.h"
#include "Helper.h"
#include "Device.h"

SoulGraphics::RenderTarget::RenderTarget()
	:_renderTargetViews{}
	, _device()
{}

SoulGraphics::RenderTarget::~RenderTarget()
{}

void SoulGraphics::RenderTarget::Initialize(const std::shared_ptr<Device>& device, UINT width, UINT height)
{
	_device = device;

	ID3D11Texture2D* backBufferTexture = nullptr;

	auto swapChain = device->GetSwapChain();
	auto dxDevice = device->GetDevice();
	auto dxDeviceContext = device->GetDeviceContext();

	HR_T(swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBufferTexture));
	HR_T(dxDevice->CreateRenderTargetView(backBufferTexture, NULL,
		&_renderTargetViews[static_cast<int>(Type::Default)]));  // �ؽ�ó�� ���� ���� ����
	SAFE_RELEASE(backBufferTexture);	//�ܺ� 

#if USE_FLIPMODE==0
	//	// ���� Ÿ���� ���� ��� ���������ο� ���ε��մϴ�.
	//	// FlipMode�� �ƴҶ��� ���� �ѹ��� �����ϸ� �ȴ�.
	dxDeviceContext->OMSetRenderTargets(1, &_renderTargetViews[static_cast<int>(Type::Default)], NULL);
#endif

}

void SoulGraphics::RenderTarget::ClearRenderTargetView(Type type)
{
	constexpr DirectX::SimpleMath::Color color{ 0.2f,0.4f,0.2f,1.f };

	_device->GetDeviceContext()->ClearRenderTargetView(_renderTargetViews[(size_t)type], color);
}

void SoulGraphics::RenderTarget::SetRenderTargetView(Type type)
{
	_device->GetDeviceContext()->OMSetRenderTargets(1, &_renderTargetViews[static_cast<int>(type)], NULL);
}

