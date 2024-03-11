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

void Soul::GameEngine::Initialize(HWND hwnd)
{

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

		}
	}
}

void Soul::GameEngine::Finalize()
{


}
