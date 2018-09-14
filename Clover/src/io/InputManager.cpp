#include "InputManager.h"
#include "..\core\Engine.h"

InputManager InputManager::m_InputManager;

InputManager::InputManager()
{

}

InputManager::~InputManager()
{

}

void InputManager::GamepadInput(int* yOffset)
{
	for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i)
	{
		XINPUT_STATE state;
		if (XInputGetState(i, &state) == ERROR_SUCCESS)
		{
			XINPUT_GAMEPAD* pad = &state.Gamepad;

			bool up = (pad->wButtons & XINPUT_GAMEPAD_DPAD_UP);
			bool down = (pad->wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
			bool left = (pad->wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
			bool right = (pad->wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
			bool start = (pad->wButtons & XINPUT_GAMEPAD_START);
			bool back = (pad->wButtons & XINPUT_GAMEPAD_BACK);
			bool leftShoulder = (pad->wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER);
			bool rightShoulder = (pad->wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER);
			bool leftThumb = (pad->wButtons & XINPUT_GAMEPAD_LEFT_THUMB);
			bool rightThumb = (pad->wButtons & XINPUT_GAMEPAD_RIGHT_THUMB);
			bool buttonA = (pad->wButtons & XINPUT_GAMEPAD_A);
			bool buttonB = (pad->wButtons & XINPUT_GAMEPAD_B);
			bool buttonX = (pad->wButtons & XINPUT_GAMEPAD_X);
			bool buttonY = (pad->wButtons & XINPUT_GAMEPAD_Y);

			if (buttonA) 
				*yOffset += 2;
			if (buttonB) 
				*yOffset -= 2;

			XINPUT_VIBRATION vibration;
			vibration.wLeftMotorSpeed = 0;
			vibration.wRightMotorSpeed = 0;
			if (leftShoulder) vibration.wLeftMotorSpeed = 30000;
			if (rightShoulder) vibration.wRightMotorSpeed = 30000;

			XInputSetState(i, &vibration);

			UINT8 leftTrigger = pad->bLeftTrigger;
			UINT8 rightTrigger = pad->bRightTrigger;
			UINT16 leftThumbX = pad->sThumbLX;
			UINT16 leftThumbY = pad->sThumbLY;
			UINT16 rightThumbX = pad->sThumbRX;
			UINT16 rightThumbY = pad->sThumbRY;
		}
	}
}

void InputManager::KeyboardInput(UINT32 keyCode)
{
	if (keyCode == 'W')
		OutputDebugString("W");
	else if (keyCode == 'A')
		OutputDebugString("A");
	else if (keyCode == 'S')
		OutputDebugString("S");
	else if (keyCode == 'D')
		OutputDebugString("D");
	else if (keyCode == VK_SPACE)
		OutputDebugString("space");
	else if (keyCode == VK_ESCAPE)
		Engine::GetInstance()->Stop();
}