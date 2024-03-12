#include "Application.h"
#include <cassert>

Application::Application()
	:_engine(nullptr)
	, _type()
	, _hwnd()
	,_hInstance()
	, _rect{}
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

	Soul::WindowInfomation info{ hInstance, _hwnd, _rect };

	_engine->Initialize(info);
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
	const wchar_t* title = L"Soul";

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

	_rect = { 100,100,1920,1080 };

	AdjustWindowRect(&_rect, WS_OVERLAPPEDWINDOW, false);


	_hwnd = CreateWindow(title, title, WS_OVERLAPPEDWINDOW,
		_rect.left, _rect.top, _rect.right - _rect.left, _rect.bottom - _rect.top,
		NULL, NULL, hInstance, NULL);

	auto error = GetLastError();

	assert(_hwnd);

	ShowWindow(_hwnd, SW_SHOWNORMAL);
	UpdateWindow(_hwnd);

}

