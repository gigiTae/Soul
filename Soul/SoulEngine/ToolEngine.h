#pragma once
#include "IEngine.h"

namespace Soul
{
	class ToolEngine : public IEngine
	{
	public:
		ToolEngine();
		~ToolEngine();


		void Initialize(HWND hwnd) override;

		void Process() override;

		void Finalize() override;

	private:


	};

}