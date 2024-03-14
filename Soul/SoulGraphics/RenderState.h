#pragma once

namespace SoulGraphics
{
	class Device;

	class RenderState
	{
	public:
		enum class Rasterizer
		{
			Wireframe,
			Solid,

			End,
		};

		RenderState();
		~RenderState();

		void Initialize(const std::shared_ptr<Device>& device);

		void Finalize();

		ID3D11RasterizerState* GetRasterizerState(Rasterizer state);

	private:
		std::array<ID3D11RasterizerState*, static_cast<size_t>(Rasterizer::End)> _rasterizerStates;

	};
}