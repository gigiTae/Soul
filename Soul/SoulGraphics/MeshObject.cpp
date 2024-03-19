#include "SoulGraphicsPCH.h"
#include "MeshObject.h"
#include "Camera.h"
#include "Device.h"
#include "RenderState.h"
#include "RenderTarget.h"
#include "Shader.h"
#include "Texture.h"
#include "GeometryBuffer.h"
#include "ConstantBufferStruct.h"
#include "ConstantBuffer.h"

SoulGraphics::MeshObject::MeshObject(std::shared_ptr<GeometryBuffer> gb, std::shared_ptr<ConstantBuffer> cb, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	:_geometryBuffer(gb)
	, _constantBuffer(cb)
	, _shader(shader)
	, _texture(texture)
	, _worldTM{}
	, _viewTM{}
	, _projTM{}
{}

SoulGraphics::MeshObject::~MeshObject()
{}


void SoulGraphics::MeshObject::Render(Device* device, RenderState* state, RenderTarget* renderTarget)
{
	auto deviceContext = device->GetDeviceContext();

	// Matrix 상수버퍼 설정
	_constantBuffer->SetMatrixCB(_worldTM, _viewTM, _projTM);
	_shader->SetShader();
	_texture->SetTexture(0);
	state->SetRasterizerState(RenderState::Rasterizer::Solid);
	state->SetSamplerState(0, RenderState::Sampler::LINEAR);

	for (UINT i = 0; i < _geometryBuffer->GetMeshSize(); ++i)
	{
		_geometryBuffer->GetIndexBuffer(i);
		_geometryBuffer->GetVertexBuffer(i);
		_geometryBuffer->GetVertexSize(i);
		_geometryBuffer->GetIndexSize(i);

		// 정점, 인덱스 버퍼 생성
		_geometryBuffer->SetVertexAndIndexBuffer(i);

		deviceContext->DrawIndexed(_geometryBuffer->GetIndexSize(i), 0, 0);
	}

}

DirectX::SimpleMath::Matrix SoulGraphics::MeshObject::GetWorldTM() const
{
	return _worldTM;
}

void SoulGraphics::MeshObject::SetWorldTM(const DirectX::SimpleMath::Matrix& mat)
{
	_worldTM = mat;
}

void SoulGraphics::MeshObject::SetViewProjTM(Camera* camera)
{
	_viewTM = camera->GetViewTM();
	_projTM = camera->GetProjTM();
}

void SoulGraphics::MeshObject::SetGeometryBuffer(const std::shared_ptr<GeometryBuffer>& buffer)
{
	_geometryBuffer = buffer;
}

std::shared_ptr<SoulGraphics::GeometryBuffer> SoulGraphics::MeshObject::GetGeometryBuffer()
{
	return _geometryBuffer;
}
