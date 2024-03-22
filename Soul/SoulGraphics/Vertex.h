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
		static constexpr UINT PosColorArraySize = 2;
		static constexpr UINT PosTexArraySize = 2;
		static constexpr UINT MeshVertexArraySize = 4;
		static constexpr UINT SkinnedVertexArraySize = 6;

		static const D3D11_INPUT_ELEMENT_DESC PosColor[PosColorArraySize];
		static const D3D11_INPUT_ELEMENT_DESC PosTex[PosTexArraySize];
		static const D3D11_INPUT_ELEMENT_DESC MeshVertex[MeshVertexArraySize];
		static const D3D11_INPUT_ELEMENT_DESC SkinnedVertex[SkinnedVertexArraySize];
	};
}