#include "SoulGraphicsPCH.h"
#include "GraphicsEngine.h"
#include "ResourceManager.h"
#include "Device.h"
#include "RenderTarget.h"
#include "RenderState.h"
#include "Camera.h"
#include "Scene.h"
#include "Box.h"

SoulGraphics::GraphicsEngine::GraphicsEngine()
	:_device(std::make_shared<Device>())
	, _renderTarget(std::make_shared<RenderTarget>())
	, _renderState(std::make_shared<RenderState>())
	, _camera(std::make_unique<Camera>())
	, _resourceManager(std::make_unique<ResourceManager>())
	, _scene(nullptr)
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
	_renderState->Initialize(_device);
	_resourceManager->Initialize(_device);
	//_scene->Initialize();

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
	_resourceManager->Finalize();

	_renderTarget->Finalize();
	_renderState->Finalize();
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

