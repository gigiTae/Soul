#include "SoulGraphicsPCH.h"
#include "GraphicsEngine.h"
#include "Helper.h"
#include "Device.h"
#include "RenderTarget.h"
#include "Camera.h"

SoulGraphics::GraphicsEngine::GraphicsEngine()
	:_device(std::make_shared<Device>())
	, _renderTarget(std::make_shared<RenderTarget>())
	, _camera(std::make_unique<Camera>())
{}

SoulGraphics::GraphicsEngine::~GraphicsEngine()
{}

void SoulGraphics::GraphicsEngine::Initialize(InitalizeInfomation info)
{
	UINT height = info.rect.right - info.rect.left;
	UINT width = info.rect.bottom - info.rect.top;

	// 결과값.
	HRESULT hr = 0;

	_device->Initialize(info.hwnd, width, height);
	_renderTarget->Initialize(_device, width, height);

}

void SoulGraphics::GraphicsEngine::Render()
{
	_renderTarget->SetRenderTargetView(RenderTarget::Type::First);
	_renderTarget->ClearRenderTargetView(RenderTarget::Type::First);


	// 스왑체인 교체.
	_device->GetSwapChain()->Present(0, 0);
}

void SoulGraphics::GraphicsEngine::Finalize()
{
	_device->Finalize();
}

ID3D11Device* SoulGraphics::GraphicsEngine::GetDevice()
{
	return _device->GetDevice();
}

ID3D11DeviceContext* SoulGraphics::GraphicsEngine::GetDeviceContext()
{
	return _device->GetDeviceContext();
}
