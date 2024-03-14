#include "SoulEnginePCH.h"
#include "ToolEngine.h"

Soul::ToolEngine::ToolEngine()
:_graphicsEngine(nullptr)
{
	_graphicsEngine = SoulGraphics::Exporter::MakeGrapicsEngine();
}

Soul::ToolEngine::~ToolEngine()
{

}

void Soul::ToolEngine::Initialize(WindowInfomation info)
{
	SoulGraphics::InitalizeInfomation initInfo{ info.hInstance,info.hwnd, info.rect };
	_graphicsEngine->Initialize(initInfo);
}

void Soul::ToolEngine::Process()
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

void Soul::ToolEngine::Finalize()
{
	_graphicsEngine->Finalize();
	SoulGraphics::Exporter::DestroyGrapicsEngnie();
}
