#include "AGEpch.hpp"

#include "Statics/Public/Statics.h"
#include "Audio/AGESound/Public/AGEAudio.h"
#include "Audio/AGESound/Public/Sound.h"
//#include "core/device.h"
//#include "alc/device.h"
//#include "common/intrusive_ptr.h"
#include "Core/Public/Log.h"

#define MINIMP3_IMPLEMENTATION
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconversion"
#pragma clang diagnostic ignored "-Wdeprecated-literal-operator"
#ifdef AG_PLATFORM_WINDOWS
#pragma clang diagnostic ignored "-Wmicrosoft-unqualified-friend"
#include "minimp3/minimp3.h"
#include "minimp3/minimp3_ex.h"
#include "core/device.h"
#include "alc/device.h"
#include "common/intrusive_ptr.h"
#else
#include "minimp3.h"
#include "minimp3_ex.h"
#include "core/device.h"
#include "alc/device.h"
#include "common/intrusive_ptr.h"
#endif
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#ifdef AG_PLATFORM_WINDOWS
#include "minimp3/minimp3.h"
#include "minimp3/minimp3_ex.h"
#include "core/device.h"
#include "alc/device.h"
#include "common/intrusive_ptr.h"
#else
#include "minimp3.h"
#include "minimp3_ex.h"
#include "core/device.h"
#include "alc/device.h"
#include "common/intrusive_ptr.h"
#endif
#pragma GCC diagnostic pop
#elif defined(_MSC_VER)
#pragma warning(push, 0)
#include "minimp3/minimp3.h"
#include "minimp3/minimp3_ex.h"
#include "core/device.h"
#include "alc/device.h"
#include "common/intrusive_ptr.h"
#pragma warning(pop)
#else
#error "Compiler is not supported with AGE yet"
#endif
namespace AGE
{
	static mp3dec_t s_Mp3d;
	static uint8_t* s_AudioScratchBuffer;
	static uint32_t s_AudioScratchBufferSize = 10 * 1024 * 1024;
	static al::intrusive_ptr<al::Device> s_Device = nullptr;
	enum class AudioFileFormat
	{
		None = 0,
		Wav,
		Mp3
	};

	/**
 * @brief Prints information about the audio device.
 *
 * This function logs various details about the current audio device to the console using CoreLogger::Info(). 
 * The logged information includes the device name, sample rate, maximum number of sources that can be played simultaneously, 
 * and the number of mono and stereo sources currently playing.
 */
/**
 * @brief Prints information about the audio device.
 *
 * This function logs various details about the current audio device to the console using CoreLogger::Info(). 
 * The logged info includes the device name, sample rate, maximum number of sources that can be played simultaneously, 
 * and the number of mono and stereo sources currently playing.
 */
static void PrintAudioDeviceInfo()
	{
		CoreLogger::Info("Audio Device Info:");
		//CoreLogger::Info("\tName: {0}", s_Device->mDeviceName);
		//CoreLogger::Info("\tSample Rate: {0}", s_Device->mSampleRate);
		//CoreLogger::Info("\tMax Sources: {0}", s_Device->SourcesMax);
		//CoreLogger::Info("\t\tMono: {0}", s_Device->NumMonoSources);
		//CoreLogger::Info("\t\tStereo: {0}", s_Device->NumStereoSources);
	}

	/**
 * @brief Determines the format of an audio file based on its extension.
 * 
 * This function takes a filename as input and returns an enumeration value representing the format of the audio file. The supported formats are Wav and Mp3. If the file has no recognized extension, it will return AudioFileFormat::None.
 * 
 * @param FileName A string containing the name (and possibly path) of the file to be examined.
 * @return An enumeration value representing the format of the audio file. Possible values are Wav, Mp3 and None.
 */
/**
 * @brief Determines the file format based on its extension.
 * @param FileName The name of the file to determine the format for.
 * @return An enum value representing the audio file format (Wav, Mp3 or None if not recognized).
 */
static AudioFileFormat GetFileFormat(const std::string& FileName)
	{
		std::filesystem::path Path = FileName;
		std::string Ext = Path.extension().string();
		
		AudioFileFormat Format = Ext == ".wav" || Ext == ".Wav" ? AudioFileFormat::Wav : Ext == ".mp3" || Ext == ".Mp3" ? AudioFileFormat::Mp3 : AudioFileFormat::None;
		return Format;
	}

	/**
 * @brief Returns an OpenAL audio format based on the number of channels and bits per sample.
 * 
 * @param Channels The number of audio channels (1 for mono, 2 for stereo).
 * @param BitsPerSample The number of bits per sample (8 or 16).
 * 
 * @return ALenum The corresponding OpenAL format code. If the inputs are not recognized, it logs an error and returns a null value.
 */
/**
 * @brief Determines the audio format based on number of channels and bits per sample.
 * 
 * @param Channels Number of audio channels (1 for mono, 2 for stereo).
 * @param BitsPerSample Bit depth of the samples.
 * 
 * @return ALenum Corresponding OpenAL format. Returns 0x0 if unrecognized Wave format.
 */
static ALenum GetFormat(uint8_t Channels, uint8_t BitsPerSample)
	{

		if (Channels == 1 && BitsPerSample == 8)
		{
			return AL_FORMAT_MONO8;
		}
		else if (Channels == 1 && BitsPerSample == 16)
		{
			return AL_FORMAT_MONO16;
		}
		else if (Channels == 2 && BitsPerSample == 8)
		{
			return AL_FORMAT_STEREO8;
		}
		else if (Channels == 2 && BitsPerSample == 16)
		{
			return AL_FORMAT_STEREO16;
		}
		else
		{
			CoreLogger::Error("Unrecognized Wave format: {0} Channels, {1} BitsPerSample", Channels, BitsPerSample);
			return 0x0;
		}
	}

	/**
 * @brief Constructor for the AGESound class. Initializes the sound object with default values.
 * 
 * This constructor initializes an instance of the AGESound class by calling the Init() function, which sets up any necessary resources or defaults for a sound object.
 * 
 * @return void
 */
/**
 * @brief Constructor for the AGESound class. Initializes a new instance of the sound object with default values.
 */
AGESound::AGESound()
	{
		Init();
	}

	

void AGESound::Init()
	{
		s_Device = al::Device::Create(DeviceType::Playback);
		if (!s_Device) //DeviceType::Playback
		{
			CoreLogger::Assert(false, "Error Creating Initializing Audio Device!");
			return;
		}

		PrintAudioDeviceInfo();
		mp3dec_init(&s_Mp3d);

		s_AudioScratchBuffer = new uint8_t[s_AudioScratchBufferSize];

		ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };
		ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };
		ALfloat ListenerOri[] = { 0.0, 0.0, -1.0, 0.0,1.0,0.0 };

		alListenerfv(AL_POSITION, ListenerPos);
		alListenerfv(AL_VELOCITY, ListenerVel);
		alListenerfv(AL_ORIENTATION, ListenerOri);
	}

	/**
 * @brief Starts the sound playback.
 *
 * This function initiates the sound playback by setting up any necessary resources and starting the audio engine. 
 * It does not start the actual playing of the sound, that is done in the Play() method.
 *
 * @return void
 */
/**
 * @brief Starts the sound playback.
 *
 * This function initiates the sound playback by starting to play the audio data from the beginning of the buffer. 
 * It does not reset or rewind the sound, it simply starts playing from where it left off.
 *
 * @return void
 */
void AGESound::Start()
	{
	}

	/**
 * @brief Updates the sound object.
 *
 * This function is responsible for updating the sound object's state based on its current configuration and any changes in the game world. 
 * It does not return a value as it operates by side effects, modifying internal states of the sound object.
 *
 * @return None
 */
/**
 * @brief Updates the sound object.
 *
 * This function is responsible for updating the state of the sound object. It may involve processing audio data, 
 * updating sound properties or triggering any other necessary actions based on its current state.
 *
 * @return void
 */
void AGESound::Update()
	{
	}

	/**
 * @brief Stops the sound from playing.
 *
 * This function is used to stop the sound that was previously started using the Play() method. 
 * It will halt any ongoing playback and reset the position of the sound source back to its initial state.
 *
 * @return void
 */
/**
 * @brief Stops the sound from playing.
 *
 * This function is used to stop the sound that was previously started using the Play() method. 
 * It should be called when you want to halt the playback of the sound.
 *
 * @return void
 */
void AGESound::Stop()
	{
	}

	/**
 * @brief Loads a list of Sound Banks into the system.
 *
 * This function takes in a vector of references to Sound Bank objects and loads them into the sound system.
 * The Sound Banks are expected to be properly initialized before being passed to this function.
 * 
 * @param[in] Banks A vector of references to Sound Bank objects.
 */
/**
 * @brief Loads a collection of Sound Banks into the system.
 *
 * This function takes in a vector of references to Sound Bank objects and loads them into the system. It does not return anything, so it is void.
 * 
 * @param[in] Banks - A constant reference to a vector of SoundBank references. Each SoundBank object represents a bank of sounds that can be played by the system.
 */
void AGESound::LoadBanks(const std::vector<Ref<SoundBank>> &Banks)
	{
	}

	/**
 * @brief Loads a sound bank into the system.
 * 
 * This function takes in a reference to a SoundBank object and loads it into the system. It does not return anything, so use void as the return type.
 *
 * @param Bank A reference to the SoundBank object that you want to load.
 */
/**
 * @brief Loads a sound bank into the system.
 * 
 * This function takes in a reference to a SoundBank object and loads it into the system for use by the AGESound class.
 * The exact behavior of this function depends on its implementation, which is not provided here.
 * 
 * @param Bank A reference to the SoundBank object to be loaded.
 */
void AGESound::LoadBank(Ref<SoundBank> Bank)
	{
	}

	/**
 * @brief Get the name of the current event
 *
 * This function returns a reference to the string that holds the name of the 
 * currently playing sound event. The returned value is not const, meaning it can be modified.
 *
 * @return A reference to the string holding the name of the current event
 */
/**
 * @brief Get the name of the current event
 * @return A reference to a string containing the name of the current event
 */
std::string & AGESound::GetCurrentEventName()
	{
		return m_EventName;
	}

	/**
 * @brief Set the name of the current event
 * @param Name The new name for the current event
 */
/**
 * @brief Sets the name of the current event.
 *
 * This function sets the name of the current event in the AGESound object. The new name is passed as a const reference to avoid unnecessary copying. 
 *
 * @param Name A constant reference to the string that will be used as the new name for the current event.
 */
void AGESound::SetCurrentEventName(const std::string &Name)
	{
	}

	/**
 * @brief Shuts down the AGESound object.
 *
 * This function is used to clean up any resources that were allocated during the initialization of the AGESound object, such as memory or file handles. It prepares the object for deletion by setting it into a safe state and cleaning up any remaining resources.
 *
 * @return void
 */
/**
 * @brief Shuts down the AGESound object.
 * 
 * This function is used to clean up any resources that were allocated during the initialization of the AGESound object, such as memory or file handles. It prepares the object for deletion or reuse.
 */
void AGESound::Shutdown()
	{
	}

	/**
 *  @brief Checks whether the given event name is valid or not.
 *  
 *  This function takes an event name as input and checks if it's a valid event. The validity of the event can be based on various factors such as its length, format etc.
 *  
 *  @param EventName A string representing the name of the event to validate.
 *  @return Returns true if the event is valid, false otherwise.
 */
/**
 * @brief Checks whether the given event name is valid or not.
 * 
 * This function takes an event name as input and checks if it's a valid event by comparing it with a list of known events. If the event name matches any of these, the function returns true; otherwise, it returns false.
 * 
 * @param EventName The name of the event to be checked.
 * @return True if the event is valid, False otherwise.
 */
bool AGESound::IsEventValid(const std::string& EventName)
	{
		return false;
	}

	/**
 * @brief This function sets a parameter by its name.
 *
 * The function takes two parameters - the name of the parameter and the value to set it to. It does not return anything. 
 * If the provided name corresponds to an existing parameter, this function will update that parameter's value. Otherwise, it will do nothing.
 *
 * @param Name A string representing the name of the parameter to be set.
 * @param Value The new float value for the parameter.
 *
 * @return None
 */
/**
 * @brief Set the parameter value by its name
 * @param Name The name of the parameter to set
 * @param Value The new value for the parameter
 */
void AGESound::SetParameterByName(const std::string &Name, float Value)
	{
	}

	/**
 * @brief Sets the 3D attributes for the sound object.
 *
 * This function sets the 3D attributes of the sound object using a void pointer to the Attributes structure. The exact nature and format of this data is not specified, as it depends on the specific implementation of the AGESound class.
 *
 * @param Attributes A void pointer to the Attributes structure.
 */
/**
 * @brief Sets the 3D attributes for the sound object.
 *
 * This function sets the 3D attributes of the sound object using a void pointer to the Attributes structure. The exact nature and format of this data is not specified in the documentation, so it's assumed to be opaque to Doxygen.
 *
 * @param Attributes A void pointer to the Attributes structure. This parameter is expected to contain specific 3D attributes for the sound object but its content is not defined by this function.
 */
void AGESound::Set3DAttributes(void *Attributes)
	{
	}

	/**
 * @brief Stops the sound from playing.
 *
 * This function is used to stop any currently playing sounds in the game. 
 * It does not take any parameters and returns void.
 */
/**
 * @brief Stops the sound from playing.
 * 
 * This function is used to stop any currently playing sounds in the game. It does not take any parameters and has no return value.
 */
void AGESound::StopSound()
	{

	}
	/**
 * @brief Unloads a sound from the specified audio source.
 *
 * This function retrieves and removes any buffers that have been queued for playback by the 
 * OpenAL audio source provided as an argument. It does this by querying the number of processed 
 * buffers (i.e., those that are ready to be played) from the source, then unqueues them if there are any.
 *
 * @param Source A reference to the AudioSource object whose sound is to be unloaded.
 */
/**
 * @brief Unloads a sound from an audio source.
 *
 * This function is used to unload or remove a sound from an audio source. It does this by checking if there are any buffers that have been processed and if so, it removes them using the alSourceUnqueueBuffers function. 
 *
 * @param Source A reference to the AudioSource object from which the sound is being removed.
 */
void AGESound::UnloadSound(const Ref<AudioSource>& Source)
	{
		int32_t ProcessedBuffers;
		alGetSourcei(Source->m_SourceHandle, AL_BUFFERS_PROCESSED, &ProcessedBuffers);
		//Possibly unneeded
		if (ProcessedBuffers > 0)
		{
			alSourceUnqueueBuffers(Source->m_SourceHandle, 1, &Source->m_BufferHandle);
		}
		

		
	}
	//void AGESound::UpdateStream(const uint32_t SourceID, const ALenum& Format, const int32_t SampleRate, std::vector<char> SoundData, size_t& Cursor)
	//{
	//	m_RemovedBuffers = 0;
	//	alCall(alGetSourcei, m_SourceID, AL_BUFFERS_PROCESSED, &m_RemovedBuffers);
	//	if (m_RemovedBuffers <= 0)
	//	{
	//		return;
	//	}
	//	while (m_RemovedBuffers--)
	//	{
	//		ALuint Buffer;
	//		DetachBuffersFromSource(m_SourceID, 1, Buffer);
	//
	//		ALsizei DataSize = m_BufferSize;
	//
	//		char* Data = new char[DataSize];
	//		std::memset(Data, 0, DataSize);
	//
	//		size_t DataSizeToCopy = m_BufferSize;
	//
	//		if (Cursor + m_BufferSize > SoundData.size())
	//		{
	//			DataSizeToCopy = SoundData.size() - Cursor;
	//		}
	//
	//		std::memcpy(&Data[0], &SoundData[Cursor], DataSizeToCopy);
	//		Cursor += DataSizeToCopy;
	//
	//		if (DataSizeToCopy < m_BufferSize)
	//		{
	//			Cursor = 0;
	//			std::memcpy(&Data[DataSizeToCopy], &SoundData[Cursor], m_BufferSize - DataSizeToCopy);
	//			Cursor = m_BufferSize - DataSizeToCopy;
	//		}
	//
	//		SetBufferData(Buffer, Format, Data, m_BufferSize, SampleRate);
	//		AttachBufferToSource(m_SourceID, 1, &Buffer);
	//
	//		delete[] Data;
	//
	//	}
	//}
	//void AGESound::AttachBufferToSource(uint32_t SourceID, ALsizei n, uint32_t* Buffer)
	//{
	//	alCall(alSourceQueueBuffers, SourceID, n, &Buffer[0]);
	//}
	//void AGESound::DetachBuffersFromSource(uint32_t SourceID, ALsizei n, uint32_t& Buffers)
	//{
	//	alCall(alSourceUnqueueBuffers, SourceID, n, &Buffers);
	//	//m_RemovedBufferIDs.push_back(Buffer);
	//
	//	//if (Buffer != m_RemovedBufferIDs[0])
	//	//{
	//	//	AttachBufferToSource(m_SourceID, 1, Buffer);
	//	//	PlaySound();
	//	//}
	//}
	/**
 * @brief Finds available devices for the given ALCdevice.
 *
 * This function retrieves a list of available audio devices using the OpenAL context provided by the Device parameter. 
 * The retrieved device names are stored in the DevicesArray vector.
 *
 * @param[out] DevicesArray A reference to a std::vector<std::string> where the device names will be stored.
 * @param[in] Device An ALCdevice pointer that represents an OpenAL context.
 * 
 * @return Returns true if devices are found, false otherwise. In this implementation, it always returns true as there is no way to fail in retrieving available devices.
 */
/**
 * @brief Finds available devices for the given ALCdevice.
 *
 * This function retrieves a list of available audio devices using the OpenAL context provided by the Device parameter. 
 * The retrieved device names are stored in the DevicesArray vector.
 *
 * @param[out] DevicesArray A reference to a std::vector<std::string> where the device names will be stored.
 * @param[in] Device Pointer to an ALCdevice that represents the OpenAL context for which available devices should be found.
 * 
 * @return Returns true if at least one device is available, false otherwise. This function does not differentiate between no devices and devices with specific names.
 */
bool AGESound::FindAvailableDevices(std::vector<std::string>& DevicesArray, ALCdevice* Device)
	{
		//const ALchar* Devices;
		//if (!alcCall(alcGetString, Devices, Device, nullptr, ALC_DEVICE_SPECIFIER))
		//{
		//	return false;
		//}
		alcGetString(Device, ALC_DEVICE_SPECIFIER);
		//const char* ptr = Devices;
		//
		//DevicesArray.clear();
		//
		//do
		//{
		//	DevicesArray.push_back(std::string(ptr));
		//	ptr += DevicesArray.back().size() + 1;
		//} while (*(ptr + 1) != '\0');

		return true;
	}

	/**
 * This function takes as input a filename and a line number along with an OpenAL error code. It then logs the appropriate error message to the console using CoreLogger::Error() and asserts that the condition is false. The function returns true if no errors are encountered, otherwise it returns false.
 */
/**
 * @brief Displays OpenAL error codes.
 * 
 * This function takes in three parameters - the file name where the error occurred, the line number and the type of error that was encountered. It logs appropriate messages for each type of error using CoreLogger::Error() and CoreLogger::Assert(). If an unknown error is detected, it simply returns false.
 * 
 * @param FN The name of the file where the error occurred.
 * @param line The line number in the file where the error occurred.
 * @param Error The type of error that was encountered.
 * 
 * @return Returns true if an error is found, false otherwise.
 */
bool AGESound::DisplayErrorCode(const std::string& FN, const uint32_t line, ALenum Error)
	{


		if (Error != AL_NO_ERROR)
		{


			switch (Error)
			{
			case AL_OUT_OF_MEMORY:
			{
				CoreLogger::Error("File: {0}, Line: {1}, The requested operation resulted in OpenAL running out of memory", FN, line);
				CoreLogger::Assert(false, "Out Of Memory!");
				break;
			}
			case AL_INVALID_VALUE:
			{
				CoreLogger::Error("File: {0}, Line: {1}, An invalid value was passed to an OpenAL function", FN, line);
				CoreLogger::Assert(false, "Invalid Value!");
				break;
			}

			case AL_ILLEGAL_COMMAND:
			{
				CoreLogger::Error("File: {0}, Line: {1}, The requested operation is not valid", FN, line);
				CoreLogger::Assert(false, "Illegal Command|Operation");
				break;
			}

			case AL_INVALID_ENUM:
			{

				CoreLogger::Error("File: {0}, Line: {1}, An invalid enum value was passed to an OpenAL function", FN, line);
				CoreLogger::Assert(false, "Invalid Enum");
				break;
			}

			case AL_INVALID_NAME:
			{
				CoreLogger::Error("File: {0}, Line: {1}, A bad name (ID) was passed to an OpenAL function", FN, line);
				CoreLogger::Assert(false, "Invalid Name");
				break;
			}

			default:
			{

				return false;
			}
			}
		}
		return true;
	}

	/**
 * @brief Loads an audio source from a file.
 * 
 * This function loads an audio source based on the format of the provided filename. It supports WAV and MP3 formats. If the format is not supported, it logs an error message and returns an invalid AudioSource object.
 * 
 * @param FileName The name of the file to load from.
 * @return An AudioSource object representing the loaded audio data.
 */
/**
 * @brief Loads an audio source from a file.
 * 
 * This function loads an audio source based on the format of the provided filename. It supports WAV and MP3 formats. If the format is not supported, it logs an error message and returns an invalid AudioSource object.
 * 
 * @param FileName The name of the file to load from.
 * @return An AudioSource object representing the loaded audio data.
 */
AudioSource AGESound::LoadAudioSource(const std::string& FileName)
	{
		auto Format = GetFileFormat(FileName);

		switch (Format)
		{
			case AudioFileFormat::Wav:
			{
				return LoadWav(FileName);
			}
			case AudioFileFormat::Mp3:
			{
				return LoadAudioSourceMP3(FileName);
			}
			default:
			{
				CoreLogger::Error("Audio File Format not supported! AudioSource Object will not be valid and should not be used!");
				return AudioSource();
			}
		}
		return AudioSource();
	}

	/** 
 * @brief Plays an audio source.
 * 
 * This function plays the provided AudioSource using OpenAL's alSourcePlay function.
 * 
 * @param Source A reference to the AudioSource that is to be played.
 */
/** 
 * @brief Plays an audio source.
 * 
 * This function plays the provided AudioSource using OpenAL's alSourcePlay function.
 * The function takes a reference to an AudioSource object which is played by this method.
 * 
 * @param Source A const reference to an AudioSource object that needs to be played.
 */
void AGESound::Play(const Ref<AudioSource>& Source)
	{
		alSourcePlay(Source->m_SourceHandle);
	}
	/**
 * @brief Stops the audio source from playing.
 * 
 * This function stops an audio source from playing by using the OpenAL library's alSourceStop() function.
 * The audio source to be stopped is passed as a reference to an AudioSource object.
 * 
 * @param Source A reference to the AudioSource object whose source should be stopped.
 */
/** 
 * @brief Stops an audio source from playing.
 * 
 * This function stops the audio source specified by the handle provided. It does not check if the source is actually playing, so it should be used with caution.
 * 
 * @param Source A reference to the AudioSource object that you want to stop.
 */
void AGESound::Stop(const Ref<AudioSource>& Source)
	{
		alSourceStop(Source->m_SourceHandle);
	}
	/**
 * @brief Stops all the audio sources in a given vector.
 * 
 * This function iterates over each element of the provided vector and calls the Stop() function on it, effectively stopping any ongoing sound playback for each AudioSource object.
 * 
 * @param Sources A constant reference to a vector of Ref<AudioSource> objects representing the audio sources to be stopped.
 * @return void No return value is expected as all operations are performed in-place.
 */
/**
 * @brief Stops all audio sources in the given vector.
 *
 * This function iterates over each element of the provided vector and calls the Stop() function on it, effectively stopping any ongoing sound playback for that source.
 * 
 * @param Sources A constant reference to a vector of AudioSource references. Each element represents an individual audio source which will have its playback stopped.
 */
void AGESound::Stop(const std::vector<Ref<AudioSource>>& Sources)
	{
		for (size_t i = 0; i < Sources.size(); i++)
		{
			Stop(Sources[i]);
		}
	}
	/**
 * @brief Set the debug logging state for the AGESound object
 * 
 * This function sets the debug logging state of the AGESound object. When debug logging is enabled, it will provide detailed information about its internal operations.
 * 
 * @param Log A boolean value indicating whether to enable (true) or disable (false) debug logging.
 * @return void
 */
/**
 * @brief Set the Debug Logging flag for the AGESound object
 * 
 * This function sets a boolean value that determines whether debug logging is enabled or disabled.
 * 
 * @param Log A boolean indicating if debug logging should be enabled (true) or disabled (false).
 */
void AGESound::SetDebugLogging(bool Log)
	{
	}

	/**
 * @brief Converts the given buffer to an integer.
 *
 * This function takes in a character buffer and its length, converts it into an integer based on the endianness of the system. 
 * If the system is little-endian, the bytes are copied directly into the integer. For big-endian systems, the bytes are reversed before being copied.
 *
 * @param Buffer The buffer to be converted.
 * @param Length The length of the buffer.
 * 
 * @return An integer representation of the input buffer.
 */
/**
 * @brief Converts a buffer of bytes to an integer.
 *
 * This function takes in a buffer and its length, converts the content of the buffer into an integer based on the endianness of the system. 
 * If the system is little-endian, it directly copies the buffer's content into the integer. If the system is big-endian, it reverses the order of bytes in the buffer and stores them into the integer.
 *
 * @param Buffer Pointer to the buffer containing the data to be converted.
 * @param Length The length of the buffer.
 * 
 * @return An integer representation of the content of the buffer.
 */
int32_t AGESound::ConvertToInt(char* Buffer, size_t Length)
	{
		int32_t a = 0;
		if (!Utils::EngineStatics::IsBigEndian())
		{
			std::memcpy(&a, Buffer, Length);
		}
		else
		{
			for (size_t i = 0; i < Length; i++)
			{
				reinterpret_cast<char*>(&a)[3 - i] = Buffer[i];
			}
		}
		return a;
	}
	"/**\n \
* @brief Loads an audio source from an MP3 file.\n \
* This function loads an MP3 file and creates an OpenAL buffer for it, logging details to console.\n \
* @param FileName The name of the MP3 file to load.\n \
* @return An AudioSource struct containing information about loaded audio source.\n \
* @note Assumes mp3dec library is already initialized and ready for use.\n \
*/"
/**
 * @brief Loads an audio source from an MP3 file.
 * 
 * @param FileName The name of the MP3 file to load.
 * @return An instance of the `AudioSource` struct containing the handle to the OpenAL buffer and source, or an empty `AudioSource` if the file cannot be loaded.
 */
AudioSource AGESound::LoadAudioSourceMP3(const std::string& FileName)
	{

		mp3dec_file_info_t Info;
		int LoadResult = mp3dec_load(&s_Mp3d, FileName.c_str(), &Info, NULL, NULL);
		if (!LoadResult)
		{
			CoreLogger::Error("Unable to load file: {}", FileName);
			return AudioSource();
		}
		size_t Size = Info.samples * sizeof(mp3d_sample_t);

		auto SampleRate = Info.hz;
		auto Channels = Info.channels;
		auto ALFormat = GetFormat((uint8_t)Channels, 16);
		double LengthSeconds = (double)Size / ((float)Info.avg_bitrate_kbps * 1024.f);
		ALuint Buffer;
		alGenBuffers(1, &Buffer);
		alBufferData(Buffer, ALFormat, Info.buffer, (int)Size, SampleRate);

		AudioSource Audio = { Buffer, true, LengthSeconds };
		alGenSources(1, &Audio.m_SourceHandle);
		alSourcei(Audio.m_SourceHandle, AL_BUFFER, (int)Buffer);

		CoreLogger::Info("File Info - {0}", FileName.c_str());
		CoreLogger::Info("\tChannels: {0}", Channels);
		CoreLogger::Info("\tSample Rate: {0}", SampleRate);
		CoreLogger::Info("\tSize: {0} bytes", Size);

		if (alGetError() != AL_NO_ERROR)
		{
			CoreLogger::Assert(false, "Failed to Setup Sound Source");
		}
		return Audio;
	}
	/**
 * @brief Loads a WAV file and returns an AudioSource object with sound data.
 * 
 * Opens a binary file, checks its openability, reads header for audio format info (channels, sample rate, bits per sample), allocates memory for sound data buffer, reads sound data into this buffer, creates AudioSource from this data.
 * 
 * @param FileName Name of the WAV file to load.
 * @return An AudioSource object with loaded audio data or empty if loading failed.
 */
/**
 * @brief Loads a WAV file and returns an AudioSource object with the sound data.
 * 
 * This function opens a binary file to get information about the audio format (channels, sample rate, bits per sample, size), allocates memory for the sound data buffer and reads the actual sound data into this buffer. It then creates an AudioSource object from the loaded data and returns it.
 * 
 * @param FileName The name of the WAV file to load.
 * @return An AudioSource object with the sound data, or an empty AudioSource if the file could not be opened or its header could not be read.
 */
AudioSource AGESound::LoadWav(const std::string& FileName)
	{
		uint8_t Channels;
		uint8_t BitsPerSample;
		int32_t SampleRate;
		ALsizei Size;

		std::ifstream In(FileName, std::ios::binary);
		if (!In.is_open())
		{
			CoreLogger::Error("Could not Open File: {0}", FileName);
			return AudioSource();
		}

		if (!LoadWavFileHeader(In, Channels, SampleRate, BitsPerSample, Size))
		{
			CoreLogger::Error("Could not load wav Header of {0}", FileName);
			return AudioSource();
		}

		char* Buffer = new char[(size_t)Size];
		In.read(Buffer, Size);
		std::vector<char> Data(Buffer, Buffer + Size);
		AudioSource Audio;
		Audio.SetSoundData(Data);
		//auto ALFormat = GetFormat(Channels, BitsPerSample);

		return Audio;
	}
	<doxygen comment>
/**
 * @brief Loads the header of a WAV file.
 * 
 * This function reads from an input stream to extract key information about the audio data in the WAV file such as number of channels, sample rate, bits per sample and size of data.
 * The extracted information is stored in output parameters provided by reference.
 * 
 * @param File The input file stream to read from.
 * @param Channels Output parameter for the number of audio channels in the WAV file (1 for mono, 2 for stereo, etc.).
 * @param SampleRate Output parameter for the sample rate of the audio data in the WAV file.
 * @param BitsPerSample Output parameter for the number of bits per sample in the WAV file.
 * @param Size Output parameter for the size of the audio data in the WAV file, measured in bytes.
 * 
 * @return True if the header was successfully loaded and parsed, false otherwise.
 */
bool AGESound::LoadWavFileHeader(std::ifstream& File, uint8_t& Channels, int32_t& SampleRate, uint8_t& BitsPerSample, ALsizei& Size)
	{
		char Buffer[4];
		if (!File.is_open())
		{
			return false;
		}

		//The RIFF

		if (!File.read(Buffer, 4))
		{
			CoreLogger::Error("Could not read RIFF!");
			return false;
		}

		if (std::strncmp(Buffer, "RIFF", 4) != 0)
		{
			CoreLogger::Error("File is NOT a valid WAVE file (Header doesn't begin with  RIFF)!");
			return false;
		}

		// The size of the file
		if (!File.read(Buffer, 4))
		{
			CoreLogger::Error("Could not read size of file!");
			return false;
		}

		// The WAVE
		if (!File.read(Buffer, 4))
		{
			CoreLogger::Error("Could not read WAVE!");
			return false;
		}
		if (std::strncmp(Buffer, "WAVE", 4) != 0)
		{
			CoreLogger::Error("File is not valid WAVE file (Header doesn't contain WAVE)!");
			return false;
		}

		// "fmt/0"
		if (!File.read(Buffer, 4))
		{
			CoreLogger::Error("Could not read fmt/0 !");
			return false;
		}
		if (!File.read(Buffer, 4))
		{
			CoreLogger::Error("Could not read the 16!");
			return false;
		}

		//PCM should be 1
		if (!File.read(Buffer, 2))
		{
			CoreLogger::Error("Could not read PCM!");
			return false;
		}
		//The number channels
		if (!File.read(Buffer, 2))
		{
			CoreLogger::Error("Could not read number of channels!");
			return false;
		}
		Channels = (uint8_t)ConvertToInt(Buffer, 2);
		//Sample rate
		if (!File.read(Buffer, 4))
		{
			CoreLogger::Error("Could not read sample rate!");
			return false;
		}
		SampleRate = ConvertToInt(Buffer, 4);

		// SampleRate * bitsPerSample * channels / 8
		//Byte Rate
		if (!File.read(Buffer, 4))
		{
			CoreLogger::Error("Could not read SampleRate * bitsPerSample * channels / 8!");
			return false;
		}

		//Block Align = NumChannels *BitsPerSample / 8
		if (!File.read(Buffer, 2))
		{
			CoreLogger::Error("Could not read Block Align!");
			return false;
		}

		//BitsPerSample
		if (!File.read(Buffer, 2))
		{
			CoreLogger::Error("Could not read Bits Per Sample!");
			return false;
		}
		BitsPerSample = (uint8_t)ConvertToInt(Buffer, 2);

		//Data Chunk Header "data"
		if (!File.read(Buffer, 4))
		{
			CoreLogger::Error("Could not read Data Chunk Header");
			return false;
		}
		if (std::strncmp(Buffer, "data", 4) != 0)
		{
			CoreLogger::Error("File is not valid WAVE file (Doesn't have 'data' tag)!");
			return false;
		}

		//Size of Data
		if (!File.read(Buffer, 4))
		{
			CoreLogger::Error("Could not read data size!");
			return false;
		}

		Size = ConvertToInt(Buffer, 4);

		if (File.eof())
		{
			CoreLogger::Error("Reached EOF on the File!");
			return false;
		}
		if (File.fail())
		{
			CoreLogger::Error("Fail state set on File!");
			return false;
		}
		return true;
	}

	template<>
	/**
 * @brief This function returns a pointer to the AGESound object.
 *
 * The function is used to obtain an instance of AGESound that can be cast back into its original class type using dynamic_cast. 
 * It does this by returning 'this' as a pointer to AGESound, which allows it to be treated as if it were an instance of the AGESound class.
 *
 * @return A pointer to the AGESound object.
 */
/**
 * @brief This function returns a pointer to AGESound object casted from the current instance of AudioEngine.
 * @return A pointer to an AGESound object, or nullptr if this is not an AGESound instance.
 */
AGESound* AudioEngine::As()
	{
		return (AGESound*)this;
	}
}