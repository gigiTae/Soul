#include "SoulGraphicsPCH.h"
#include "Box.h"
#include "Camera.h"
#include "Vertex.h"

SoulGraphics::Box::Box()
	:_worldTM(DirectX::SimpleMath::Matrix::Identity)
	, _viewTM(DirectX::SimpleMath::Matrix::Identity)
	, _projTM(DirectX::SimpleMath::Matrix::Identity)
	,_geometryBuffer(nullptr)
{}

SoulGraphics::Box::~Box()
{

}

void SoulGraphics::Box::Render(Device* device, RenderState* state, RenderTarget* renderTarget)
{
}

void SoulGraphics::Box::Initialize()
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



	UINT indices[] =
	{
		3,1,0, 2,1,3,
		0,5,4, 1,5,0,
		3,4,7, 0,4,3,
		1,6,5, 2,6,1,
		2,7,6, 3,7,2,
		6,4,5, 7,4,6,
	};
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
	_geometryBuffer = buffer;
}

std::shared_ptr<SoulGraphics::GeometryBuffer> SoulGraphics::Box::GetGeometryBuffer()
{
	return _geometryBuffer;
}
