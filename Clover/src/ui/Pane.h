#ifndef PANE_H_
#define PANE_H_

#include <windows.h>

class Pane
{
private :
	static int m_BitmapWidth;
	static int m_BitmapHeight;
	HWND m_Handle;
	static BITMAPINFO m_Info;
	static HBITMAP m_Section;
	static void* m_Memory;

	static void RenderBackground(int xOffset, int yOffset);
	static void ResizeSection(int width, int height);
	static void UpdatePane(HDC deviceContext, RECT* paneRect, int x, int y, int width, int height);
	static LRESULT CALLBACK WindowCallBack(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

public :
	Pane();
	virtual ~Pane();

	void Show();
};

#endif