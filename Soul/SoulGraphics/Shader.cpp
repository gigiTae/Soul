#include "SoulGraphicsPCH.h"
#include "Shader.h"

SoulGraphics::Shader::Shader(ResourceManager* resMger)
	:Resource(resMger),
	_inputLayout(nullptr),
	_vertexShader(nullptr),
	_pixelShader(nullptr)
{}

SoulGraphics::Shader::~Shader()
{}

void SoulGraphics::Shader::Load(const std::wstring& vertex, const std::wstring& pixel, Vertex::Type type)
{
	switch (type)
	{
	case SoulGraphics::Vertex::Type::PosColor:
	{

	}
		break;
	case SoulGraphics::Vertex::Type::MeshVertex:
		break;
	case SoulGraphics::Vertex::Type::SkinnedVertex:
		break;
	default:
		break;
	}
}

