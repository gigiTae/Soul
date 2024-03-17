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

		void Initialize(Device* device);

		DirectX::SimpleMath::Matrix GetWorldTM()const override;
		void SetWorldTM(DirectX::SimpleMath::Matrix mat) override;
		void SetViewProjTM(Camera* camera) override;
		void SetGeometryBuffer(const std::shared_ptr<GeometryBuffer>& buffer) override;
		std::shared_ptr<GeometryBuffer> GetGeometryBuffer() override;

		FLOAT GetHeight() const { return _height; }
		void SetHeight(FLOAT val) { _height = val; }
		FLOAT GetWidth() const { return _width; }
		void SetWidth(FLOAT val) { _width = val; }
	private:
		DirectX::SimpleMath::Matrix _worldTM;
		DirectX::SimpleMath::Matrix _viewTM;
		DirectX::SimpleMath::Matrix _projTM;

		ID3D11InputLayout* _inputLayout;
		ID3D11PixelShader* _pixelShader;
		ID3D11VertexShader* _vertexShader;
		UINT _vertexBufferStride;
		UINT _vertexBufferOffset;

		ID3D11ShaderResourceView* _textureRV;
		ID3D11SamplerState* _samepleState;

		ID3D11Buffer* _vertexBuffer;
		ID3D11Buffer* _indexBuffer;
		UINT _indices;
		ID3D11Buffer* _constantBuffer;

		FLOAT _width;
		FLOAT _height;
	};

	struct ContantBuffer
	{
		DirectX::SimpleMath::Matrix world;
		DirectX::SimpleMath::Matrix view;
		DirectX::SimpleMath::Matrix projection;
	};

}
