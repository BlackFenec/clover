#ifndef PANE_H_
#define PANE_H_

#include <windows.h>
#include "PaneBuffer.h"

class Pane
{
private :
	/*static int m_BitmapWidth;
	static int m_BitmapHeight;*/
	HWND m_Handle;
	static PaneBuffer m_Buffer;
	/*static BITMAPINFO m_Info;
	static void* m_Memory;*/

	static void RenderBackground(PaneBuffer* buffer, int xOffset, int yOffset);
	static void ResizeSection(PaneBuffer* buffer, int width, int height);
	static void DisplayPaneBuffer(HDC deviceContext, RECT paneRect, PaneBuffer* buffer,int x, int y, int width, int height);
	static LRESULT CALLBACK WindowCallBack(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

public :
	Pane();
	virtual ~Pane();

	void Show();
};

#endif