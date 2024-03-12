#pragma once


namespace SoulGraphics
{
	class Camera
	{
	public:
		enum class ProjectionType
		{
			Perspective, 
			Orthographic // 직각 투영
		};

	public:
		Camera();

		void Update(DirectX::SimpleMath::Matrix mat);

		void SetScreenSize(UINT width, UINT height);

		DirectX::SimpleMath::Vector3 GetPosition()const { return _position; }
		DirectX::SimpleMath::Quaternion GetRotation()const { return _rotation; }
		DirectX::SimpleMath::Matrix GetViewTM()const { return _viewTM; }
		DirectX::SimpleMath::Matrix GetProjTM()const { return _projTM; }

	private:
		void MakeProjectionMatrix();

	private:
		UINT _screenWidth;
		UINT _screenHeight;

		DirectX::SimpleMath::Vector3 _position;
		DirectX::SimpleMath::Quaternion _rotation;
		DirectX::SimpleMath::Matrix _viewTM;
		DirectX::SimpleMath::Matrix _projTM;

		ProjectionType _projectionType;
		float _fieldofView;
		float _nearPlain;
		float _farPlain;
	};


}