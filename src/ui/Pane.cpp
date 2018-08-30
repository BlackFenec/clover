#include "Pane.h"

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
	windowClass.lpszClassName = L"CloverEngineWindowClass";
	windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&windowClass))
	{
		MessageBox(NULL, L"Register class failed", L"Error", 0);
		return;
	}

	m_Handle = CreateWindowEx(NULL, windowClass.lpszClassName, L"Clover engine", 
		WS_OVERLAPPED | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, NULL, NULL, NULL, NULL);   

	if (!m_Handle)
	{
		MessageBox(NULL, L"CreateWindowEx failed", L"Error", 0);
		return;
	}

	//TODO : I need a thread
	MSG message;
	while(GetMessage(&message, NULL, 0, 0) > 0)
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
}

Pane::~Pane()
{

}
LRESULT CALLBACK Pane::WindowCallBack(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(handle, message, wParam, lParam);
}