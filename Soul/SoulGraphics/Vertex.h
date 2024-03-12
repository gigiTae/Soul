#pragma once


namespace SoulGraphics::Vertex
{
	struct PosColor
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT4 color;
	};

	struct MeshVertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT2 uv;
		DirectX::XMFLOAT3 tangent;
	};

	struct SkinnedVertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT2 uv;
		DirectX::XMFLOAT3 tangent;

		DirectX::XMFLOAT3 weight;
		UINT32 boneIndices[4];
	};

	class InputLayoutDesc
	{
	public:
		static const D3D11_INPUT_ELEMENT_DESC posColor[2];
		static const D3D11_INPUT_ELEMENT_DESC meshVertex[4];
		static const D3D11_INPUT_ELEMENT_DESC skinnedVertex[6];
	};
}