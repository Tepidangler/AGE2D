#include "AGEpch.hpp"
#include "Audio/AGESound/Public/Sound.h"
#include "Audio/AGESound/Public/AGEAudio.h"
#include "Audio/Fmod/Public/FmodEngine.h"
#include "Statics/Public/Statics.h"
//#include "AL/al.h"
//#include "AL/alext.h"
//#include "alcmain.h"
//#include "alhelpers.h"


namespace AGE
{
	AudioSource::AudioSource(const std::string& FilePath)
	{
		AudioSource Tmp = LoadFromFile(FilePath);
		this->bLoaded = Tmp.bLoaded;
		this->bLoop = Tmp.bLoop;
		this->bSpatial = Tmp.bSpatial;
		this->m_BufferHandle = Tmp.m_BufferHandle;
		this->m_FilePath = Tmp.m_FilePath;
		this->m_Gain = Tmp.m_Gain;
		this->m_Pitch = Tmp.m_Pitch;
		this->m_Position = Tmp.m_Position;
		this->m_SoundData = Tmp.m_SoundData;
		this->m_SourceHandle = Tmp.m_SourceHandle;
		this->m_TotalDuration = Tmp.m_TotalDuration;

		std::filesystem::path Path = FilePath;
		this->m_Name = Utils::EngineStatics::GetFilename(Path);

	}
	AudioSource::AudioSource(uint32_t Handle, bool Loaded, float Length)
		: m_BufferHandle(Handle), bLoaded(Loaded), m_TotalDuration(Length)
	{
	}

	AudioSource::AudioSource(uint32_t Handle, bool Loaded, float Length, std::vector<char> Data)
		: m_BufferHandle(Handle), bLoaded(Loaded), m_TotalDuration(Length), m_SoundData(Data)
	{
	}

	//AGE::AudioSource::~AudioSource()
	//{
	//}
	void AudioSource::SetPosition(const Vector3& P)
	{
		m_Position = P;
		alSourcefv(m_SourceHandle, AL_POSITION, &m_Position.x);
	}
	void AudioSource::SetPosition(float x, float y, float z)
	{
		m_Position.x = x;
		m_Position.y = y;
		m_Position.z = z;
		alSourcefv(m_SourceHandle, AL_POSITION, &m_Position.x);
	}
	void AudioSource::SetGain(float Gain)
	{
		m_Gain = Gain;

		alSourcef(m_SourceHandle, AL_GAIN, Gain);
	}
	void AudioSource::SetPitch(float Pitch)
	{
		m_Pitch = Pitch;
		alSourcef(m_SourceHandle, AL_PITCH, Pitch);
	}
	void AudioSource::SetSpatial(bool Spatial)
	{
		bSpatial = Spatial;
		alSourcei(m_SourceHandle, AL_SOURCE_SPATIALIZE_SOFT, Spatial ? AL_TRUE : AL_FALSE);
		alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
	}
	void AudioSource::SetLoop(bool Loop)
	{
		bLoop = Loop;

		alSourcei(m_SourceHandle, AL_LOOPING, Loop ? AL_TRUE : AL_FALSE);

	}
	std::pair<uint32_t, uint32_t> AudioSource::GetLengthMinutesAndSeconds() const
	{
		return { (uint32_t)(m_TotalDuration / 60.f), (uint32_t)m_TotalDuration % 60 };
	}
	AudioSource AudioSource::LoadFromFile(const std::string& File, bool Spatial)
	{
		AudioSource Result = AGESound::LoadAudioSource(File);
		Result.SetSpatial(Spatial);
		Result.m_FilePath = File;
		return Result;
	}
}