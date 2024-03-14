#include "SoulEnginePCH.h"
#include "IEngine.h"
#include <assert.h>
#include "GameEngine.h"
#include "ToolEngine.h"

#include <imgui_impl_dx11.h>
#include <imgui.h>
#include <imgui_impl_win32.h>


Soul::IEngine* Soul::SoulExporter::_engine =nullptr;

SOUL_ENGNIE_API Soul::IEngine* Soul::SoulExporter::MakeGameEngine()
{
	assert(!_engine);
    
    _engine = new GameEngine();
    return _engine;
}

SOUL_ENGNIE_API Soul::IEngine* Soul::SoulExporter::MakeToolEngine()
{
	assert(!_engine);

    _engine = new ToolEngine();
    return _engine;
}

SOUL_ENGNIE_API void Soul::SoulExporter::DestroyEngine()
{
    assert(_engine);

    delete _engine;
}


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

SOUL_ENGNIE_API LRESULT CALLBACK Soul::SoulExporter::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		return true;

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);

	}
	return 0;
}


SOUL_ENGNIE_API LRESULT CALLBACK Soul::SoulExporter::ToolWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

