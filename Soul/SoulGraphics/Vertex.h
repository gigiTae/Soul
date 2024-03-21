#pragma once


namespace SoulGraphics::Vertex
{
	enum class Type
	{
		PosColor,
		PosTex,
		PosNormal,
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

	struct PosNormal
	{
		DirectX::SimpleMath::Vector3 pos;
		DirectX::SimpleMath::Vector3 normal;
	};

	struct MeshVertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT2 tex;
		DirectX::XMFLOAT3 tangent;
	};

	struct SkinnedVertex
	{
		SM::Vector3 pos;
		SM::Vector3 normal;
		SM::Vector2 tex;
		SM::Vector3 tangent;
		SM::Vector3 boneWeight;
		UINT32 boneIndices[4];

		void AddBoneDate(UINT boneIndex, float weight);
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