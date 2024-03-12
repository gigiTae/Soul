#pragma once

#include <DirectXMath.h>
#include <Windows.h>
#pragma comment(lib, "d3d11.lib")

namespace SoulGraphics
{
	struct InitalizeInfomation
	{
		HINSTANCE hInstance;
		HWND hwnd;
		RECT rect;
	};

	class IGraphicsEngine
	{
	public:
		virtual ~IGraphicsEngine(){}

		virtual void Initialize(InitalizeInfomation info) abstract;

		virtual void Render() abstract;

		virtual void Finalize() abstract;
	};

	class Exporter
	{
	public:
		static IGraphicsEngine* MakeGrapicsEngine();

		static void DestroyGrapicsEngnie();

	private:
		inline static IGraphicsEngine* _graphicsEngnie = nullptr;
	};


}