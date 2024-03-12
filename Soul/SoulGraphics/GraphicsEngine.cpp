#include "SoulGraphicsPCH.h"
#include "GraphicsEngine.h"
#include "Helper.h"

SoulGraphics::GraphicsEngine::GraphicsEngine()
{

}

SoulGraphics::GraphicsEngine::~GraphicsEngine()
{

}

void SoulGraphics::GraphicsEngine::Initialize(InitalizeInfomation info)
{
	UINT height = info.rect.right - info.rect.left;
	UINT width = info.rect.bottom - info.rect.top;

	// �����.
	HRESULT hr = 0;

	// ����ü�� �Ӽ� ���� ����ü ����.
	DXGI_SWAP_CHAIN_DESC swapDesc = {};
#if USE_FLIPMODE==1
	swapDesc.BufferCount = 2;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
#else
	swapDesc.BufferCount = 1;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;	//�⺻�� 0
#endif
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = info.hwnd;	// ����ü�� ����� â �ڵ� ��.
	swapDesc.Windowed = true;		// â ��� ���� ����.
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	// �����(�ؽ�ó)�� ����/���� ũ�� ����.
	swapDesc.BufferDesc.Width = width;
	swapDesc.BufferDesc.Height = height;
	// ȭ�� �ֻ��� ����.
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	// ���ø� ���� ����.
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;

	UINT creationFlags = 0;
#ifdef _DEBUG
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	// 1. ��ġ ����.   2.����ü�� ����. 3.��ġ ���ؽ�Ʈ ����.
	HR_T(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, creationFlags, NULL, NULL,
		D3D11_SDK_VERSION, &swapDesc, &_swapChain, &_device, NULL, &_deviceContext));

	// 4. ����Ÿ�ٺ� ����.  (����۸� �̿��ϴ� ����Ÿ�ٺ�)	
	ID3D11Texture2D* pBackBufferTexture = nullptr;
	HR_T(_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBufferTexture));
	HR_T(_device->CreateRenderTargetView(pBackBufferTexture, NULL, &_renderTargetView));  // �ؽ�ó�� ���� ���� ����
	SAFE_RELEASE(pBackBufferTexture);	//�ܺ� ���� ī��Ʈ�� ���ҽ�Ų��.

#if USE_FLIPMODE==0
	// ���� Ÿ���� ���� ��� ���������ο� ���ε��մϴ�.
	// FlipMode�� �ƴҶ��� ���� �ѹ��� �����ϸ� �ȴ�.
	_deviceContext->OMSetRenderTargets(1, &_renderTargetView, NULL);
#endif

}

void SoulGraphics::GraphicsEngine::Render()
{
#if USE_FLIPMODE==1
	// Flip��忡���� �������� ���� �ʿ�
	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);
#endif
	DirectX::SimpleMath::Color color(0.0f, 0.5f, 0.5f, 1.0f);
	// ȭ�� ĥ�ϱ�.
	_deviceContext->ClearRenderTargetView(_renderTargetView, color);

	// ����ü�� ��ü.
	_swapChain->Present(0, 0);
}

void SoulGraphics::GraphicsEngine::Finalize()
{

}
