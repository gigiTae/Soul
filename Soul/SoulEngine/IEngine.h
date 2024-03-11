#pragma once

#include <windows.h>
#include "ExportSoul.h"

namespace Soul
{
	class IEngine
	{
	public:
		virtual ~IEngine() {}

		virtual SOUL_ENGNIE_API void Initialize(HWND hwnd) abstract;

		virtual SOUL_ENGNIE_API void Process() abstract;

		virtual SOUL_ENGNIE_API void Finalize() abstract;
	};

	class SoulExporter
	{
	public:
		static SOUL_ENGNIE_API IEngine* MakeGameEngine();

		static SOUL_ENGNIE_API IEngine* MakeToolEngine();

		static SOUL_ENGNIE_API void DestroyEngine();

		static SOUL_ENGNIE_API LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		static SOUL_ENGNIE_API LRESULT CALLBACK ToolWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	private:
		static IEngine* _engine;
	};
}