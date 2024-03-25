#pragma once

namespace SoulEngine
{
/// <summary>
/// �Է¿� ���� ó���� �ϴ� Ŭ����
/// ex) ���콺, Ű���� ���
/// </summary>
class InputManager
{
    struct KeyInfomation
    {
        KeyState state = KeyState::None;
        bool prevPush  = false;
    };
    
public:
    InputManager();
    ~InputManager();

    void Initalize(HWND main);
    void Update(float dt);

    void Finalize();

    // Ű���� Ű�� ������¸� ��ȯ
    KeyState GetKeyState(Key key) const;
    bool IsKeyState(const Key& _key, const KeyState& _state) const;

    // �̹� ������ ���콺 ��ġ
    POINT GetMousePosition() const
    {
        return currentMousePosition;
    }
    // �̹� ������ ���콺 ��ȭ��
    POINT GetDeltaMousePosition() const
    {
        return deltaMousePosition;
    }

    bool IsActive() const
    {
        return _isActive;
    }
    void SetActive(bool isActive)
    {
        _isActive = isActive;
    }

    RECT GetScreenRect() const;

private:
    HWND _hwnd; // ���� ������ �ڵ�
    KeyInfomation _keyInfomations[static_cast<size_t>(Key::Last)]; // Ű���������� ���� �迭

    const int _matchVK[static_cast<size_t>(Key::Last)]; // KEY ���� ����Ű���� ��Ī�����ִ� �迭

    POINT currentMousePosition; // ���� ������ ���콺 ��ġ
    POINT prevMousePosition;    // ���� ������ ���콺 ��ġ
    POINT deltaMousePosition;   // �̹������� ���콺 ��ȭ��

    bool _isActive; // ���� Ű�Է��� �޴���
};
} // namespace ImpEngineModule
