#ifndef PANE_H_
#define PANE_H_

#include <windows.h>
#include "PaneBuffer.h"

class Pane
{
private :
	HWND m_Handle;
	PaneBuffer* m_Buffer;
	//static Pane m_Pane;

	void RenderBackground(int xOffset, int yOffset);
	void ResizeSection(int width, int height);
	void DisplayPaneBuffer(HDC deviceContext, int width, int height);
	LRESULT PaneCallBack(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
	
	static LRESULT CALLBACK WindowCallBack(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

public :
	Pane();
	virtual ~Pane();

	void Show();
};

#endif