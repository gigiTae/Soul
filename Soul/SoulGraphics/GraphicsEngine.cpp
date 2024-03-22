#include "SoulGraphicsPCH.h"
#include "GraphicsEngine.h"
#include "ResourceManager.h"
#include "Device.h"
#include "RenderTarget.h"
#include "RenderState.h"
#include "Camera.h"
#include "Scene.h"

SoulGraphics::GraphicsEngine::GraphicsEngine()
	:_device(std::make_shared<Device>())
	, _renderTarget(std::make_shared<RenderTarget>())
	, _renderState(std::make_shared<RenderState>())
	, _camera(std::make_unique<Camera>())
	, _resourceManager(std::make_unique<ResourceManager>())
	, _scene(nullptr)
{
}

SoulGraphics::GraphicsEngine::~GraphicsEngine()
{}

void SoulGraphics::GraphicsEngine::Initialize(InitalizeInfomation info)
{
	UINT width = info.rect.right - info.rect.left;
	UINT height = info.rect.bottom - info.rect.top;

	// 결과값.
	HRESULT hr = 0;

	_device->Initialize(info.hwnd, width, height);
	_renderTarget->Initialize(_device, width, height);
	_renderState->Initialize(_device);
	_resourceManager->Initialize(_device);

	_camera->Initialize(width, height);

	_scene = std::make_unique<Scene>(this);
	_scene->Initialize();

}

void SoulGraphics::GraphicsEngine::Render()
{
	_renderTarget->SetRenderTargetView(RenderTarget::RenderTargetView::First);
	_renderTarget->Clear(RenderTarget::RenderTargetView::First);

	_scene->Render(_device.get(), _renderState.get(), _renderTarget.get());
}

void SoulGraphics::GraphicsEngine::EndRender()
{
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

void SoulGraphics::GraphicsEngine::AddMeshObject(MeshObjectInfomation info)
{
	_scene->AddMeshObject(info);
}

void SoulGraphics::GraphicsEngine::AddSkinnedMeshObject(MeshObjectInfomation info)
{
	_scene->AddSkinnedMeshObject(info);
}

void SoulGraphics::GraphicsEngine::UpdateCamera(DirectX::SimpleMath::Matrix tm)
{
	_camera->Update(tm);
}

ID3D11Device* SoulGraphics::GraphicsEngine::GetDevice()
{
	return _device->GetDXDevice();
}

ID3D11DeviceContext* SoulGraphics::GraphicsEngine::GetDeviceContext()
{
	return _device->GetDXDeviceContext();
}

