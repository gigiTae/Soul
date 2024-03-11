#pragma once
#include "IEngine.h"


namespace Soul
{
	class GameEngine : public IEngine
	{
	public:
		GameEngine();
		~GameEngine();

		void Initialize(HWND hwnd) override;

		void Process() override;

		void Finalize() override;

	private:
		

	};


}