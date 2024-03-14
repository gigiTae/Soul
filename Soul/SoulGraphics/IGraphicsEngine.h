#pragma once

#include <directxtk/simplemath.h>
#include <Windows.h>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")

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

		virtual void EndRender() abstract;

		virtual void Finalize() abstract;

		// Camera 
		virtual void UpdateCamera(DirectX::SimpleMath::Matrix tm) abstract;
		virtual struct ID3D11Device* GetDevice() abstract;
		virtual struct ID3D11DeviceContext* GetDeviceContext() abstract;
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