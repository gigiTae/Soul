#include "Application.h"
#include <cassert>

Application::Application()
	:_engine(nullptr)
	, _type()
	, _hwnd()
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

	InitializeWindow(hInstance);

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
	const wchar_t* title = L"title";
	
	WNDCLASS wndClass{};
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	if (_type == EngineType::Game)
	{
		wndClass.lpfnWndProc = Soul::SoulExporter::WndProc;
	}
	else
	{
		wndClass.lpfnWndProc = Soul::SoulExporter::ToolWndProc;
	}

	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = title;

	RegisterClass(&wndClass);

	RECT rc{ 100,100,1920,1080 };
	
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);


	_hwnd = CreateWindow(title, title, WS_OVERLAPPEDWINDOW,
		rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top,
		NULL, NULL, hInstance, NULL);

	auto error =GetLastError();

	assert(_hwnd);

	ShowWindow(_hwnd, SW_SHOWNORMAL);
	UpdateWindow(_hwnd);

}

