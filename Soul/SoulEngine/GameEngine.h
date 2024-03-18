#pragma once
#include "IEngine.h"

namespace SoulEngine
{
	class InputManager;
}


namespace Soul
{
	class GameEngine : public IEngine
	{
	public:
		GameEngine();
		~GameEngine();

		void Initialize(WindowInfomation info) override;

		void Process() override;

		void Finalize() override;

	private:
		void CameraUpdate();
		void ImGuiInit(HWND hwnd);

	private:
		SoulGraphics::IGraphicsEngine* _graphicsEngine;
		std::unique_ptr<SoulEngine::InputManager> _inputManager;

		DirectX::SimpleMath::Vector3 _position;
		DirectX::SimpleMath::Quaternion _rotation;
	};


}