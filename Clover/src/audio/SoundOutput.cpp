#include "SoundOuput.h"

SoundOutput::SoundOutput(int samplesPerSecond, int toneHertz, int toneVolume) : m_SamplesPerSecond(samplesPerSecond), m_ToneHertz(toneHertz), m_ToneVolume(toneVolume)
{
	m_RunningSampleIndex = 0;
	m_WavePeriod = m_SamplesPerSecond / m_ToneHertz;
	m_BytesPerSample = sizeof(uint16_t) * 2;
	m_SecondaryBufferSize = m_SamplesPerSecond * m_BytesPerSample;
}

SoundOutput::~SoundOutput()
{

}

int SoundOutput::GetBytesPerSample()
{
	return m_BytesPerSample;
}

int SoundOutput::GetSamplesPerSecond()
{
	return m_SamplesPerSecond;
}

int SoundOutput::GetSecondaryBufferSize()
{
	return m_SecondaryBufferSize;
}

int SoundOutput::GetToneHertz()
{
	return m_ToneHertz;
}

void SoundOutput::InitSound(HWND handle)
{
	LPDIRECTSOUND directSound;
	WAVEFORMATEX format = {};
	format.wFormatTag = WAVE_FORMAT_PCM;
	format.nChannels = 2;
	format.nSamplesPerSec = m_SamplesPerSecond;
	format.wBitsPerSample = 16;
	format.nBlockAlign = (format.nChannels* format.wBitsPerSample) / 8;
	format.nAvgBytesPerSec = format.nSamplesPerSec * format.nBlockAlign;
	format.cbSize = 0;

	if (SUCCEEDED(DirectSoundCreate(0, &directSound, 0)))
	{
		if (SUCCEEDED(directSound->SetCooperativeLevel(handle, DSSCL_PRIORITY)))
		{
			DSBUFFERDESC bufferDescription = {};
			bufferDescription.dwSize = sizeof(bufferDescription);
			bufferDescription.dwFlags = DSBCAPS_PRIMARYBUFFER;

			LPDIRECTSOUNDBUFFER primaryBuffer;
			if (SUCCEEDED(directSound->CreateSoundBuffer(&bufferDescription, &primaryBuffer, 0)))
			{
				if (SUCCEEDED(primaryBuffer->SetFormat(&format)))
				{
					DSBUFFERDESC secondaryBufferDescription = {};
					secondaryBufferDescription.dwSize = sizeof(secondaryBufferDescription);
					secondaryBufferDescription.dwFlags = 0;
					secondaryBufferDescription.dwBufferBytes = m_SecondaryBufferSize;
					secondaryBufferDescription.lpwfxFormat = &format;
					if (SUCCEEDED(directSound->CreateSoundBuffer(&secondaryBufferDescription, &m_SecondaryBuffer, 0)))
					{
						this->FillSoundBuffer(0, this->GetSecondaryBufferSize());
					}
				}
			}			
		}
	}
}

void SoundOutput::FillSoundBuffer(DWORD ByteToLock, DWORD BytesToWrite)
{
	VOID* region1;
	DWORD region1Size;
	VOID* region2;
	DWORD region2Size;

	if (SUCCEEDED(m_SecondaryBuffer->Lock(ByteToLock, BytesToWrite, &region1, &region1Size, &region2, &region2Size, 0)))
	{

		DWORD region1SampleCount = region1Size / m_BytesPerSample;
		INT16* sampleout = (INT16*)region1;
		for (DWORD sampleIndex = 0; sampleIndex < region1SampleCount; ++sampleIndex)
		{

			float t = 2.0f*Pi*(float)m_RunningSampleIndex / (float)m_WavePeriod;
			float sineValue = sinf(t);
			INT16 SampleValue = (INT16)(sineValue * m_ToneVolume);
			*sampleout++ = SampleValue;
			*sampleout++ = SampleValue;
			++m_RunningSampleIndex;
		}

		DWORD region2SampleCount = region2Size / m_BytesPerSample;
		sampleout = (INT16*)region2;
		for (DWORD sampleIndex = 0; sampleIndex < region2SampleCount; ++sampleIndex)
		{
			float t = 2.0f*Pi*(float)m_RunningSampleIndex / (float)m_WavePeriod;
			float sineValue = sinf(t);
			INT16 SampleValue = (INT16)(sineValue * m_ToneVolume);
			*sampleout++ = SampleValue;
			*sampleout++ = SampleValue;
			++m_RunningSampleIndex;
		}

		m_SecondaryBuffer->Unlock(region1, region1Size, region2, region2Size);
	}
}

void SoundOutput::Play()
{
	m_SecondaryBuffer->Play(0, 0, DSBPLAY_LOOPING);
}

void SoundOutput::UpdateSoundBuffer()
{
	DWORD playCursor;
	DWORD writeCursor;
	if (SUCCEEDED(m_SecondaryBuffer->GetCurrentPosition(&playCursor, &writeCursor)))
	{
		DWORD byteToLock = ((m_RunningSampleIndex * m_BytesPerSample) % m_SecondaryBufferSize);
		DWORD BytesToWrite;
		if (byteToLock == playCursor)
		{
			BytesToWrite = 0;
		}
		else if (byteToLock > playCursor)
		{
			BytesToWrite = (m_SecondaryBufferSize - byteToLock);
			BytesToWrite += playCursor;
		}
		else
		{
			BytesToWrite = playCursor - byteToLock;
		}
		FillSoundBuffer(byteToLock, BytesToWrite);
	}
}