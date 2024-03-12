#pragma once

#include "IGraphicsEngine.h"

namespace SoulGraphics
{
	class Device;
	class RenderTarget;
	class Camera;

	class GraphicsEngine : public IGraphicsEngine
	{
	public: 
		GraphicsEngine();
		~GraphicsEngine();

		void Initialize(InitalizeInfomation info) override;

		void Render() override;

		void Finalize() override;

		ID3D11Device* GetDevice() override;
		ID3D11DeviceContext* GetDeviceContext() override;

	private:
		std::shared_ptr<Device> _device;
		std::shared_ptr<RenderTarget> _renderTarget;
		std::unique_ptr<Camera> _camera;
	};


}