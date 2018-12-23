#include "PaneBuffer.h"

PaneBuffer::PaneBuffer()
{
	m_BitmapInfo = new BITMAPINFO();
	m_BytesPerPixel = 0;
	m_Height = 0;
	m_Memory = nullptr;
	m_Width = 0;
}

PaneBuffer::~PaneBuffer()
{
	delete m_BitmapInfo;
	delete m_Memory;
}

int PaneBuffer::BytesPerPixel()
{
	return m_BytesPerPixel;
}

void PaneBuffer::BytesPerPixel(int bytesPerPixel)
{
	m_BytesPerPixel = bytesPerPixel;
}

int PaneBuffer::Height()
{
	return m_Height;
}

void PaneBuffer::Height(int height)
{
	m_Height = height;
}

BITMAPINFO* PaneBuffer::BitmapInfo()
{
	return m_BitmapInfo;
}

void PaneBuffer::BitmapInfo(BITMAPINFO* bitmapInfo)
{
	m_BitmapInfo = bitmapInfo;
}

void* PaneBuffer::Memory()
{
	return m_Memory;
}

void PaneBuffer::Memory(void* memory)
{
	m_Memory = memory;
}

int PaneBuffer::Width()
{
	return m_Width;
}

void PaneBuffer::Width(int width)
{
	m_Width = width;
}