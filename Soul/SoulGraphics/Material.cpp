#include "SoulGraphicsPCH.h"
#include "Material.h"
#include "Texture.h"

SoulGraphics::Material::Material()
	:_textures{}
{

}

SoulGraphics::Material::~Material()
{

}

void SoulGraphics::Material::BindTexture(UINT slot, Type type)
{
	_textures[static_cast<int>(type)]->
		BindTexture(slot);
}
