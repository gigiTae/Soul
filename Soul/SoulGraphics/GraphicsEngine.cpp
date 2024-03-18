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
	, box(new Box())
{}

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

	box->Initialize(_device.get());
	box->SetHeight(static_cast<FLOAT>(height));
	box->SetWidth(static_cast<FLOAT>(width));
}

void SoulGraphics::GraphicsEngine::Render()
{
	_renderTarget->SetRenderTargetView(RenderTarget::Type::First);
	_renderTarget->ClearRenderTargetView(RenderTarget::Type::First);

	using namespace DirectX::SimpleMath;

	static float r = 0.f;
	r += 0.0001f;
	Matrix m_World = DirectX::XMMatrixRotationX(r);

	box->SetWorldTM(m_World);
	box->SetViewProjTM(_camera.get());
	box->Render(_device.get(), _renderState.get(), _renderTarget.get());
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
	auto baseColor = _resourceManager->LoadTexture(info.baseColor);
	auto normal = _resourceManager->LoadTexture(info.normalMap);

}

void SoulGraphics::GraphicsEngine::UpdateCamera(DirectX::SimpleMath::Matrix tm)
{
	_camera->Update(tm);
}

ID3D11Device* SoulGraphics::GraphicsEngine::GetDevice()
{
	return _device->GetDevice();
}

ID3D11DeviceContext* SoulGraphics::GraphicsEngine::GetDeviceContext()
{
	return _device->GetDeviceContext();
}

