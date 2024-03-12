#pragma once

#include <windows.h>
#include <memory>
#include "../SoulEngine/IEngine.h"


enum class EngineType
{
	Game,
	Tool,
};

class Application
{
public:
	Application();
	~Application();

public:
	void Initialize(HINSTANCE hInstance, EngineType type);

	/// Run Application
	void Process();

	/// Á¾·á
	void Finalize();

private:
	void InitializeWindow(HINSTANCE hInstance);
private:
	Soul::IEngine* _engine;
	EngineType _type;
	HWND _hwnd;
	HINSTANCE _hInstance;
	RECT _rect;
};

