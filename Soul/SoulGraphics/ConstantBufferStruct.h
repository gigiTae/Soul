#pragma once

namespace  SoulGraphics::CB
{
	struct Matrix
	{
		DirectX::SimpleMath::Matrix world;
		DirectX::SimpleMath::Matrix view;
		DirectX::SimpleMath::Matrix projection;
	};

	static_assert((sizeof(Matrix) % 16) == 0,
		"Constant Buffer size must be 16-byte aligned");

	struct Light
	{
		DirectX::SimpleMath::Vector4 lightDirection;
		DirectX::SimpleMath::Vector2 lightColor;
		DirectX::SimpleMath::Vector2 pad;
	};

	static_assert((sizeof(Light) % 16) == 0,
		"Constant Buffer size must be 16-byte aligned");
}

