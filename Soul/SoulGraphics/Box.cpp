#include "SoulGraphicsPCH.h"
#include "Box.h"
#include "Camera.h"
#include "Vertex.h"
#include "RenderState.h"
#include "Device.h"

SoulGraphics::Box::Box()
	:_worldTM(DirectX::SimpleMath::Matrix::Identity)
	, _viewTM(DirectX::SimpleMath::Matrix::Identity)
	, _projTM(DirectX::SimpleMath::Matrix::Identity)
	,_inputLayout(nullptr)
	,_pixelShader(nullptr)
	,_vertexShader(nullptr)
	,_vertexBufferOffset(0)
	,_vertexBufferStride(0)
	,_vertexBuffer(nullptr)
	,_indexBuffer(nullptr)
	,_indices(0)
	,_constantBuffer(nullptr)
{}

SoulGraphics::Box::~Box()
{}

void SoulGraphics::Box::Render(Device* device, RenderState* state, RenderTarget* renderTarget)
{
	auto deviceContext = device->GetDeviceContext();
	// 상수버퍼 
	ContantBuffer cb;
	cb.world = DirectX::XMMatrixTranspose(_worldTM);
	cb.view = DirectX::XMMatrixTranspose(_viewTM);
	cb.projection = DirectX::XMMatrixTranspose(_projTM);
	deviceContext->UpdateSubresource(_constantBuffer, 0, nullptr, &cb, 0, 0);

	deviceContext->RSSetState(state->GetRasterizerState(RenderState::Rasterizer::Solid));
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	deviceContext->IASetVertexBuffers(0, 1, &_vertexBuffer, &_vertexBufferStride, &_vertexBufferOffset);
	deviceContext->IASetInputLayout(_inputLayout);
	deviceContext->IASetIndexBuffer(_indexBuffer, DXGI_FORMAT_R16_UINT, 0);	// INDEX값의 범위
	deviceContext->VSSetShader(_vertexShader, nullptr, 0);
	deviceContext->PSSetShader(_pixelShader, nullptr, 0);
	deviceContext->VSSetConstantBuffers(0, 1, &_constantBuffer);

	deviceContext->DrawIndexed(_indices, 0, 0);
}

void SoulGraphics::Box::Initialize(Device* device)
{
	HRESULT hr = 0; // 결과값.
	ID3D10Blob* errorMessage = nullptr;	 // 에러 메시지를 저장할 버퍼.

	using namespace DirectX::SimpleMath;

	SoulGraphics::Vertex::PosColor vertices[] =
	{
		{ Vector3(-1.0f, 1.0f, -1.0f),	Vector4(0.0f, 0.0f, 1.0f, 1.0f) },
		{ Vector3(1.0f, 1.0f, -1.0f),	Vector4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ Vector3(1.0f, 1.0f, 1.0f),	Vector4(0.0f, 1.0f, 1.0f, 1.0f) },
		{ Vector3(-1.0f, 1.0f, 1.0f),	Vector4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ Vector3(-1.0f, -1.0f, -1.0f), Vector4(1.0f, 0.0f, 1.0f, 1.0f) },
		{ Vector3(1.0f, -1.0f, -1.0f),	Vector4(1.0f, 1.0f, 0.0f, 1.0f) },
		{ Vector3(1.0f, -1.0f, 1.0f),	Vector4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ Vector3(-1.0f, -1.0f, 1.0f),	Vector4(0.0f, 0.0f, 0.0f, 1.0f) },
	};

	D3D11_BUFFER_DESC bd = {};
	bd.ByteWidth = sizeof(Vertex::PosColor) * ARRAYSIZE(vertices);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA vbData = {};
	vbData.pSysMem = vertices; // 배열 데이터 할당.
	HR_T(device->GetDevice()->CreateBuffer(&bd, &vbData, &_vertexBuffer));

	_vertexBufferStride = sizeof(Vertex::PosColor);
	_vertexBufferOffset = 0;

	ID3D10Blob* vertexShaderBuffer = nullptr;	// 정점 셰이더 코드가 저장될 버퍼.
	HR_T(CompileShaderFromFile(L"BasicVS.hlsl", "main", "vs_5_0", &vertexShaderBuffer));
	HR_T(device->GetDevice()->CreateInputLayout(Vertex::InputLayoutDesc::posColor, ARRAYSIZE(Vertex::InputLayoutDesc::posColor),
		vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &_inputLayout));

	HR_T(device->GetDevice()->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(), NULL, &_vertexShader));
	SAFE_RELEASE(vertexShaderBuffer);

	WORD indices[] =
	{
		3,1,0, 2,1,3,
		0,5,4, 1,5,0,
		3,4,7, 0,4,3,
		1,6,5, 2,6,1,
		2,7,6, 3,7,2,
		6,4,5, 7,4,6,
	};

	_indices = ARRAYSIZE(indices);
	bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * ARRAYSIZE(indices);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA ibData = {};
	ibData.pSysMem = indices;
	HR_T(device->GetDevice()->CreateBuffer(&bd, &ibData, &_indexBuffer));

	ID3D10Blob* pixelShaderBuffer = nullptr;	// 픽셀 셰이더 코드가 저장될 버퍼.
	HR_T(CompileShaderFromFile(L"BasicPS.hlsl", "main", "ps_5_0", &pixelShaderBuffer));
	HR_T(device->GetDevice()->CreatePixelShader(
		pixelShaderBuffer->GetBufferPointer(),
		pixelShaderBuffer->GetBufferSize(), NULL, &_pixelShader));
	SAFE_RELEASE(pixelShaderBuffer);
	
	// 6. Render() 에서 파이프라인에 바인딩할 상수 버퍼 생성
	// Create the constant buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ContantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	HR_T(device->GetDevice()->CreateBuffer(&bd, nullptr, &_constantBuffer));
}

DirectX::SimpleMath::Matrix SoulGraphics::Box::GetWorldTM() const
{
	return _worldTM;
}

void SoulGraphics::Box::SetWorldTM(DirectX::SimpleMath::Matrix mat)
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
