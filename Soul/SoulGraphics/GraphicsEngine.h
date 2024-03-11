#pragma once

#include "IGraphicsEngine.h"

namespace SoulGraphics
{
	class GraphicsEngine : public IGraphicsEngine
	{
	public: 
		GraphicsEngine();
		~GraphicsEngine();

		void Initialize(InitalizeInfomation info) override;

		void Finalize() override;

	private:

	};


}