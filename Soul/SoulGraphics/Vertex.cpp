#include "SoulGraphicsPCH.h"
#include "Vertex.h"

const D3D11_INPUT_ELEMENT_DESC SoulGraphics::Vertex::InputLayoutDesc::posColor[2] =
{
	{"POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
};

const D3D11_INPUT_ELEMENT_DESC SoulGraphics::Vertex::InputLayoutDesc::posTex[2] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

const D3D11_INPUT_ELEMENT_DESC SoulGraphics::Vertex::InputLayoutDesc::meshVertex[4] =
{
	{"POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TANGENT",		0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

const D3D11_INPUT_ELEMENT_DESC SoulGraphics::Vertex::InputLayoutDesc::skinnedVertex[6] =
{
	{"POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"Tangent",		0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"WEIGHT",		0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 44, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"BONEINDICES", 0, DXGI_FORMAT_R32G32B32A32_UINT, 0, 56, D3D11_INPUT_PER_VERTEX_DATA, 0}
};


void SoulGraphics::Vertex::SkinnedVertex::AddBoneDate(UINT boneIndex, float weight)
{
	
	if (boneWeight.x == 0.0f)
	{	
		boneWeight.x = weight;
		boneIndices[0] = boneIndex;
		return;
	}
	else if (boneWeight.y == 0.0f)
	{
		boneWeight.y = weight;
		boneIndices[1] = boneIndex;
		return;
	}
	else if (boneWeight.z == 0.0f)
	{
		boneWeight.z = weight;
		boneIndices[2] = boneIndex;
		return;
	}
	else
	{
		float w = 1.f - boneWeight.x - boneWeight.y - boneWeight.z;

		boneIndices[3] = boneIndex;
	}

}
