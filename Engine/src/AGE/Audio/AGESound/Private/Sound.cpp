#include "AGEpch.hpp"
#include "Audio/AGESound/Public/Sound.h"
#include "Audio/AGESound/Public/AGEAudio.h"
#include "Audio/Fmod/Public/FmodEngine.h"
#include "Statics/Public/Statics.h"
#include "AL/al.h"
#include "AL/alext.h"
//#include "alc/alcmain.h"
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
	/**
 *  @brief Constructs an AudioSource object with the given parameters.
 *  
 *  This constructor initializes a new instance of the AudioSource class with the provided handle, loaded status and total duration.
 *  
 *  @param Handle The buffer handle for the audio source.
 *  @param Loaded A boolean indicating whether or not the audio data is loaded.
 *  @param Length The total duration of the audio in seconds.
 */
AudioSource::AudioSource(uint32_t Handle, bool Loaded, double Length)
		: m_BufferHandle(Handle), bLoaded(Loaded), m_TotalDuration(Length)
	{
	}

	/**
 * @brief Constructs an AudioSource object with the given parameters.
 * 
 * This function constructs a new instance of the AudioSource class, initializing its member variables to the provided values.
 * 
 * @param Handle A uint32_t representing the buffer handle for the audio data.
 * @param Loaded A bool indicating whether or not the audio data is loaded.
 * @param Length A double representing the total duration of the audio in seconds.
 * @param Data A vector of chars containing the raw sound data.
 */
AudioSource::AudioSource(uint32_t Handle, bool Loaded, double Length, std::vector<char> Data)
		: m_BufferHandle(Handle), bLoaded(Loaded), m_TotalDuration(Length), m_SoundData(Data)
	{
	}

	//AGE::AudioSource::~AudioSource()
	//{
	//}
	/**
 * @brief Sets the position of the audio source in 3D space.
 *
 * This function sets the position of the audio source to a specified Vector3 value P. The actual OpenAL call is made within this function, setting the position of the audio source represented by m_SourceHandle using the alSourcefv function with AL_POSITION as the parameter and &m_Position.x as the argument.
 * 
 * @param P A const reference to a Vector3 object representing the new position for the audio source.
 */
void AudioSource::SetPosition(const Vector3& P)
	{
		m_Position = P;
		alSourcefv(m_SourceHandle, AL_POSITION, &m_Position.x);
	}
	/**
 * @brief Sets the position of the audio source in 3D space.
 *
 * This function sets the position of the audio source using three floating-point values (x, y, z). The new position is then applied to the OpenAL source handle associated with this AudioSource instance.
 *
 * @param x The x coordinate of the new position.
 * @param y The y coordinate of the new position.
 * @param z The z coordinate of the new position.
 */
void AudioSource::SetPosition(float x, float y, float z)
	{
		m_Position.x = x;
		m_Position.y = y;
		m_Position.z = z;
		alSourcefv(m_SourceHandle, AL_POSITION, &m_Position.x);
	}
	/**
 * @brief Set the gain of the audio source.
 *
 * This function sets the gain value for the audio source represented by m_SourceHandle. The gain is a float value that represents the volume level of the audio source. 
 * It also updates the OpenAL source with the new Gain value using alSourcef().
 *
 * @param Gain A float representing the desired gain level. Must be between 0.0 and 1.0.
 */
void AudioSource::SetGain(float Gain)
	{
		m_Gain = Gain;

		alSourcef(m_SourceHandle, AL_GAIN, Gain);
	}
	/**
 * @brief This function sets the pitch of an audio source.
 *
 * The function takes a float value as input and assigns it to the member variable m_Pitch. 
 * It then uses this value to set the 'AL_PITCH' property of the OpenAL source represented by m_SourceHandle.
 * This change in pitch will affect how the audio is played back, affecting its speed or tempo.
 *
 * @param Pitch The new pitch value for the audio source.
 */
void AudioSource::SetPitch(float Pitch)
	{
		m_Pitch = Pitch;
		alSourcef(m_SourceHandle, AL_PITCH, Pitch);
	}
	/**
 * @brief Sets the spatialization state of this audio source.
 *
 * This function sets the spatialization state of the audio source, enabling or disabling spatialization based on the input parameter. 
 * It also sets the distance model to AL_INVERSE_DISTANCE_CLAMPED for proper spatialization behavior.
 *
 * @param Spatial The new spatialization state. If true, spatialization is enabled; if false, it's disabled.
 */
void AudioSource::SetSpatial(bool Spatial)
	{
		bSpatial = Spatial;
		alSourcei(m_SourceHandle, AL_SOURCE_SPATIALIZE_SOFT, Spatial ? AL_TRUE : AL_FALSE);
		alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
	}
	/**
 * @brief Sets the looping state of the audio source.
 *
 * This function sets the looping state of the audio source by modifying the 'bLoop' member variable and the OpenAL source handle. 
 * If Loop is true, the AL_LOOPING parameter will be set to AL_TRUE indicating that the audio should continue playing indefinitely when it reaches the end. 
 * If Loop is false, the AL_LOOPING parameter will be set to AL_FALSE signifying that the audio should stop playing once it has reached the end.
 *
 * @param Loop A boolean value indicating whether or not the source should loop.
 */
void AudioSource::SetLoop(bool Loop)
	{
		bLoop = Loop;

		alSourcei(m_SourceHandle, AL_LOOPING, Loop ? AL_TRUE : AL_FALSE);

	}
	/**
 * @brief This function returns the total duration of the audio source in minutes and seconds.
 * @return A pair where the first element is the number of minutes, and the second element is the number of seconds.
 */
std::pair<uint32_t, uint32_t> AudioSource::GetLengthMinutesAndSeconds() const
	{
		return { (uint32_t)(m_TotalDuration / 60.f), (uint32_t)m_TotalDuration % 60 };
	}
	/**
 * @brief Loads an audio source from a file and sets its spatial property.
 * 
 * This function loads an audio source from the specified file path using AGESound::LoadAudioSource(). It then sets the spatial property of the loaded audio source to the provided value. The file path is also stored in the resultant AudioSource object for future reference.
 * 
 * @param File A string representing the file path of the audio file to load.
 * @param Spatial A boolean indicating whether or not the audio should be spatialized.
 * 
 * @return An AudioSource object loaded from the specified file and with its spatial property set according to the provided value.
 */
AudioSource AudioSource::LoadFromFile(const std::string& File, bool Spatial)
	{
		AudioSource Result = AGESound::LoadAudioSource(File);
		Result.SetSpatial(Spatial);
		Result.m_FilePath = File;
		return Result;
	}
}