#ifndef PANE_H_
#define PANE_H_

#include <windows.h>
#include "PaneBuffer.h"

struct SoundOutput
{
	int samplesPerSecond;
	int toneHz;
	int toneVolume;
	UINT32 runningSampleIndex;
	int wavePeriod;
	int bytesPerSample;
	int SecondaryBufferSize;
};

class Pane
{
private :
	HWND m_Handle;
	PaneBuffer* m_Buffer;

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