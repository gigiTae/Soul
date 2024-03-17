#pragma once


namespace SoulGraphics::Vertex
{
	enum class Type
	{
		PosColor,
		MeshVertex,
		SkinnedVertex,
	};

	struct PosColor
	{
		DirectX::SimpleMath::Vector3 pos;
		DirectX::SimpleMath::Vector4 color;
	};

	struct PosTex
	{
		DirectX::SimpleMath::Vector3 pos;
		DirectX::SimpleMath::Vector2 tex;
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
		static const D3D11_INPUT_ELEMENT_DESC posTex[2];
		static const D3D11_INPUT_ELEMENT_DESC meshVertex[4];
		static const D3D11_INPUT_ELEMENT_DESC skinnedVertex[6];
	};
}