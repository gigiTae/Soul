#include "Application.h"

Application::Application()
	:_engine(nullptr),_type()
	,_hwnd()
{}

Application::~Application()
{}


void Application::Initialize(HINSTANCE hInstance, EngineType type)
{
	_type = type;

	if (_type == EngineType::Game)
	{
		_engine = Soul::SoulExporter::MakeGameEngine();
	}
	else
	{
		_engine = Soul::SoulExporter::MakeToolEngine();
	}
	_engine->Initialize(_hwnd);

}

void Application::Process()
{
	_engine->Process();
}

void Application::Finalize()
{
	_engine->Finalize();

	Soul::SoulExporter::DestroyEngine();
	_engine = nullptr;
}

void Application::InitializeWindow(HINSTANCE hInstance)
{

}

