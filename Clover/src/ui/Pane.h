#ifndef PANE_H_
#define PANE_H_

#include "PaneBuffer.h"
#include "..\audio\SoundOuput.h"
#include <windows.h>
#include <Xinput.h>



class Pane
{
private :
	HWND m_Handle;
	PaneBuffer* m_Buffer;
	SoundOutput* m_SoundOutput;

	void DisplayPaneBuffer(HDC deviceContext, int width, int height);
	void InitSound(INT32 bufferSize, INT32 samplesPerSecond);
	void RenderBackground(int xOffset, int yOffset);
	void ResizeSection(int width, int height);
	LRESULT PaneCallBack(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
	void FillSoundBuffer(SoundOutput* output, DWORD ByteToLock, DWORD BytesToWrite);
	
	static LRESULT CALLBACK WindowCallBack(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

public :
	Pane();
	virtual ~Pane();

	void Show();
};

#endif