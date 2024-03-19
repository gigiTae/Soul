#include "SoulGraphicsPCH.h"
#include "RenderTarget.h"
#include "Device.h"

SoulGraphics::RenderTarget::RenderTarget()
	:_renderTargetViews{}
	, _device()
	, _depthStencilView(nullptr)
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
		&_renderTargetViews[static_cast<int>(RenderTargetView::First)]));  // �ؽ�ó�� ���� ���� ����
	SAFE_RELEASE(backBufferTexture);	//�ܺ� 

#if USE_FLIPMODE==0
	//	// ���� Ÿ���� ���� ��� ���������ο� ���ε��մϴ�.
	//	// FlipMode�� �ƴҶ��� ���� �ѹ��� �����ϸ� �ȴ�.
	dxDeviceContext->OMSetRenderTargets(1, &_renderTargetViews[static_cast<int>(RenderTargetView::First)], NULL);
#endif

	//4. ����Ʈ ����.	
	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = static_cast<float>(width);
	viewport.Height = static_cast<float>(height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	// ����Ʈ ����
	dxDeviceContext->RSSetViewports(1, &viewport);

	//6. �X��&���ٽ� �� ����
	D3D11_TEXTURE2D_DESC descDepth = {};
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;

	ID3D11Texture2D* textureDepthStencil = nullptr;
	HR_T(dxDevice->CreateTexture2D(&descDepth, nullptr, &textureDepthStencil));

	// �������ٽ� �� 
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	HR_T(dxDevice->CreateDepthStencilView(textureDepthStencil, &descDSV, &_depthStencilView));
	SAFE_RELEASE(textureDepthStencil);
}

void SoulGraphics::RenderTarget::Finalize()
{
	for (auto renderTarget : _renderTargetViews)
	{
		SAFE_RELEASE(renderTarget);
	}
}

void SoulGraphics::RenderTarget::Clear(RenderTargetView type)
{
	constexpr SM::Color color{ 0.f,0.25f,0.f,1.f };

	_device->GetDeviceContext()->ClearRenderTargetView(_renderTargetViews[(size_t)type], color);
	_device->GetDeviceContext()->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH, 1.f, 0.f);
}

void SoulGraphics::RenderTarget::SetRenderTargetView(RenderTargetView type)
{
	_device->GetDeviceContext()->OMSetRenderTargets(1, &_renderTargetViews[static_cast<int>(type)], _depthStencilView);
}

