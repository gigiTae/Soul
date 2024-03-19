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
		
		// ��� ���� ���� 
		void Initialize();

		void SetMatrixCB(const SM::Matrix& world, const SM::Matrix& view, const SM::Matrix& proj)const;

		// ��� ���� ����
		void Finalize();

	private:
		std::array<ID3D11Buffer*, static_cast<size_t>(Type::End)> _constantBuffers;
	};
}
