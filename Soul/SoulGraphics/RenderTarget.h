#pragma once

namespace SoulGraphics
{
	class Device;

	class RenderTarget
	{
	public:
		enum class RenderTargetView
		{
			First,
			Second,

			End,
		}; 

	public:
		RenderTarget();
		~RenderTarget();

		void Initialize(const std::shared_ptr<Device>& device, UINT width, UINT height);

		void Finalize();

		void Clear(RenderTargetView type);

		void SetRenderTargetView(RenderTargetView type);

	private:
		std::shared_ptr<Device> _device;
		std::array<ID3D11RenderTargetView*, static_cast<size_t>(RenderTargetView::End)> _renderTargetViews;	// ·£´õ Å¸°Ù ºä
		ID3D11DepthStencilView* _depthStencilView;
	};

}