#pragma once
#include "Core/Public/Core.h"
#include "Audio/AudioEngine/Public/AudioEngine.h"
#include "AL/al.h"
#include "AL/alext.h"


namespace AGE
{
	class AudioSource;

	class AGESound : public AudioEngine
	{
	public:
		AGESound();

		virtual void Init() override;
		virtual void Start() override;
		virtual void Update() override;
		virtual void Stop() override;

		virtual void LoadBanks(const std::vector<Ref<SoundBank>>& Banks) override;
		virtual void LoadBank(Ref<SoundBank> Bank) override;

		virtual std::string& GetCurrentEventName() override;
		virtual void SetCurrentEventName(const std::string& Name) override;
		virtual void LoadEvents() override{};
		virtual void Shutdown() override;
		virtual bool IsEventValid(const std::string& EventName) override;

		virtual void SetParameterByName(const std::string& Name, float Value) override;
		virtual void Set3DAttributes(void* Attributes) override;
		static AudioSource LoadAudioSource(const std::string& FileName);
		void Play(const Ref<AudioSource>& Source);
		void Stop(const Ref<AudioSource>& Source);
		void Stop(const std::vector<Ref<AudioSource>>& Sources);




		static void SetDebugLogging(bool Log);

	private:

		static int32_t ConvertToInt(char* Buffer, size_t Length);
		static AudioSource LoadAudioSourceMP3(const std::string& FileName);
		static AudioSource LoadWav(const std::string& FileName);
		static bool LoadWavFileHeader(std::ifstream& File, uint8_t& Channels, int32_t& SampleRate, uint8_t& BitsPerSample, ALsizei& Size);


		void StopSound();
		static void UnloadSound(const Ref<AudioSource>& Source);

		//void UpdateStream(const uint32_t SourceID, const ALenum& Format, const int32_t SampleRate, std::vector<char> SoundData, size_t& Cursor);

		//void AttachBufferToSource(uint32_t SourceID, ALsizei n, uint32_t* Buffer);
		//void DetachBuffersFromSource(uint32_t SourceID, ALsizei n, uint32_t& Buffers);
		std::vector<std::string> GetAvailableSoundDevices() { return m_AvailableSoundDevices; }

		static bool DisplayErrorCode(const std::string& FN, const uint32_t line, ALenum Error);

	private:
		bool FindAvailableDevices(std::vector<std::string>& DevicesArray, ALCdevice* Device);
	private:

		ALCdevice* m_Device;

		ALCcontext* m_Context;

		std::vector<std::string> m_AvailableSoundDevices;

		std::string m_EventName = "NONE";
	};
}