#pragma once
#include "Resource.h"

#include "ConstantBufferStruct.h"

namespace SoulGraphics
{
	class ConstantBuffer :	public Resource
	{
	public:
		enum class Type
		{
			Matrix,
			Light,
	
			End,
		};

		ConstantBuffer(ResourceManager* resMgr);
		~ConstantBuffer();
		
		// 상수 버퍼 생성 
		void Initialize();

		void BindMatrixCB(const SM::Matrix& world, const SM::Matrix& view, const SM::Matrix& proj)const;
		void BindLightCB(const CB::Light& light)const;

		// 상수 버퍼 해제
		void Finalize();

	private:
		std::array<ID3D11Buffer*, static_cast<size_t>(Type::End)> _constantBuffers;
	};
}
