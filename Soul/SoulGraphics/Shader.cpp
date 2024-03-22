#include "SoulGraphicsPCH.h"
#include "Shader.h"
#include "ResourceManager.h"
#include "Device.h"

SoulGraphics::Shader::Shader(ResourceManager* resMger
	, ID3D11VertexShader* vs
	, ID3D11PixelShader* ps
	, ID3D11InputLayout* inputlayout)
	:Resource(resMger)
	,_vertexShader(vs)
	,_pixelShader(ps)
	,_inputLayout(inputlayout)
{}

SoulGraphics::Shader::~Shader()
{}

void SoulGraphics::Shader::BindShader()
{
	assert(_inputLayout || _pixelShader || _vertexShader);

	auto deviceContext = GetResourceManager()->GetDevice()->GetDXDeviceContext();

	deviceContext->IASetInputLayout(_inputLayout);
	deviceContext->VSSetShader(_vertexShader, nullptr, 0);
	deviceContext->PSSetShader(_pixelShader, nullptr, 0);
}
