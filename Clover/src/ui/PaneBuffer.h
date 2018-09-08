#ifndef PANEBUFFER_H_
#define PANEBUFFER_H_
#include <Windows.h>

class PaneBuffer
{
private :
	int m_BytesPerPixel;
	int m_Height;
	BITMAPINFO* m_BitmapInfo;
	void* m_Memory;
	int m_Width;
	static PaneBuffer m_PaneBuffer;

public:
	PaneBuffer();
	virtual ~PaneBuffer();

	int BytesPerPixel();
	void BytesPerPixel(int bytesPerPixel);
	int Height();
	void Height(int height);
	BITMAPINFO* BitmapInfo();
	void BitmapInfo(BITMAPINFO* bitmapInfo);
	static PaneBuffer* GetInstance() { return &m_PaneBuffer; }
	void* Memory();
	void Memory(void* memory);
	int Width();
	void Width(int width);
};
#endif // !PANEBUFFER_H_