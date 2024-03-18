#pragma once

#include <string>
#include <windows.h>

namespace SoulGraphics
{
	struct InitalizeInfomation
	{
		HINSTANCE hInstance;
		HWND hwnd;
		RECT rect;
	};

	struct MeshObjectInfomation
	{
		std::wstring fbx;
		std::wstring baseColor;
		std::wstring normalMap;
	};

}