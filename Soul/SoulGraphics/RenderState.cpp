#include "SoulGraphicsPCH.h"
#include "RenderState.h"
#include "Device.h"

SoulGraphics::RenderState::RenderState()
	:_rasterizerStates{}
{}

SoulGraphics::RenderState::~RenderState()
{}

void SoulGraphics::RenderState::Initialize(const std::shared_ptr<Device>& device)
{
	// 솔리드
	D3D11_RASTERIZER_DESC solidDesc;
	ZeroMemory(&solidDesc, sizeof(D3D11_RASTERIZER_DESC));
	solidDesc.FillMode = D3D11_FILL_SOLID;
	solidDesc.CullMode = D3D11_CULL_NONE;
	solidDesc.FrontCounterClockwise = false;
	solidDesc.DepthClipEnable = true;
	HR_T(device->GetDevice()->CreateRasterizerState(&solidDesc,
		&_rasterizerStates[static_cast<size_t>(Rasterizer::Solid)]));

	// 와이어
	D3D11_RASTERIZER_DESC wireframeDesc;
	ZeroMemory(&wireframeDesc, sizeof(D3D11_RASTERIZER_DESC));
	wireframeDesc.FillMode = D3D11_FILL_WIREFRAME;
	wireframeDesc.CullMode = D3D11_CULL_NONE;
	wireframeDesc.FrontCounterClockwise = false;
	wireframeDesc.DepthClipEnable = true;
	HR_T(device->GetDevice()->CreateRasterizerState(&wireframeDesc,
		&_rasterizerStates[static_cast<size_t>(Rasterizer::Wireframe)]));
}

void SoulGraphics::RenderState::Finalize()
{
	for (auto rs : _rasterizerStates)
	{
		SAFE_RELEASE(rs);
	}
}

ID3D11RasterizerState* SoulGraphics::RenderState::GetRasterizerState(Rasterizer state) const
{
	return _rasterizerStates[static_cast<size_t>(state)];
}
