#include "Pane.h"
#include "..\core\Engine.h"
#include <Xinput.h>
#include <dsound.h>

#define Pi32 3.14159265359f




LPDIRECTSOUNDBUFFER m_SecondaryBuffer;
//SoundOutput soundOutput;
bool SoundIsPlaying;


Pane::Pane()
{
	m_Buffer = new PaneBuffer();
	WNDCLASSEX windowClass;
	ResizeSection(1920, 1080);
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WindowCallBack;
	windowClass.cbClsExtra = NULL;
	windowClass.cbWndExtra = NULL;
	windowClass.hInstance = GetModuleHandle(NULL);
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = NULL;
	windowClass.lpszMenuName = "CloverEngineWindowMenu";
	windowClass.lpszClassName = "CloverEngineWindowClass";
	windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&windowClass))
	{
		MessageBox(NULL, "Register class failed", "Error", NULL);
		return;
	}

	m_Handle = CreateWindowEx(0, windowClass.lpszClassName, "Clover engine", 
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, NULL, NULL, GetModuleHandle(NULL), this);

	if (!m_Handle)
	{
		MessageBox(NULL, "CreateWindowEx failed", "Error", NULL);
		return;
	}
}

Pane::~Pane()
{

}

void Pane::InitSound(INT32 bufferSize, INT32 samplesPerSecond)
{
	LPDIRECTSOUND directSound;
	WAVEFORMATEX format = {};
	format.wFormatTag = WAVE_FORMAT_PCM;
	format.nChannels = 2;
	format.nSamplesPerSec = samplesPerSecond;
	format.wBitsPerSample = 16;
	format.nBlockAlign = (format.nChannels* format.wBitsPerSample) / 8;
	format.nAvgBytesPerSec = format.nSamplesPerSec * format.nBlockAlign;
	format.cbSize = 0;

	if (SUCCEEDED(DirectSoundCreate(0, &directSound, 0)))
	{
		if(SUCCEEDED(directSound->SetCooperativeLevel(m_Handle, DSSCL_PRIORITY)))
		{
			DSBUFFERDESC bufferDescription = {};
			bufferDescription.dwSize = sizeof(bufferDescription);
			bufferDescription.dwFlags = DSBCAPS_PRIMARYBUFFER;

			LPDIRECTSOUNDBUFFER primaryBuffer;
			if (SUCCEEDED(directSound->CreateSoundBuffer(&bufferDescription, &primaryBuffer, 0)))
			{
				if (SUCCEEDED(primaryBuffer->SetFormat(&format)))
				{
					
				};
			}

			DSBUFFERDESC secondaryBufferDescription = {};
			secondaryBufferDescription.dwSize = sizeof(secondaryBufferDescription);
			secondaryBufferDescription.dwFlags = 0;
			secondaryBufferDescription.dwBufferBytes = bufferSize;
			secondaryBufferDescription.lpwfxFormat = &format;
			m_SecondaryBuffer;
			if (SUCCEEDED(directSound->CreateSoundBuffer(&secondaryBufferDescription, &m_SecondaryBuffer, 0)))
			{
				
			}
		}
	}

}

void Pane::RenderBackground(int xOffset, int yOffset)
{
	static uint8_t red = 0;
	static int op = 1;

	int width = m_Buffer->Width();
	int height = m_Buffer->Height();
	int pitch = width * m_Buffer->BytesPerPixel();
	uint8_t * row = (uint8_t *)m_Buffer->Memory();
	uint32_t* pixel = (uint32_t *)row;
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{	
			if (x >= width / (double)20 * 10 && x <= width / (double)20 * 11 && y >= height / (double)8 * 3 && y <= height / (double)8 * 4)
			{
				*pixel++ = (255-red << 16) | (0 << 8) | 0;
			}
			else
			{
				uint8_t blue = (y / (double)height * 255) + yOffset - 127;
				uint8_t green = 127 + yOffset;

				*pixel++ = (red << 16) | (green << 8) | blue;
			}
		}

		row += pitch;
	}
	if ((red == 255 && op == 1) || (red == 0 && op == -1))
		op = -op;
	red += op;
}

void Pane::ResizeSection(int width, int height)
{
	if (m_Buffer->Memory())
		VirtualFree(m_Buffer->Memory(), 0, MEM_RELEASE);

	m_Buffer->Height(height);
	m_Buffer->Width(width);
	m_Buffer->BytesPerPixel(4);
	m_Buffer->BitmapInfo()->bmiHeader.biSize = sizeof(m_Buffer->BitmapInfo()->bmiHeader);
	m_Buffer->BitmapInfo()->bmiHeader.biWidth = m_Buffer->Width();
	m_Buffer->BitmapInfo()->bmiHeader.biHeight = -m_Buffer->Height();
	m_Buffer->BitmapInfo()->bmiHeader.biPlanes = 1;
	m_Buffer->BitmapInfo()->bmiHeader.biBitCount = 32;
	m_Buffer->BitmapInfo()->bmiHeader.biCompression = BI_RGB;

	m_Buffer->Memory(VirtualAlloc(NULL, m_Buffer->Width() * m_Buffer->Height() * m_Buffer->BytesPerPixel(), MEM_COMMIT, PAGE_READWRITE));
}


void Pane::FillSoundBuffer(SoundOutput* output, DWORD ByteToLock, DWORD BytesToWrite)
{
	VOID* region1;
	DWORD region1Size;
	VOID* region2;
	DWORD region2Size;

	if (!SoundIsPlaying && SUCCEEDED(m_SecondaryBuffer->Lock(ByteToLock, BytesToWrite, &region1, &region1Size, &region2, &region2Size, 0)))
	{

		DWORD region1SampleCount = region1Size / output->bytesPerSample;
		INT16* sampleout = (INT16*)region1;
		for (DWORD sampleIndex = 0; sampleIndex < region1SampleCount; ++sampleIndex)
		{

			float t = 2.0f*Pi32*(float)output->runningSampleIndex / (float)output->wavePeriod;
			float sineValue = sinf(t);
			INT16 SampleValue = (INT16)(sineValue * output->toneVolume);
			*sampleout++ = SampleValue;
			*sampleout++ = SampleValue;
			++output->runningSampleIndex;
		}

		DWORD region2SampleCount = region2Size / output->bytesPerSample;
		sampleout = (INT16*)region2;
		for (DWORD sampleIndex = 0; sampleIndex < region2SampleCount; ++sampleIndex)
		{
			float t = 2.0f*Pi32*(float)output->runningSampleIndex / (float)output->wavePeriod;
			float sineValue = sinf(t);
			INT16 SampleValue = (INT16)(sineValue * output->toneVolume);
			*sampleout++ = SampleValue;
			*sampleout++ = SampleValue;
			++output->runningSampleIndex;
		}

		m_SecondaryBuffer->Unlock(region1, region1Size, region2, region2Size);
	}
}

void Pane::Show()
{
	if(!ShowWindowAsync(m_Handle, SW_SHOWDEFAULT))
		MessageBox(NULL, "Show window async failed", "Error", NULL);


	int xOffset = 0;
	int yOffset = 0;

	//int samplesPerSecond = 48000;
	//int toneHz = 256;
	//int toneVolume = 3000;
	//UINT32 runningSampleIndex = 0;
	//int wavePeriod = samplesPerSecond / toneHz;
	////int halfSquareWavePeriod = squareWavePeriod / 2;
	//int bytesPerSample = sizeof(INT16) * 2;
	//int SecondaryBufferSize = samplesPerSecond * bytesPerSample;
	////int squareWaveCounter = 0;
	
	SoundOutput soundOutput = {};
	soundOutput.samplesPerSecond = 48000;
	soundOutput.toneHz = 256;
	soundOutput.toneVolume = 3000;
	soundOutput.runningSampleIndex = 0;
	soundOutput.wavePeriod = soundOutput.samplesPerSecond / soundOutput.toneHz;
	//int halfSquareWavePeriod = squareWavePeriod / 2;
	soundOutput.bytesPerSample = sizeof(INT16) * 2;
	soundOutput.SecondaryBufferSize = soundOutput.samplesPerSecond * soundOutput.bytesPerSample;
	//SoundIsPlaying = false;
	InitSound(soundOutput.samplesPerSecond, soundOutput.SecondaryBufferSize);
	FillSoundBuffer(&soundOutput, 0, soundOutput.SecondaryBufferSize);
	m_SecondaryBuffer->Play(0, 0, DSBPLAY_LOOPING);

	while (Engine::GetInstance()->CurrentState() == EngineState::started)
	{
		MSG message;
		while(PeekMessage(&message, 0,0,0,PM_REMOVE))
		{
			if (message.message == WM_QUIT)
				Engine::GetInstance()->Stop();
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		//TODO : Add to new class for input management
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

				if (buttonA) yOffset += 2;
				if (buttonB) yOffset -= 2;

				XINPUT_VIBRATION vibration;
				vibration.wLeftMotorSpeed = 0;
				vibration.wRightMotorSpeed = 0;
				if (leftShoulder) vibration.wLeftMotorSpeed = 30000;
				if (rightShoulder) vibration.wRightMotorSpeed = 30000;

				XInputSetState(i, &vibration);

				uint8_t leftTrigger = pad->bLeftTrigger;
				uint8_t rightTrigger = pad->bRightTrigger;
				uint16_t leftThumbX = pad->sThumbLX;
				uint16_t leftThumbY = pad->sThumbLY;
				uint16_t rightThumbX = pad->sThumbRX;
				uint16_t rightThumbY = pad->sThumbRY;
			}
		}
		
		RenderBackground(xOffset,yOffset);

		//TODO : Refactor
		DWORD playCursor;
		DWORD writeCursor;
		if (SUCCEEDED(m_SecondaryBuffer->GetCurrentPosition(&playCursor,&writeCursor)))
		{
			DWORD byteToLock = soundOutput.runningSampleIndex * soundOutput.bytesPerSample % soundOutput.SecondaryBufferSize;
			DWORD BytesToWrite;
			if (byteToLock == playCursor)
			{
				BytesToWrite = 0;
			}
			else if (byteToLock > playCursor)
			{
				BytesToWrite = (soundOutput.SecondaryBufferSize - byteToLock);
				BytesToWrite += playCursor;
			}
			else
			{
				BytesToWrite = playCursor - byteToLock;
			}
			FillSoundBuffer(&soundOutput, byteToLock, BytesToWrite);
		}

		RECT clientRect;
		GetClientRect(m_Handle, &clientRect);
		HDC deviceContext = GetDC(m_Handle);
		DisplayPaneBuffer(deviceContext, clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
		ReleaseDC(m_Handle, deviceContext);

		++xOffset;
	}
}

void Pane::DisplayPaneBuffer(HDC deviceContext, int width, int height)
{
	StretchDIBits(deviceContext, 0, 0, width, height, 0, 0, m_Buffer->Width(), m_Buffer->Height(), m_Buffer->Memory(), m_Buffer->BitmapInfo(), DIB_RGB_COLORS, SRCCOPY);
}

LRESULT Pane::PaneCallBack(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{//TODO : Add to new class for input management
		case WM_KEYUP:
		{
			uint32_t keyCode = wParam;
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
		case WM_PAINT:
		{
			PAINTSTRUCT paint;
			HDC deviceContext = BeginPaint(handle, &paint);
			DisplayPaneBuffer(deviceContext, paint.rcPaint.right - paint.rcPaint.left, paint.rcPaint.bottom - paint.rcPaint.top);
			EndPaint(handle, &paint);
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		case WM_CLOSE:
		{
			Engine::GetInstance()->Stop();
			break;
		}
	}
	return DefWindowProc(handle, message, wParam, lParam);
}

LRESULT CALLBACK Pane::WindowCallBack(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (WM_NCCREATE == message)
	{
		SetWindowLongPtr(handle, GWLP_USERDATA, (LONG_PTR)((CREATESTRUCT*)lParam)->lpCreateParams);
		return TRUE;
	}

	return ((Pane*)GetWindowLongPtr(handle, GWLP_USERDATA))->PaneCallBack(handle, message, wParam, lParam);
}