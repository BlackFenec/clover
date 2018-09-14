#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#include <Windows.h>
#include <Xinput.h>

class InputManager
{
private:
	static InputManager m_InputManager;
	InputManager();

public :
	virtual ~InputManager();
	static InputManager* GetInstance() { return &m_InputManager; };

	void GamepadInput(int* yOffset);
	void KeyboardInput(UINT32 keyCode);
};

#endif