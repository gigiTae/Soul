#include "SoulGraphicsPCH.h"
#include "Box.h"
#include "Camera.h"
#include "Vertex.h"
#include "RenderState.h"
#include "Device.h"
#include "ConstantBufferStruct.h"

SoulGraphics::Box::Box()
	:_worldTM(DirectX::SimpleMath::Matrix::Identity)
	, _viewTM(DirectX::SimpleMath::Matrix::Identity)
	, _projTM(DirectX::SimpleMath::Matrix::Identity)
	, _inputLayout(nullptr)
	, _pixelShader(nullptr)
	, _vertexShader(nullptr)
	, _vertexBufferOffset(0)
	, _vertexBufferStride(0)
	, _vertexBuffer(nullptr)
	, _indexBuffer(nullptr)
	, _indices(0)
	, _constantBuffer(nullptr)
	, _samepleState(nullptr)
	, _textureRV(nullptr)
	,_width(0)
	,_height(0)
{}

SoulGraphics::Box::~Box()
{}

void SoulGraphics::Box::Render(Device* device, RenderState* state, RenderTarget* renderTarget)
{
	auto deviceContext = device->GetDXDeviceContext();
	// 상수버퍼 
	CB::Matrix cb;
	cb.world = DirectX::XMMatrixTranspose(_worldTM);
	cb.view = DirectX::XMMatrixTranspose(_viewTM);
	cb.projection = DirectX::XMMatrixTranspose(_projTM);
	deviceContext->UpdateSubresource(_constantBuffer, 0, nullptr, &cb, 0, 0);

	deviceContext->RSSetState(state->GetRasterizerState(RenderState::Rasterizer::Solid));
	deviceContext->PSSetSamplers(0, 1, &_samepleState);
	
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	deviceContext->IASetVertexBuffers(0, 1, &_vertexBuffer, &_vertexBufferStride, &_vertexBufferOffset);
	deviceContext->IASetInputLayout(_inputLayout);
	deviceContext->IASetIndexBuffer(_indexBuffer, DXGI_FORMAT_R32_UINT, 0);	// INDEX값의 범위
	deviceContext->VSSetShader(_vertexShader, nullptr, 0);
	deviceContext->PSSetShader(_pixelShader, nullptr, 0);
	deviceContext->VSSetConstantBuffers(0, 1, &_constantBuffer);

	deviceContext->PSSetShaderResources(0, 1, &_textureRV);

	deviceContext->DrawIndexed(_indices, 0, 0);
}

void SoulGraphics::Box::Initialize(Device* device)
{
	HRESULT hr = 0; // 결과값.
	ID3D10Blob* errorMessage = nullptr;	 // 에러 메시지를 저장할 버퍼.

	using namespace DirectX::SimpleMath;

	SoulGraphics::Vertex::PosTex vertices[] =
	{
		{ Vector3(-1.0f, 1.0f, -1.0f), Vector2(1.0f, 0.0f) },
		{ Vector3(1.0f, 1.0f, -1.0f), Vector2(0.0f, 0.0f) },
		{ Vector3(1.0f, 1.0f, 1.0f), Vector2(0.0f, 1.0f) },
		{ Vector3(-1.0f, 1.0f, 1.0f), Vector2(1.0f, 1.0f) },

		{ Vector3(-1.0f, -1.0f, -1.0f), Vector2(0.0f, 0.0f) },
		{ Vector3(1.0f, -1.0f, -1.0f), Vector2(1.0f, 0.0f) },
		{ Vector3(1.0f, -1.0f, 1.0f), Vector2(1.0f, 1.0f) },
		{ Vector3(-1.0f, -1.0f, 1.0f), Vector2(0.0f, 1.0f) },

		{ Vector3(-1.0f, -1.0f, 1.0f), Vector2(0.0f, 1.0f) },
		{ Vector3(-1.0f, -1.0f, -1.0f), Vector2(1.0f, 1.0f) },
		{ Vector3(-1.0f, 1.0f, -1.0f), Vector2(1.0f, 0.0f) },
		{ Vector3(-1.0f, 1.0f, 1.0f), Vector2(0.0f, 0.0f) },

		{ Vector3(1.0f, -1.0f, 1.0f), Vector2(1.0f, 1.0f) },
		{ Vector3(1.0f, -1.0f, -1.0f), Vector2(0.0f, 1.0f) },
		{ Vector3(1.0f, 1.0f, -1.0f), Vector2(0.0f, 0.0f) },
		{ Vector3(1.0f, 1.0f, 1.0f), Vector2(1.0f, 0.0f) },

		{ Vector3(-1.0f, -1.0f, -1.0f), Vector2(0.0f, 1.0f) },
		{ Vector3(1.0f, -1.0f, -1.0f), Vector2(1.0f, 1.0f) },
		{ Vector3(1.0f, 1.0f, -1.0f), Vector2(1.0f, 0.0f) },
		{ Vector3(-1.0f, 1.0f, -1.0f), Vector2(0.0f, 0.0f) },

		{ Vector3(-1.0f, -1.0f, 1.0f), Vector2(1.0f, 1.0f) },
		{ Vector3(1.0f, -1.0f, 1.0f), Vector2(0.0f, 1.0f) },
		{ Vector3(1.0f, 1.0f, 1.0f), Vector2(0.0f, 0.0f) },
		{ Vector3(-1.0f, 1.0f, 1.0f), Vector2(1.0f, 0.0f) },
	};

	D3D11_BUFFER_DESC bd = {};
	bd.ByteWidth = sizeof(Vertex::PosTex) * ARRAYSIZE(vertices);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA vbData = {};
	vbData.pSysMem = vertices; // 배열 데이터 할당.
	HR_T(device->GetDXDevice()->CreateBuffer(&bd, &vbData, &_vertexBuffer));

	_vertexBufferStride = sizeof(Vertex::PosTex);
	_vertexBufferOffset = 0;

 	ID3D10Blob* vertexShaderBuffer = nullptr;	// 정점 셰이더 코드가 저장될 버퍼.
	HR_T(CompileShaderFromFile(L"BasicVS.hlsl", "main", "vs_4_0", &vertexShaderBuffer));

	HR_T(device->GetDXDevice()->CreateInputLayout(Vertex::InputLayoutDesc::posTex, ARRAYSIZE(Vertex::InputLayoutDesc::posTex),
		vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &_inputLayout));

	HR_T(device->GetDXDevice()->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(), NULL, &_vertexShader));
	
	SAFE_RELEASE(vertexShaderBuffer);

	WORD indices[] =
	{
		3,1,0, 2,1,3,
		6,4,5, 7,4,6,
		11,9,8, 10,9,11,
		14,12,13, 15,12,14,
		19,17,16, 18,17,19,
		22,20,21, 23,20,22
	};

	_indices = ARRAYSIZE(indices);
	bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * ARRAYSIZE(indices);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA ibData = {};
	ibData.pSysMem = indices;
	HR_T(device->GetDXDevice()->CreateBuffer(&bd, &ibData, &_indexBuffer));

	ID3D10Blob* pixelShaderBuffer = nullptr;	// 픽셀 셰이더 코드가 저장될 버퍼.
	HR_T(CompileShaderFromFile(L"BasicPS.hlsl", "main", "ps_5_0", &pixelShaderBuffer));
	HR_T(device->GetDXDevice()->CreatePixelShader(
		pixelShaderBuffer->GetBufferPointer(),
		pixelShaderBuffer->GetBufferSize(), NULL, &_pixelShader));
	
	SAFE_RELEASE(pixelShaderBuffer);

	// 6. Render() 에서 파이프라인에 바인딩할 상수 버퍼 생성
	// Create the constant buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(CB::Matrix);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	HR_T(device->GetDXDevice()->CreateBuffer(&bd, nullptr, &_constantBuffer));

	// 텍스쳐 로드 
	HR_T(DirectX::CreateDDSTextureFromFile(device->GetDXDevice(), L"seafloor.dds", nullptr, &_textureRV));
	 
	D3D11_SAMPLER_DESC sampDesc = {};
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	HR_T(device->GetDXDevice()->CreateSamplerState(&sampDesc, &_samepleState));

}

DirectX::SimpleMath::Matrix SoulGraphics::Box::GetWorldTM() const
{
	return _worldTM;
}

void SoulGraphics::Box::SetWorldTM(const DirectX::SimpleMath::Matrix& mat)
{
	_worldTM = mat;
}

void SoulGraphics::Box::SetViewProjTM(Camera* camera)
{
	_viewTM = camera->GetViewTM();
	_projTM = camera->GetProjTM();
}

void SoulGraphics::Box::SetGeometryBuffer(const std::shared_ptr<GeometryBuffer>& buffer)
{
}

std::shared_ptr<SoulGraphics::GeometryBuffer> SoulGraphics::Box::GetGeometryBuffer()
{
	return nullptr;
}
