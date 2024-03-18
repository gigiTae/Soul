#include "SoulGraphicsPCH.h"
#include "Shader.h"
#include "ResourceManager.h"
#include "Device.h"

SoulGraphics::Shader::Shader(ResourceManager* resMger)
	:Resource(resMger),
	_inputLayout(nullptr),
	_vertexShader(nullptr),
	_pixelShader(nullptr)
{}

SoulGraphics::Shader::~Shader()
{}

void SoulGraphics::Shader::LoadShader(const std::wstring& vsPath, const std::wstring& psPath)
{
	auto dxDevice = GetResourceManager()->GetDevice()->GetDevice();

	ID3D10Blob* vertexShaderBuffer = nullptr;	// ���� ���̴� �ڵ尡 ����� ����.
	HR_T(CompileShaderFromFile(vsPath.c_str(), "main", "vs_4_0", &vertexShaderBuffer));

	// InputLayout ����
	HR_T(dxDevice->CreateInputLayout(Vertex::InputLayoutDesc::meshVertex,
		ARRAYSIZE(Vertex::InputLayoutDesc::meshVertex),
		vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &_inputLayout));

	// VS����
	HR_T(dxDevice->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(), NULL, &_vertexShader));

	SAFE_RELEASE(vertexShaderBuffer);

	// PS����
	ID3D10Blob* pixelShaderBuffer = nullptr;	// �ȼ� ���̴� �ڵ尡 ����� ����.
	HR_T(CompileShaderFromFile(psPath.c_str(), "main", "ps_5_0", &pixelShaderBuffer));
	HR_T(dxDevice->CreatePixelShader(
		pixelShaderBuffer->GetBufferPointer(),
		pixelShaderBuffer->GetBufferSize(), NULL, &_pixelShader));
	SAFE_RELEASE(pixelShaderBuffer);

}
