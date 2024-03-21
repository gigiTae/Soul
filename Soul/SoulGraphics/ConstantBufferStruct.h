#pragma once

namespace  SoulGraphics::CB
{
	struct Matrix
	{
		DirectX::SimpleMath::Matrix world;
		DirectX::SimpleMath::Matrix view; 
		DirectX::SimpleMath::Matrix projection;
		DirectX::SimpleMath::Matrix worldInverseTranspose;
	};

	static_assert((sizeof(Matrix) % 16) == 0,
		"Constant Buffer size must be 16-byte aligned");

	struct Light
	{
		DirectX::SimpleMath::Vector4 lightDirection[2];
		DirectX::SimpleMath::Vector4 lightColor[2];
	};

	static_assert((sizeof(Light) % 16) == 0,
		"Constant Buffer size must be 16-byte aligned");

	struct BoneMatrix
	{
		SM::Matrix bone[128];
	};

	static_assert((sizeof(BoneMatrix) % 16) == 0,
		"Constant Buffer size must be 16-byte aligned");
}

