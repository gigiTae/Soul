#pragma once
#include "IObject.h"

namespace SoulGraphics
{
	class Box : public IObject
	{
	public:
		Box();
		~Box();

		void Render(Device* device,
			RenderState* state,
			RenderTarget* renderTarget) override;

		void Initialize();

		DirectX::SimpleMath::Matrix GetWorldTM()const override;
		void SetWorldTM(DirectX::SimpleMath::Matrix mat) override;
		void SetViewProjTM(Camera* camera) override;
		void SetGeometryBuffer(const std::shared_ptr<GeometryBuffer>& buffer) override;
		std::shared_ptr<GeometryBuffer> GetGeometryBuffer() override;

	private:
		DirectX::SimpleMath::Matrix _worldTM;
		DirectX::SimpleMath::Matrix _viewTM;
		DirectX::SimpleMath::Matrix _projTM;

		std::shared_ptr<GeometryBuffer> _geometryBuffer;
	};

}
