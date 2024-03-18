#pragma once
#include "Resource.h"
#include "Vertex.h"

namespace SoulGraphics
{
	class Shader : public Resource
	{
	public:
		Shader(ResourceManager* resMger);
		~Shader();

		void LoadShader(const std::wstring& vsPath, const std::wstring& psPath);

		ID3D11VertexShader* GetVertexShader() { return _vertexShader; }
		ID3D11PixelShader* GetPixelShader() { return _pixelShader; }
		ID3D11InputLayout* GetInputLayout() { return _inputLayout; }

	private:
		ID3D11VertexShader* _vertexShader;
		ID3D11PixelShader* _pixelShader;
		ID3D11InputLayout* _inputLayout;
	};
}
