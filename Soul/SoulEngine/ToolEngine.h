#pragma once
#include "IEngine.h"
#include "../SoulGraphics/IGraphicsEngine.h"


namespace Soul
{
	class ToolEngine : public IEngine
	{
	public:
		ToolEngine();
		~ToolEngine();

		void Initialize(WindowInfomation info) override;

		void Process() override;

		void Finalize() override;

	private:
		SoulGraphics::IGraphicsEngine* _graphicsEngine;
	};

}