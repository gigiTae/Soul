#include "SoulGraphicsPCH.h"
#include "Camera.h"

SoulGraphics::Camera::Camera()
	:_screenHeight(0),
	_screenWidth(0),
	_viewTM{},
	_projTM{},
	_farPlain(0.f),
	_nearPlain(0.f),
	_fieldofView(0.f),
	_projectionType(ProjectionType::Perspective)
{} 


void SoulGraphics::Camera::MakeProjectionMatrix()
{
	if (_projectionType == ProjectionType::Perspective)
	{
		_projTM = DirectX::SimpleMath::Matrix::CreatePerspective(static_cast<float>(_screenWidth),
			static_cast<float>(_screenHeight), _nearPlain, _farPlain);
	}
	else
	{
		_projTM = DirectX::SimpleMath::Matrix::CreateOrthographic(static_cast<float>(_screenWidth),
			static_cast<float>(_screenHeight), _nearPlain, _farPlain);
	}
}

void SoulGraphics::Camera::Update(DirectX::SimpleMath::Matrix mat)
{
	DirectX::SimpleMath::Vector3 scale{};
	mat.Decompose(scale, _rotation, _position);

	_viewTM = mat.Invert();
	MakeProjectionMatrix();
}

void SoulGraphics::Camera::SetScreenSize(UINT width, UINT height)
{
	_screenWidth = width;
	_screenHeight = height;

	MakeProjectionMatrix();
}
