#pragma once

#include "IGraphicsEngine.h"

namespace SoulGraphics
{
	class GraphicsEngine : public IGraphicsEngine
	{
	public: 
		GraphicsEngine();
		~GraphicsEngine();

		void Initialize(InitalizeInfomation info) override;

		void Render() override;

		void Finalize() override;

	private:
		ID3D11Device* _device = nullptr;
		ID3D11DeviceContext* _deviceContext = nullptr;
		IDXGISwapChain* _swapChain = nullptr;
		ID3D11RenderTargetView* _renderTargetView = nullptr;

	};


}