#pragma once

#include "IGraphicsEngine.h"

namespace SoulGraphics
{
	class ResourceManager;
	class Device;
	class RenderTarget;
	class RenderState;
	class Camera;
	class Scene;

	class GraphicsEngine : public IGraphicsEngine
	{
	public: 
		GraphicsEngine();
		~GraphicsEngine();

		void Initialize(InitalizeInfomation info) override;
		void Render() override;
		void EndRender() override;
		void Finalize() override;

		void AddMeshObject(MeshObjectInfomation info) override;

		// Caemra
		void UpdateCamera(DirectX::SimpleMath::Matrix tm) override;

		//DXDevice
		ID3D11Device* GetDevice() override;
		ID3D11DeviceContext* GetDeviceContext() override;

		ResourceManager* GetResourceManager()const { return _resourceManager.get(); }
		Camera* GetCamera()const { return _camera.get(); }

	private:
		std::unique_ptr<Scene> _scene;
		std::unique_ptr<ResourceManager> _resourceManager;
		std::unique_ptr<Camera> _camera;

		std::shared_ptr<Device> _device;
		std::shared_ptr<RenderTarget> _renderTarget;
		std::shared_ptr<RenderState> _renderState;
	};


}