#include "Pane.h"
#include "..\core\Engine.h"

BITMAPINFO Pane::m_Info;
HBITMAP Pane::m_Section;
void* Pane::m_Memory;

Pane::Pane()
{
	WNDCLASSEX windowClass;
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
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
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, NULL, NULL, GetModuleHandle(NULL), NULL);

	if (!m_Handle)
	{
		MessageBox(NULL, "CreateWindowEx failed", "Error", NULL);
		return;
	}
}

Pane::~Pane()
{

}

void Pane::ResizeSection(int width, int height)
{
	if (m_Section)
		DeleteObject(m_Section);

	m_Info;
	m_Info.bmiHeader.biSize = sizeof(m_Info.bmiHeader);
	m_Info.bmiHeader.biWidth = width;
	m_Info.bmiHeader.biHeight = height;
	m_Info.bmiHeader.biPlanes = 1;
	m_Info.bmiHeader.biBitCount = 32;
	m_Info.bmiHeader.biCompression = BI_RGB;

	m_Section = CreateDIBSection(CreateCompatibleDC(0), &m_Info, DIB_RGB_COLORS, &m_Memory, NULL, NULL);
}

void Pane::Show()
{
	if(!ShowWindowAsync(m_Handle, SW_SHOWDEFAULT))
		MessageBox(NULL, "Show window async failed", "Error", NULL);

	MSG message;
	while (GetMessage(&message, NULL, NULL, NULL) > 0 && Engine::GetInstance()->CurrentState() == EngineState::started)
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

void Pane::UpdatePane(HDC deviceContext, int x, int y, int width, int height)
{
	StretchDIBits(deviceContext, x, y, width, height, x, y, width, height, m_Memory, &m_Info, DIB_RGB_COLORS, SRCCOPY);
}

LRESULT CALLBACK Pane::WindowCallBack(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_SIZE:
		{
			RECT clientRect;
			GetClientRect(handle, &clientRect);
			ResizeSection(clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
			break;
		}
		case WM_PAINT:
		{
			PAINTSTRUCT paint;
			HDC deviceContext = BeginPaint(handle, &paint);
			int x = paint.rcPaint.left;
			int y = paint.rcPaint.top;
			UpdatePane(deviceContext, x, y, paint.rcPaint.right - x, paint.rcPaint.bottom - y);
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