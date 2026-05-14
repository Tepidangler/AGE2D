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
		/**
 * @brief Destructor for AGESound class.
 *
 * This function is responsible for releasing any resources that the AGESound object may have acquired during its lifetime, such as memory or file handles. It does not return anything and has no parameters.
 */
~AGESound() override = default;
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
		/**
 * @brief Retrieves the list of available sound devices.
 *
 * This function returns a vector containing all the currently available sound devices. The devices are returned in no particular order.
 *
 * @return A std::vector<std::string> containing the names of all available sound devices. If there are no available sound devices, an empty vector is returned.
 */
/**
 * @brief Retrieves the list of available sound devices.
 *
 * This function returns a vector containing all the currently available sound devices in the system.
 * The returned data is populated from internal storage and may not always be up-to-date with the current state of the system.
 * 
 * @return A std::vector<std::string> containing the names of all available sound devices. If no sound devices are available, an empty vector is returned.
 */
std::vector<std::string> GetAvailableSoundDevices() { return m_AvailableSoundDevices; }

		static bool DisplayErrorCode(const std::string& FN, const uint32_t line, ALenum Error);

	private:
		bool FindAvailableDevices(std::vector<std::string>& DevicesArray, ALCdevice* Device);
	private:

		[[maybe_unused]] ALCdevice* m_Device;

		[[maybe_unused]] ALCcontext* m_Context;

		std::vector<std::string> m_AvailableSoundDevices;

		std::string m_EventName = "NONE";
	};
}