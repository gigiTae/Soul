#include "SoulGraphicsPCH.h"
#include "MeshObject.h"
#include "Camera.h"
#include "Device.h"
#include "RenderState.h"
#include "RenderTarget.h"
#include "ContantBuffer.h"
#include "Shader.h"
#include "GeometryBuffer.h"

SoulGraphics::MeshObject::MeshObject(std::shared_ptr<GeometryBuffer> buffer,
	std::shared_ptr<Shader> shader,
	std::shared_ptr<Texture> texture)
	:_geometryBuffer(buffer)
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

	ContantBuffer::Matrix cb;
	cb.world = DirectX::XMMatrixTranspose(_worldTM);
	cb.view = DirectX::XMMatrixTranspose(_viewTM);
	cb.projection = DirectX::XMMatrixTranspose(_projTM);
	//deviceContext->UpdateSubresource(_constantBuffer, 0, nullptr, &cb, 0, 0);

	deviceContext->IASetInputLayout(_shader->GetInputLayout());

	for (UINT i = 0; i < _geometryBuffer->GetMeshSize(); ++i)
	{
		_geometryBuffer->GetIndexBuffer(i);
		_geometryBuffer->GetVertexBuffer(i);
		_geometryBuffer->GetVertexSize(i);
		_geometryBuffer->GetIndexSize(i);

		//deviceContext->IASetIndexBuffer(_geometryBuffer->GetIndexBuffer(i));
		//deviceContext->DrawIndexed(_geometryBuffer->GetIndexSize(i), 0, 0);
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
