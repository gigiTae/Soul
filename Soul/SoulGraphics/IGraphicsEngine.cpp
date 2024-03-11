#include "SoulGraphicsPCH.h"
#include "IGraphicsEngine.h"
#include "GraphicsEngine.h"

SoulGraphics::IGraphicsEngine* SoulGraphics::Exporter::MakeGrapicsEngine()
{
	assert(!_graphicsEngnie);
	_graphicsEngnie = new GraphicsEngine();
	return _graphicsEngnie;
}

void SoulGraphics::Exporter::DestroyGrapicsEngnie()
{
	assert(_graphicsEngnie);
	delete _graphicsEngnie;
	_graphicsEngnie = nullptr;
}
