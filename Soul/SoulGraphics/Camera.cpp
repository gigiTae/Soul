#include "SoulGraphicsPCH.h"
#include "Camera.h"

SoulGraphics::Camera::Camera()
	:_screenHeight(0),
	_screenWidth(0),
	_viewTM{},
	_projTM{},
	_farPlain(1000.f),
	_nearPlain(0.1f),
	_fieldofView(14.f),
	_projectionType(ProjectionType::Perspective)
{}

void SoulGraphics::Camera::Initialize(UINT width, UINT height)
{
	using namespace DirectX;

	_screenWidth = width;
	_screenHeight = height;

	// Initialize the view matrix
	XMVECTOR Eye = XMVectorSet(0.0f, 1.0f, -5.0f, 0.0f);
	XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	_viewTM = XMMatrixLookAtLH(Eye, At, Up);
	_projTM = XMMatrixPerspectiveFovLH(XM_PIDIV2, width / (FLOAT)height, _nearPlain, _farPlain);
}

void SoulGraphics::Camera::MakeProjectionMatrix()
{
	if (_projectionType == ProjectionType::Perspective)
	{
		_projTM =DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV2, _screenWidth / (FLOAT)_screenHeight, _nearPlain, _farPlain);
		/*	_projTM = DirectX::SimpleMath::Matrix::CreatePerspective(static_cast<float>(_screenWidth),
				static_cast<float>(_screenHeight), _nearPlain, _farPlain)*/;
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
