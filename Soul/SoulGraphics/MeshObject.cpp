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
#include "Material.h"

SoulGraphics::MeshObject::MeshObject(std::shared_ptr<GeometryBuffer> gb
	, std::shared_ptr<ConstantBuffer> cb
	, std::shared_ptr<Shader> shader
	, std::shared_ptr<Material> material)
	:_geometryBuffer(gb)
	, _constantBuffer(cb)
	, _shader(shader)
	,_material(material)
	, _worldTM{}
	, _viewTM{}
	, _projTM{}
{}

SoulGraphics::MeshObject::~MeshObject()
{}


void SoulGraphics::MeshObject::Render(Device* device, RenderState* state, RenderTarget* renderTarget)
{
	auto deviceContext = device->GetDXDeviceContext();

	// Matrix 상수버퍼 설정
	_constantBuffer->BindMatrixCB(_worldTM, _viewTM, _projTM);
	_shader->BindShader();
	_material->BindTexture(0, Material::Type::BaseColor);
	_material->BindTexture(1, Material::Type::Normal);

	state->BindRasterizerState(RenderState::Rasterizer::Solid);
	state->BindSamplerState(0, RenderState::Sampler::LINEAR);

	for (UINT i = 0; i < _geometryBuffer->GetMeshSize(); ++i)
	{
		// 정점, 인덱스 버퍼 생성
		_geometryBuffer->BindVertexAndIndexBuffer(i);

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
