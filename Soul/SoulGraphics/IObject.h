#pragma once

namespace SoulGraphics
{
	class Device;
	class RenderTarget;
	class RenderState;
	class Camera;

	class GeometryBuffer;

	class IObject
	{
	public:
		virtual ~IObject(){}

		virtual void Render(Device* device,
			RenderState* state,
			RenderTarget* renderTarget) abstract;

		virtual DirectX::SimpleMath::Matrix GetWorldTM()const abstract;
		virtual void SetWorldTM(const DirectX::SimpleMath::Matrix& mat) abstract;
		virtual void SetViewProjTM(Camera* camera) abstract;

		virtual std::shared_ptr<GeometryBuffer> GetGeometryBuffer() abstract;
		virtual void SetGeometryBuffer(const std::shared_ptr<GeometryBuffer>& buffer) abstract;
	};
}
