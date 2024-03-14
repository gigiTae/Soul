#include "SoulEnginePCH.h"
#include "GameEngine.h"
#include "InputManager.h"

#include <imgui_impl_dx11.h>
#include <imgui.h>
#include <imgui_impl_win32.h>

Soul::GameEngine::GameEngine()
	:_graphicsEngine(nullptr)
	, _position()
	, _rotation(DirectX::SimpleMath::Quaternion::Identity)
	, _inputManager(std::make_unique<SoulEngine::InputManager>())
{
	_graphicsEngine = SoulGraphics::Exporter::MakeGrapicsEngine();
}

Soul::GameEngine::~GameEngine()
{

}

void Soul::GameEngine::Initialize(WindowInfomation info)
{
	SoulGraphics::InitalizeInfomation initInfo{ info.hInstance,info.hwnd, info.rect };
	_graphicsEngine->Initialize(initInfo);
	_inputManager->Initalize(info.hwnd);

	ImGuiInit(info.hwnd);
}

void Soul::GameEngine::Process()
{
	MSG msg;

	bool isDone = false;

	while (!isDone)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				isDone = true;
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			_inputManager->Update(0.f);

			CameraUpdate();

			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			_graphicsEngine->Render();

			if (ImGui::Begin("Camera"))
			{
				// Position
				float pos[3] = { _position.x,_position.y,_position.z };

				if (ImGui::DragFloat3("position", pos))
				{
					_position = { pos[0],pos[1],pos[2] };
				}
				ImGui::End();
			}

			ImGui::Render();
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
			_graphicsEngine->EndRender();
		}
	}
}

void Soul::GameEngine::Finalize()
{
	_graphicsEngine->Finalize();
	SoulGraphics::Exporter::DestroyGrapicsEngnie();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void Soul::GameEngine::CameraUpdate()
{
	using namespace DirectX::SimpleMath;

	if (_inputManager->IsKeyState(Key::Left, KeyState::Hold))
	{
		_rotation *= Quaternion::CreateFromAxisAngle(Vector3{ 0.f,1.f,0.f }, 0.001f);
	}

	Matrix transM = Matrix::CreateTranslation(_position);
	Matrix rotM = Matrix::CreateFromQuaternion(_rotation);

	_graphicsEngine->UpdateCamera(rotM*transM);
}

void Soul::GameEngine::ImGuiInit(HWND hwnd)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(hwnd);
	auto device = static_cast<ID3D11Device*>(_graphicsEngine->GetDevice());
	auto deviceContext = _graphicsEngine->GetDeviceContext();
	ImGui_ImplDX11_Init(device, deviceContext);
}
