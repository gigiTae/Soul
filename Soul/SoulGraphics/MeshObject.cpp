#include "SoulGraphicsPCH.h"
#include "MeshObject.h"
#include "Camera.h"
#include "Device.h"
#include "RenderState.h"
#include "RenderTarget.h"

SoulGraphics::MeshObject::MeshObject()
{

}

SoulGraphics::MeshObject::~MeshObject()
{

}


void SoulGraphics::MeshObject::Render(Device* device, RenderState* state, RenderTarget* renderTarget)
{
}

DirectX::SimpleMath::Matrix SoulGraphics::MeshObject::GetWorldTM() const
{
	return _worldTM;
}

void SoulGraphics::MeshObject::SetWorldTM(DirectX::SimpleMath::Matrix mat)
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
