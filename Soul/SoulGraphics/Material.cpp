#include "SoulGraphicsPCH.h"
#include "Material.h"
#include "Texture.h"

SoulGraphics::Material::Material(std::shared_ptr<Texture> baseColor, std::shared_ptr<Texture> normal)
	:_textures{}
{
	_textures[static_cast<size_t>(Type::BaseColor)] = baseColor;
	_textures[static_cast<size_t>(Type::Normal)] = normal;
}

SoulGraphics::Material::~Material()
{}

void SoulGraphics::Material::BindTexture(UINT slot, Type type)
{
	_textures[static_cast<int>(type)]->
		BindTexture(slot);
}
