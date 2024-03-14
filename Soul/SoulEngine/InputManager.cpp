#include "SoulEnginePCH.h"
#include "InputManager.h"


SoulEngine::InputManager::InputManager()
	:_matchVK{
		VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,
		'Q','W','E','R','T','Y','U','O','P',
		'A','S','D','F','G','H','J','K','L',
		'Z','X','C','V','B','N','M',

		VK_MENU, // ALT,
		VK_CONTROL, // CTRL,
		VK_LSHIFT, // LSHIFT,
		VK_SPACE, // SPACE,
		VK_RETURN, // ENTER,
		VK_ESCAPE, // ESC,
		VK_TAB, //TAB

		VK_LBUTTON, // LBTN
		VK_RBUTTON, // RBTN

		VK_F1, // F1
		VK_F2, // F2
		VK_F3, // F3
		VK_F4, // F4
		VK_F5, // F5
        VK_F6, // F6
        VK_F7, // F7
        VK_F8, // F8

       VK_INSERT, //        Ins,
       VK_DELETE,//Del,
       VK_HOME,//Home,
      VK_END,   //End,
      VK_PRIOR,//PgUp,
       VK_NEXT,//PgDn,

	}
	, _keyInfomations{}
	, _hwnd(nullptr)
	, currentMousePosition{}
	, prevMousePosition{}
	, deltaMousePosition{} 
	,_isActive(true)
{
}

SoulEngine::InputManager::~InputManager()
{
}

void SoulEngine::InputManager::Initalize(HWND main)
{
    _hwnd = main;
}

void SoulEngine::InputManager::Update(float dt)
{

    HWND hWnd = GetFocus();

    // ���� ��Ŀ�����϶�
    if (nullptr != hWnd && _isActive)
    {
        for (int i = 0; i < static_cast<int>(Key::Last); ++i)
        {
            if (GetAsyncKeyState(_matchVK[i]) & 0x8000)
            {
                if (_keyInfomations[i].prevPush)
                {
                    _keyInfomations[i].state = KeyState::Hold;
                }
                else
                {
                    _keyInfomations[i].state = KeyState::Tap;
                }
                _keyInfomations[i].prevPush = true;
            }
            else
            {
                if (_keyInfomations[i].prevPush)
                {
                    _keyInfomations[i].state = KeyState::Away;
                }
                else
                {
                    _keyInfomations[i].state = KeyState::None;
                }
                _keyInfomations[i].prevPush = false;
            }
        }

        prevMousePosition = currentMousePosition;

        // Mouse ��ġ ���
        GetCursorPos(&currentMousePosition);

        // ��ũ�� ��ǥ���� ���콺 ��ġ
        ScreenToClient(_hwnd, &currentMousePosition);

        // ���콺�� �̹������ӿ� �󸶳� ����������
        deltaMousePosition = { currentMousePosition.x - prevMousePosition.x,
                               currentMousePosition.y - prevMousePosition.y };
    }
    // ��Ŀ�������Ǿ� ����ó�� ����
    else
    {
        for (int i = 0; i < static_cast<int>(Key::Last); ++i)
        {
            _keyInfomations[i].prevPush = false;
            if (KeyState::Tap == _keyInfomations[i].state ||
                KeyState::Hold == _keyInfomations[i].state)
            {
                _keyInfomations[i].state = KeyState::Away;
            }
            else if (KeyState::Away == _keyInfomations[i].state)
            {
                _keyInfomations[i].state = KeyState::None;
            }
        }
    }
}

void SoulEngine::InputManager::Finalize()
{
}


KeyState SoulEngine::InputManager::GetKeyState(Key key) const
{
    return _keyInfomations[static_cast<int>(key)].state;
}

bool SoulEngine::InputManager::IsKeyState(const Key& _key,
                                               const KeyState& _state) const
{
    if (_state == GetKeyState(_key))
    {
        return true;
    }

    return false;
}

RECT SoulEngine::InputManager::GetScreenRect() const
{
    RECT rect;

    GetWindowRect(_hwnd, &rect);

    return rect;
}
