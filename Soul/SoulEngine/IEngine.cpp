#include "pch.h"
#include "IEngine.h"
#include <assert.h>
#include "GameEngine.h"
#include "ToolEngine.h"

SOUL_ENGNIE_API Soul::IEngine* Soul::SoulExporter::MakeGameEngine()
{
	assert(!_engine);
    
    _engine = new GameEngine();
    return _engine;
}

SOUL_ENGNIE_API Soul::IEngine* Soul::SoulExporter::MakeToolEngine()
{
	assert(!_engine);

    _engine = new ToolEngine();
    return _engine;
}

SOUL_ENGNIE_API void Soul::SoulExporter::DestroyEngine()
{
    assert(_engine);

    delete _engine;
}

Soul::IEngine* Soul::SoulExporter::_engine =nullptr;
