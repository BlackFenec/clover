#include "Pane.h"
#include "..\core\Engine.h"

PaneBuffer Pane::m_Buffer;

Pane::Pane()
{
	WNDCLASSEX windowClass;
	m_Buffer.BitmapInfo(new BITMAPINFO());
	ResizeSection(&m_Buffer, 1920, 1080);
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

void Pane::RenderBackground(PaneBuffer* buffer, int xOffset, int yOffset)
{
	static uint8_t red = 0;
	static int op = 1;

	int pitch = buffer->Width() * buffer->BytesPerPixel();
	uint8_t * row = (uint8_t *)buffer->Memory();
	uint32_t* pixel = (uint32_t *)row;
	for (int y = 0; y < buffer->Height(); ++y)
	{
		for (int x = 0; x < buffer->Width(); ++x)
		{	
			if (x >= buffer->Width() / (double)20 * 10 && x <= buffer->Width() / (double)20 * 11 && y >= buffer->Height() / (double)8 * 3 && y <= buffer->Height() / (double)8 * 4)
			{
				*pixel++ = ((255-red << 16) | (0 << 8) | 0);
			}
			else
			{
				uint8_t blue = (y / (double)buffer->Height() * 255) + yOffset - 127;
				uint8_t green = 127 + yOffset;

				*pixel++ = ((red << 16) | (green << 8) | blue);
			}
		}

		row += pitch;
	}
	if ((red == 255 && op == 1) || (red == 0 && op == -1))
		op = -op;
	red += op;
}

void Pane::ResizeSection(PaneBuffer* buffer,int width, int height)
{
	if (buffer->Memory())
		VirtualFree(buffer->Memory(), 0, MEM_RELEASE);

	buffer->Height(height);
	buffer->Width(width);
	buffer->BytesPerPixel(4);
	buffer->BitmapInfo()->bmiHeader.biSize = sizeof(buffer->BitmapInfo()->bmiHeader);
	buffer->BitmapInfo()->bmiHeader.biWidth = buffer->Width();
	buffer->BitmapInfo()->bmiHeader.biHeight = -buffer->Height();
	buffer->BitmapInfo()->bmiHeader.biPlanes = 1;
	buffer->BitmapInfo()->bmiHeader.biBitCount = 32;
	buffer->BitmapInfo()->bmiHeader.biCompression = BI_RGB;

	buffer->Memory(VirtualAlloc(NULL, buffer->Width() * buffer->Height() * buffer->BytesPerPixel(), MEM_COMMIT, PAGE_READWRITE));

}

void Pane::Show()
{
	if(!ShowWindowAsync(m_Handle, SW_SHOWDEFAULT))
		MessageBox(NULL, "Show window async failed", "Error", NULL);

	int xOffset = 0;
	int yOffset = 0;
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
		
		RenderBackground(&m_Buffer,xOffset,yOffset);
		RECT clientRect;
		//TODO CDA : Refactor
		GetClientRect(m_Handle, &clientRect);
		HDC deviceContext = GetDC(m_Handle);
		DisplayPaneBuffer(deviceContext, clientRect, &m_Buffer,0, 0, clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
		ReleaseDC(m_Handle, deviceContext);

		++xOffset;
	}
}

void Pane::DisplayPaneBuffer(HDC deviceContext, RECT paneRect, PaneBuffer* buffer,int x, int y, int width, int height)
{
	StretchDIBits(deviceContext, 0, 0, width, height, 0, 0, buffer->Width(), buffer->Height(), buffer->Memory(), buffer->BitmapInfo(), DIB_RGB_COLORS, SRCCOPY);
}

LRESULT CALLBACK Pane::WindowCallBack(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_PAINT:
		{
			RECT clientRect;
			//TODO CDA : Refactor
			GetClientRect(handle, &clientRect);
			PAINTSTRUCT paint;
			HDC deviceContext = BeginPaint(handle, &paint);
			int x = paint.rcPaint.left;
			int y = paint.rcPaint.top;
			DisplayPaneBuffer(deviceContext, clientRect, &m_Buffer, x, y, paint.rcPaint.right - x, paint.rcPaint.bottom - y);
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