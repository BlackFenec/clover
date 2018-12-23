#include "Pane.h"
#include "..\core\Engine.h"
#include "..\io\InputManager.h"

Pane::Pane()
{
	m_Buffer = new PaneBuffer();
	m_SoundOutput = new SoundOutput(48000,256,3000);
	m_Handle = NULL;

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

void Pane::RenderBackground(int xOffset, int yOffset)
{
	static UINT8 red = 0;
	static int op = 1;

	int width = m_Buffer->Width();
	int height = m_Buffer->Height();
	int pitch = width * m_Buffer->BytesPerPixel();
	UINT8 * row = (UINT8 *)m_Buffer->Memory();
	UINT32* pixel = (UINT32 *)row;
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{	
			if (x >= width / (double)20 * 10 && x <= width / (double)20 * 11 && y >= height / (double)8 * 3 && y <= height / (double)8 * 4)
			{
				*pixel++ = ((255-red) << 16) | (0 << 8) | 0;
			}
			else
			{
				UINT8 blue = (UINT8)((y / (double)height * 255) + yOffset - 127);
				UINT8 green = 127 + yOffset;

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

void Pane::Show()
{
	if(!ShowWindowAsync(m_Handle, SW_SHOWDEFAULT))
		MessageBox(NULL, "Show window async failed", "Error", NULL);

	int xOffset = 0;
	int yOffset = 0;
	
	m_SoundOutput->InitSound(m_Handle);
	m_SoundOutput->Play();

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
		InputManager::GetInstance()->GamepadInput(&yOffset);	
		RenderBackground(xOffset,yOffset);
		m_SoundOutput->UpdateSoundBuffer();

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
	{
		case WM_KEYUP:
		{
			InputManager::GetInstance()->KeyboardInput((UINT32)wParam);
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