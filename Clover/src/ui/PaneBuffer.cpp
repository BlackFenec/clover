#include "PaneBuffer.h"

PaneBuffer::PaneBuffer()
{
}

PaneBuffer::~PaneBuffer()
{
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