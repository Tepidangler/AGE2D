#pragma once
#ifdef WITH_WWISE
#ifndef AK_OPTIMIZED
#include <AK/Comm/AkCommunication.h>
#endif
#include "Core/Public/Core.h"
#include "Core/Public/Wwise_IDs.h"
#include "Audio/AudioEngine/Public/AudioEngine.h"
#include <AK/SoundEngine/Common/AkSoundEngine.h>
#include <AK/MusicEngine/Common/AkMusicEngine.h>
#include <AK/SoundEngine/Common/AkMemoryMgr.h>
#include <AK/SoundEngine/Common/AkModule.h>
#include <AK/SoundEngine/Common/IAkStreamMgr.h>
#include <AK/SpatialAudio/Common/AkSpatialAudio.h>
#include <AK/Tools/Common/AkPlatformFuncs.h>
#include <AK/SoundEngine/Common/AkFilePackageLowLevelIODeferred.h>
#include <string>

namespace AGE
{
	class Wwise : public AudioEngine
	{
	public:

		Wwise();

		~Wwise();


		inline void SetMarkerLabel(const std::string& Label) { m_MarkerLabel = Label; }

		virtual void Init() override;

		virtual void Start() override;
		virtual void Update() override;
		virtual void Stop() override;

		virtual void Shutdown() override;

		virtual void LoadBanks(const std::vector<Ref<SoundBank>>& Banks) override;
		virtual void LoadBank(Ref<SoundBank> Bank) override;

		virtual std::string& GetCurrentEventName() override;
		virtual void SetCurrentEventName(const std::string& Name) override;
		virtual bool IsEventValid(const std::string& EventName) override;

		virtual void SetParameterByName(const std::string& Name, float Value) override;
		virtual void Set3DAttributes(void* Attributes) override;
		virtual void LoadEvents() override{};

		void ProcessAudio();

		void SetBasePath(const AkOSChar* Path);
#if 0
		void LoadBank(const std::string& Name);

		void LoadBank(const uint32_t Name);
#endif

		void UnloadBank(const std::string& Name);

		void UnloadBank(const uint32_t Name);

		void MIDICallback(bool LastCall);

		AkPlayingID PostMIDIOnEvent(uint32_t EventID, uint64_t GameObjID, AkMIDIPost* Posts, uint16_t NumPosts);

		AkPlayingID PostMarkerEvent(const char* EventID, uint64_t GameObjID);

		AkPlayingID PostMarkerEvent(const uint32_t EventID, uint64_t GameObjID);

		AKRESULT SetPosition(uint64_t GameObjID, AkSoundPosition SoundPos);

		AKRESULT SetRTPCValue(const char* Name, AkRtpcValue nRPM);

		AKRESULT SetState(uint32_t StateGroupID, uint32_t StateID);

		AKRESULT SetState(const char* Name, const char* Group);

		AKRESULT SetSwitch(uint32_t SwitchGroupID, uint32_t SwitchID, uint64_t GameObjID);

		AKRESULT SetSwitch(const char* SwitchGroup, const char* Switch, uint64_t GameObjID);

		AKRESULT RegisterGameObj(uint64_t GameObjID, const char* Name);

		AKRESULT UnregisterGameObj(uint64_t GameObjID);

		void ParseSoundBankFile(const std::string& Filepath);

		const char* ProcessResultErrorCode(AKRESULT Code);

		CAkFilePackageLowLevelIODeferred* g_LowLevelIO;

	private:
		std::string m_BasePath;
		AkAudioSettings m_AudioSettings;

		std::string m_MarkerLabel;
	};
}
#endif