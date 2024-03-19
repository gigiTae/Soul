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

		enum class Sampler
		{
			LINEAR,

			End,
		};

		RenderState();
		~RenderState();

		// State Resource 생성
		void Initialize(const std::shared_ptr<Device>& device);
		
		// State Resource 해제 
		void Finalize();

		// Get RasterizerState State 
		ID3D11RasterizerState* GetRasterizerState(Rasterizer state)const ;

		// Get SamplerState
		ID3D11SamplerState** GetSamplerState(Sampler state);

		void BindRasterizerState(Rasterizer stata)const;

		void BindSamplerState(UINT slot, Sampler state);

	private:
		std::shared_ptr<Device> _device;

		std::array<ID3D11RasterizerState*, static_cast<size_t>(Rasterizer::End)> _rasterizerStates;
		std::array<ID3D11SamplerState*, static_cast<size_t>(Sampler::End)> _samplerStates;

	};
}