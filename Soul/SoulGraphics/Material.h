#pragma once

namespace SoulGraphics
{
	class Texture;

	class Material
	{
	public:
		enum class Type
		{
			BaseColor,
			Normal,

			End,
		};

		Material();
		~Material();

		void BindTexture(UINT slot, Type type);

	private:
		std::array < std::shared_ptr<Texture>, static_cast<size_t>(Type::End)> _textures;
	};


}