#ifndef PANE_H_
#define PANE_H_

#include <windows.h>

class Pane
{
private :
	HWND m_Handle;

	static LRESULT CALLBACK WindowCallBack(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

public :
	Pane();
	virtual ~Pane();

	void Show();
};

#endif