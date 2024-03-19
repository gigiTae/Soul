#pragma once
#include "Resource.h"


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

		void SetMatrixCB(const SM::Matrix& world, const SM::Matrix& view, const SM::Matrix& proj)const;

		// 상수 버퍼 해제
		void Finalize();

	private:
		std::array<ID3D11Buffer*, static_cast<size_t>(Type::End)> _constantBuffers;
	};
}
