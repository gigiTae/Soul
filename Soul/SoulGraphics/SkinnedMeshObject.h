#pragma once
#include "IObject.h"

namespace SoulGraphics
{
	class Shader;
	class ConstantBuffer;
	class Material;
	class Animator;

	class SkinnedMeshObject : public IObject
	{
	public:
		SkinnedMeshObject(std::shared_ptr<GeometryBuffer> gb,
			std::shared_ptr<ConstantBuffer> cb,
			std::shared_ptr<Shader> shader,
			std::shared_ptr<Material> material,
			std::shared_ptr<Animator> animator);
		~SkinnedMeshObject();

		void Render(Device* device,
			RenderState* state,
			RenderTarget* renderTarget) override;

		DirectX::SimpleMath::Matrix GetWorldTM()const override;
		void SetWorldTM(const DirectX::SimpleMath::Matrix& mat) override;
		void SetViewProjTM(Camera* camera) override;
		void SetGeometryBuffer(const std::shared_ptr<GeometryBuffer>& buffer)  override;
		std::shared_ptr<GeometryBuffer> GetGeometryBuffer() override;

	private:
		SM::Matrix _worldTM;
		SM::Matrix _viewTM;
		SM::Matrix _projTM;

		std::shared_ptr<ConstantBuffer> _constantBuffer;
		std::shared_ptr<GeometryBuffer> _geometryBuffer;
		std::shared_ptr<Shader> _shader;
		std::shared_ptr<Material> _material;
		std::shared_ptr<Animator> _animationClip;
	};
}