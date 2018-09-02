#include "Pane.h"
#include "..\core\Engine.h"

Pane::Pane()
{
	WNDCLASSEX windowClass;
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WindowCallBack;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = GetModuleHandle(NULL);
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = NULL;
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = "CloverEngineWindowClass";
	windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&windowClass))
	{
		MessageBox(NULL, "Register class failed", "Error", 0);
		return;
	}

	m_Handle = CreateWindowEx(0, windowClass.lpszClassName, "Clover engine", 
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, 0, 0, GetModuleHandle(NULL), 0);

	if (!m_Handle)
	{
		MessageBox(NULL, "CreateWindowEx failed", "Error", 0);
		return;
	}
}

Pane::~Pane()
{

}

void Pane::Show()
{
	if(!ShowWindowAsync(m_Handle, SW_SHOWDEFAULT))
		MessageBox(NULL, "Show window async failed", "Error", 0);

	MSG message;
	while (GetMessage(&message, NULL, 0, 0) > 0 && Engine::GetInstance()->CurrentState() == EngineState::started)
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

LRESULT CALLBACK Pane::WindowCallBack(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_PAINT:
		{
			PAINTSTRUCT paint;
			HDC deviceContext = BeginPaint(handle, &paint);
			int x = paint.rcPaint.left;
			int y = paint.rcPaint.top;
			PatBlt(deviceContext, x, y, paint.rcPaint.right - x, paint.rcPaint.bottom - y, WHITENESS);
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