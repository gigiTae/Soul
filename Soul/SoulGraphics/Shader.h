#pragma once
#include "Resource.h"


namespace SoulGraphics
{
	class Shader : public Resource
	{
	public:
		Shader(ResourceManager* resMger);
		~Shader();

		ID3D11VertexShader* GetVertexShader() { return _vertexShader; }
		ID3D11PixelShader* GetPixelShader() { return _pixelShader; }
		ID3D11InputLayout* GetInputLayout() { return _inputLayout; }

	private:
		ID3D11VertexShader* _vertexShader;
		ID3D11PixelShader* _pixelShader;
		ID3D11InputLayout* _inputLayout;
	};
}
