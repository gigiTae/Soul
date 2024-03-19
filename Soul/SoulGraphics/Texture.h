#pragma once
#include "Resource.h"



namespace SoulGraphics
{
	class Texture : public Resource
	{
	public:
		Texture(ResourceManager* resMgr);
		~Texture();

		void LoadTexture(const std::filesystem::path& path);

		ID3D11ShaderResourceView* GetShaderResourceView()const { return _shaderResourceView; }
	
		std::wstring GetResourcePath() const { return _resourcePath; }

		void SetTexture(UINT slot);

	private:
		std::wstring _resourcePath;
		ID3D11ShaderResourceView* _shaderResourceView;
	};
}