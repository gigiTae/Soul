#pragma once

namespace SoulGraphics
{
	class Device;

	class RenderTarget
	{
	public:
		enum class Type
		{
			Default,
			Second,

			EndCount,
		};

	public:
		RenderTarget();
		~RenderTarget();

		void Initialize(const std::shared_ptr<Device>& device, UINT width, UINT height);

		void ClearRenderTargetView(Type type);

		void SetRenderTargetView(Type type);

	private:
		std::shared_ptr<Device> _device;

		std::array<ID3D11RenderTargetView*, static_cast<size_t>(Type::EndCount)> _renderTargetViews;	// ·£´õ Å¸°Ù ºä

	};

}