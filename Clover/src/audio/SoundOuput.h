#ifndef SOUNDOUTPUT_H_
#define SOUNDOUTPUT_H_

#include <dsound.h>
#include <math.h>

#define Pi 3.14159265359f

class SoundOutput
{
private:
	int m_BytesPerSample;
	UINT32 m_RunningSampleIndex;
	int m_SamplesPerSecond;
	LPDIRECTSOUNDBUFFER m_SecondaryBuffer;
	int m_SecondaryBufferSize;
	int m_ToneHertz;
	int m_ToneVolume;
	int m_WavePeriod;

	void FillSoundBuffer(DWORD ByteToLock, DWORD BytesToWrite);

public:
	SoundOutput(int samplesPerSecond, int toneHertz, int toneVolume);
	virtual ~SoundOutput();

	int GetBytesPerSample();
	int GetSamplesPerSecond();
	int GetSecondaryBufferSize();
	int GetToneHertz();
	void InitSound(HWND handle);
	void Play();
	void UpdateSoundBuffer();
};

#endif // ! SOUNDOUTPUT_H_