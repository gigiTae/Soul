#include "SoulEnginePCH.h"
#include "GameEngine.h"

Soul::GameEngine::GameEngine()
	:_graphicsEngine(nullptr)
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
			_graphicsEngine->Render();
		}
	}
}

void Soul::GameEngine::Finalize()
{
	_graphicsEngine->Finalize();
	SoulGraphics::Exporter::DestroyGrapicsEngnie();
}
