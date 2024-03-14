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

		void Load(const std::wstring& vertex, const std::wstring& pixel, Vertex::Type type);

		template <typename Vertex>
		void Load(const std::wstring& vertex, const std::wstring& pixel);

		ID3D11VertexShader* GetVertexShader() { return _vertexShader; }
		ID3D11PixelShader* GetPixelShader() { return _pixelShader; }
		ID3D11InputLayout* GetInputLayout() { return _inputLayout; }

	private:
		ID3D11VertexShader* _vertexShader;
		ID3D11PixelShader* _pixelShader;
		ID3D11InputLayout* _inputLayout;
	};

	template <typename Vertex>
	void SoulGraphics::Shader::Load(const std::wstring& vertex, const std::wstring& pixel)
	{

	}

}
