#include "AGEpch.hpp"

#include "Statics/Public/Statics.h"
#include "Audio/AGESound/Public/AGEAudio.h"
#include "Audio/AGESound/Public/Sound.h"
#include "core/device.h"
#include "alc/device.h"
#include "common/intrusive_ptr.h"
#include "Core/Public/Log.h"

#define MINIMP3_IMPLEMENTATION

#include "minimp3/minimp3.h"
#include "minimp3/minimp3_ex.h"

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

	static void PrintAudioDeviceInfo()
	{
		CoreLogger::Info("Audio Device Info:");
		//CoreLogger::Info("\tName: {0}", s_Device->mDeviceName);
		//CoreLogger::Info("\tSample Rate: {0}", s_Device->mSampleRate);
		//CoreLogger::Info("\tMax Sources: {0}", s_Device->SourcesMax);
		//CoreLogger::Info("\t\tMono: {0}", s_Device->NumMonoSources);
		//CoreLogger::Info("\t\tStereo: {0}", s_Device->NumStereoSources);
	}

	static AudioFileFormat GetFileFormat(const std::string& FileName)
	{
		std::filesystem::path Path = FileName;
		std::string Ext = Path.extension().string();
		
		AudioFileFormat Format = Ext == ".wav" || Ext == ".Wav" ? AudioFileFormat::Wav : Ext == ".mp3" || Ext == ".Mp3" ? AudioFileFormat::Mp3 : AudioFileFormat::None;
		return Format;
	}

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

	AGESound::AGESound()
	{
		Init();
	}

	void AGESound::Init()
	{
		if (s_Device = al::Device::Create(DeviceType::Playback)) //DeviceType::Playback
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

	void AGESound::Start()
	{
	}

	void AGESound::Update()
	{
	}

	void AGESound::Stop()
	{
	}

	void AGESound::LoadBanks(const std::vector<Ref<SoundBank>> &Banks)
	{
	}

	void AGESound::LoadBank(Ref<SoundBank> Bank)
	{
	}

	std::string & AGESound::GetCurrentEventName()
	{
		return m_EventName;
	}

	void AGESound::SetCurrentEventName(const std::string &Name)
	{
	}

	void AGESound::Shutdown()
	{
	}

	bool AGESound::IsEventValid(const std::string& EventName)
	{
		return false;
	}

	void AGESound::SetParameterByName(const std::string &Name, float Value)
	{
	}

	void AGESound::Set3DAttributes(void *Attributes)
	{
	}

	void AGESound::StopSound()
	{

	}
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
			return false;
			}
		}
		return true;
	}

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
		}
		return AudioSource();
	}
	void AGESound::Play(const Ref<AudioSource>& Source)
	{
		alSourcePlay(Source->m_SourceHandle);
	}
	void AGESound::Stop(const Ref<AudioSource>& Source)
	{
		alSourceStop(Source->m_SourceHandle);
	}
	void AGESound::Stop(const std::vector<Ref<AudioSource>>& Sources)
	{
		for (int i = 0; i < Sources.size(); i++)
		{
			Stop(Sources[i]);
		}
	}
	void AGESound::SetDebugLogging(bool Log)
	{
	}
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
	AudioSource AGESound::LoadAudioSourceMP3(const std::string& FileName)
	{

		mp3dec_file_info_t Info;
		int LoadResult = mp3dec_load(&s_Mp3d, FileName.c_str(), &Info, NULL, NULL);
		size_t Size = Info.samples * sizeof(mp3d_sample_t);

		auto SampleRate = Info.hz;
		auto Channels = Info.channels;
		auto ALFormat = GetFormat(Channels, 16);
		float LengthSeconds = Size / (Info.avg_bitrate_kbps * 1024.f);
		ALuint Buffer;
		alGenBuffers(1, &Buffer);
		alBufferData(Buffer, ALFormat, Info.buffer, Size, SampleRate);

		AudioSource Audio = { Buffer, true, LengthSeconds };
		alGenSources(1, &Audio.m_SourceHandle);
		alSourcei(Audio.m_SourceHandle, AL_BUFFER, Buffer);

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

		char* Buffer = new char[Size];
		In.read(Buffer, Size);
		std::vector<char> Data(Buffer, Buffer + Size);
		AudioSource Audio;
		Audio.SetSoundData(Data);
		auto ALFormat = GetFormat(Channels, BitsPerSample);

		return Audio;
	}
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
		Channels = ConvertToInt(Buffer, 2);
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
		BitsPerSample = ConvertToInt(Buffer, 2);

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
	AGESound* AudioEngine::As()
	{
		return (AGESound*)this;
	}
}