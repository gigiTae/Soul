#pragma once

#include <directxtk/simplemath.h>
#include <Windows.h>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")

#include "InitializeInfomation.h"

namespace SoulGraphics
{
	class IGraphicsEngine
	{
	public:
		virtual ~IGraphicsEngine(){}

		virtual void Initialize(InitalizeInfomation info) abstract;

		virtual void Render() abstract;

		virtual void EndRender() abstract;

		virtual void Finalize() abstract;

		virtual void AddMeshObject(MeshObjectInfomation info) abstract;

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