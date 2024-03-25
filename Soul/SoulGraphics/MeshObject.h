#pragma once
#include "IObject.h"

namespace SoulGraphics
{
	class Shader;
	class ConstantBuffer;
	class Material;

	class MeshObject : public IObject
	{
	public:
		MeshObject(std::shared_ptr<GeometryBuffer> gb,
			std::shared_ptr<ConstantBuffer> cb,
			std::shared_ptr<Shader> shader,
			std::shared_ptr<Material> material);

		~MeshObject();
		
		void Update(float dt) override;

		void Render(Device* device,
			RenderState* state,
			RenderTarget* renderTarget) override;

		DirectX::SimpleMath::Matrix GetWorldTM()const override;
		void SetWorldTM(const DirectX::SimpleMath::Matrix& mat) override;
		void SetViewProjTM(Camera* camera) override;
		void SetGeometryBuffer(const std::shared_ptr<GeometryBuffer>& buffer) override;
		std::shared_ptr<GeometryBuffer> GetGeometryBuffer() override;

	private:
		DirectX::SimpleMath::Matrix _worldTM;
		DirectX::SimpleMath::Matrix _viewTM;
		DirectX::SimpleMath::Matrix _projTM;

		std::shared_ptr<ConstantBuffer> _constantBuffer;
		std::shared_ptr<GeometryBuffer> _geometryBuffer;
		std::shared_ptr<Shader> _shader;
		std::shared_ptr<Material> _material;
	};


}