#ifndef PANE_H_
#define PANE_H_

#include <windows.h>
#include "PaneBuffer.h"

class Pane
{
private :
	HWND m_Handle;
	PaneBuffer m_Buffer;
	static Pane m_Pane;

	static void RenderBackground(PaneBuffer* buffer, int xOffset, int yOffset);
	static void ResizeSection(PaneBuffer* buffer, int width, int height);
	static void DisplayPaneBuffer(HDC deviceContext, PaneBuffer* buffer,int x, int y, int width, int height);
	static LRESULT CALLBACK WindowCallBack(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

public :
	Pane();
	virtual ~Pane();

	static Pane* GetInstance() { return &m_Pane; }
	void Show();
};

#endif