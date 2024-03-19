#include "SoulGraphicsPCH.h"
#include "RenderState.h"
#include "Device.h"

SoulGraphics::RenderState::RenderState()
	:_rasterizerStates{}
	,_samplerStates{}
	, _device(nullptr)
{}

SoulGraphics::RenderState::~RenderState()
{}

void SoulGraphics::RenderState::Initialize(const std::shared_ptr<Device>& device)
{
	_device = device;

	// RasterizerState 

	// 솔리드
	D3D11_RASTERIZER_DESC solidDesc;
	ZeroMemory(&solidDesc, sizeof(D3D11_RASTERIZER_DESC));
	solidDesc.FillMode = D3D11_FILL_SOLID;
	solidDesc.CullMode = D3D11_CULL_BACK;
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

	// SamplerState

	// Linear
	D3D11_SAMPLER_DESC sampDesc = {};
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	HR_T(device->GetDevice()->CreateSamplerState(&sampDesc,
		&_samplerStates[static_cast<size_t>(Sampler::LINEAR)]));
}

void SoulGraphics::RenderState::Finalize()
{
	for (auto rs : _rasterizerStates)
	{
		SAFE_RELEASE(rs);
	}

	for (auto ss : _samplerStates)
	{
		SAFE_RELEASE(ss);
	}

}


ID3D11RasterizerState* SoulGraphics::RenderState::GetRasterizerState(Rasterizer state) const
{
	return _rasterizerStates[static_cast<size_t>(state)];
}


ID3D11SamplerState** SoulGraphics::RenderState::GetSamplerState(Sampler state)
{
	return &_samplerStates[static_cast<size_t>(state)];
}

void SoulGraphics::RenderState::SetRasterizerState(Rasterizer stata) const
{
	_device->GetDeviceContext()->RSSetState(_rasterizerStates[static_cast<size_t>(stata)]);
}

void SoulGraphics::RenderState::SetSamplerState(UINT slot , Sampler state)
{
	_device->GetDeviceContext()->PSSetSamplers(slot, 1, &_samplerStates[static_cast<size_t>(state)]);
}
