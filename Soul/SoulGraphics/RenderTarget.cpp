#include "SoulGraphicsPCH.h"
#include "RenderTarget.h"
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
		&_renderTargetViews[static_cast<int>(Type::First)]));  // 텍스처는 내부 참조 증가
	SAFE_RELEASE(backBufferTexture);	//외부 

#if USE_FLIPMODE==0
	//	// 렌더 타겟을 최종 출력 파이프라인에 바인딩합니다.
	//	// FlipMode가 아닐때는 최초 한번만 설정하면 된다.
	dxDeviceContext->OMSetRenderTargets(1, &_renderTargetViews[static_cast<int>(Type::First)], NULL);
#endif

	//4. 뷰포트 설정.	
	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = static_cast<float>(width);
	viewport.Height = static_cast<float>(height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	// 뷰포트 설정.
	dxDeviceContext->RSSetViewports(1, &viewport);
}

void SoulGraphics::RenderTarget::Finalize()
{
	for (auto renderTarget : _renderTargetViews)
	{
		SAFE_RELEASE(renderTarget);
	}
}

void SoulGraphics::RenderTarget::ClearRenderTargetView(Type type)
{
	constexpr DirectX::SimpleMath::Color color{ 0.f,0.25f,0.f,1.f };

	_device->GetDeviceContext()->ClearRenderTargetView(_renderTargetViews[(size_t)type], color);
}

void SoulGraphics::RenderTarget::SetRenderTargetView(Type type)
{
	_device->GetDeviceContext()->OMSetRenderTargets(1, &_renderTargetViews[static_cast<int>(type)], NULL);
}

