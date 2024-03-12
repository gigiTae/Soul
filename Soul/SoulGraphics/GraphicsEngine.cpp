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

	// 결과값.
	HRESULT hr = 0;

	// 스왑체인 속성 설정 구조체 생성.
	DXGI_SWAP_CHAIN_DESC swapDesc = {};
#if USE_FLIPMODE==1
	swapDesc.BufferCount = 2;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
#else
	swapDesc.BufferCount = 1;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;	//기본값 0
#endif
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = info.hwnd;	// 스왑체인 출력할 창 핸들 값.
	swapDesc.Windowed = true;		// 창 모드 여부 설정.
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	// 백버퍼(텍스처)의 가로/세로 크기 설정.
	swapDesc.BufferDesc.Width = width;
	swapDesc.BufferDesc.Height = height;
	// 화면 주사율 설정.
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	// 샘플링 관련 설정.
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;

	UINT creationFlags = 0;
#ifdef _DEBUG
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	// 1. 장치 생성.   2.스왑체인 생성. 3.장치 컨텍스트 생성.
	HR_T(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, creationFlags, NULL, NULL,
		D3D11_SDK_VERSION, &swapDesc, &_swapChain, &_device, NULL, &_deviceContext));

	// 4. 렌더타겟뷰 생성.  (백버퍼를 이용하는 렌더타겟뷰)	
	ID3D11Texture2D* pBackBufferTexture = nullptr;
	HR_T(_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBufferTexture));
	HR_T(_device->CreateRenderTargetView(pBackBufferTexture, NULL, &_renderTargetView));  // 텍스처는 내부 참조 증가
	SAFE_RELEASE(pBackBufferTexture);	//외부 참조 카운트를 감소시킨다.

#if USE_FLIPMODE==0
	// 렌더 타겟을 최종 출력 파이프라인에 바인딩합니다.
	// FlipMode가 아닐때는 최초 한번만 설정하면 된다.
	_deviceContext->OMSetRenderTargets(1, &_renderTargetView, NULL);
#endif

}

void SoulGraphics::GraphicsEngine::Render()
{
#if USE_FLIPMODE==1
	// Flip모드에서는 매프레임 설정 필요
	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);
#endif
	DirectX::SimpleMath::Color color(0.0f, 0.5f, 0.5f, 1.0f);
	// 화면 칠하기.
	_deviceContext->ClearRenderTargetView(_renderTargetView, color);

	// 스왑체인 교체.
	_swapChain->Present(0, 0);
}

void SoulGraphics::GraphicsEngine::Finalize()
{

}
