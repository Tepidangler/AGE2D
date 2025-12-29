#include "AGEpch.hpp"

#include "Audio/Wwise/Public/WWiseEngine.h"

namespace AGE
{
	Wwise::Wwise()
	{
		g_LowLevelIO = new CAkFilePackageLowLevelIODeferred();
		Init();
	}

	Wwise::~Wwise()
	{
		Shutdown();
	}
	void Wwise::Init()
	{

		AkMemSettings MemSettings;
		AK::MemoryMgr::GetDefaultSettings(MemSettings);
		if (AK::MemoryMgr::Init(&MemSettings) != AK_Success)
		{
			AGE_CORE_ASSERT(false, "Could Not Create The Memory Manager!");
			return;

		}

		CoreLogger::Trace("Initialized Wwise Memory Manager!");
		AkStreamMgrSettings StmSettings;
		AK::StreamMgr::GetDefaultSettings(StmSettings);
		if (!AK::StreamMgr::Create(StmSettings))
		{
			AGE_CORE_ASSERT(false, "Could Not Create The Streaming Manager!");
			return;
		}
		CoreLogger::Trace("Initialized Wwise Streaming Manager!");


		AkDeviceSettings DeviceSettings;
		AK::StreamMgr::GetDefaultDeviceSettings(DeviceSettings);

		if (g_LowLevelIO->Init(DeviceSettings) != AK_Success)
		{
			AGE_CORE_ASSERT(false, "Could Not Create The Streaming Device and Low-Level I/O System!");
			return;
		}
		CoreLogger::Trace("Initialized Wwise Streaming Device and Low-Level I/O System!");



		AK::StreamMgr::SetCurrentLanguage(AKTEXT("English(US)"));

		AkInitSettings InitSettings;
		AkPlatformInitSettings PlatformInitSettings;
		AK::SoundEngine::GetDefaultInitSettings(InitSettings);
		AK::SoundEngine::GetDefaultPlatformInitSettings(PlatformInitSettings);

		if (AK::SoundEngine::Init(&InitSettings, &PlatformInitSettings) != AK_Success)
		{
			AGE_CORE_ASSERT(false, "Could Not Initialize The Sound Engine!");
			return;
		}
		CoreLogger::Trace("Initialized Wwise Sound Engine!");

		//AK::SoundEngine::RegisterGlobalCallback(&MIDICallback, AkGlobalCallbackLocation_PreProcessMessageQueueForRender);

		AK::SoundEngine::GetAudioSettings(m_AudioSettings);

		AkMusicSettings MusicSettings;
		AK::MusicEngine::GetDefaultInitSettings(MusicSettings);
		if (AK::MusicEngine::Init(&MusicSettings) != AK_Success)
		{
			AGE_CORE_ASSERT(false, "Could Not Initialize The Music Engine!");
			return;
		}
		CoreLogger::Trace("Initialized Wwise Music Engine!");

		AkSpatialAudioInitSettings SAInitSettings;
		if (AK::SpatialAudio::Init(SAInitSettings) != AK_Success)
		{
			AGE_CORE_ASSERT(false, "Could Not Initialize The Spatial Audio!");
			return;
		}
		CoreLogger::Trace("Initialized Wwise Spatial Audio!");
#ifndef AK_OPTIMIZED
		AkCommSettings CommSettings;
		AK::Comm::GetDefaultInitSettings(CommSettings);
		if (AK::Comm::Init(CommSettings) != AK_Success)
		{
			AGE_CORE_ASSERT(false, "Could Not Initialize Communication!");
			return;
		}
		CoreLogger::Trace("Initialized Wwise Communication");
#endif // !AK_OPTIMIZED

		//InitPlugins();
	}

	void Wwise::Start()
	{
	}

	void Wwise::Update()
	{
	}

	void Wwise::Stop()
	{
	}

	void Wwise::Shutdown()
	{
#ifndef AK_OPTIMIZED
		AK::Comm::Term();
#endif // !AK_OPTIMIZED

		//AK::SpatialAudio::
		AK::MusicEngine::Term();
		AK::SoundEngine::Term();
		g_LowLevelIO->Term();
		if (AK::IAkStreamMgr::Get())
		{
			AK::IAkStreamMgr::Get()->Destroy();
		}
		AK::MemoryMgr::Term();
	}

	void Wwise::LoadBanks(const std::vector<Ref<SoundBank>> &Banks)
	{
	}

	void Wwise::LoadBank(Ref<SoundBank> Bank)
	{
	}

	std::string & Wwise::GetCurrentEventName()
	{
		return m_MarkerLabel;
	}

	void Wwise::SetCurrentEventName(const std::string &Name)
	{
	}

	bool Wwise::IsEventValid(const std::string& EventName)
	{
		return false;
	}

	void Wwise::SetParameterByName(const std::string &Name, float Value)
	{
	}

	void Wwise::Set3DAttributes(void *Attributes)
	{
	}

	void Wwise::ProcessAudio()
	{
		if (AK::SoundEngine::IsInitialized())
		{
			AK::SoundEngine::RenderAudio();
		}
	}

	void Wwise::SetBasePath(const AkOSChar* Path)
	{
		AKRESULT Result = g_LowLevelIO->SetBasePath(Path);
		AGE_CORE_ASSERT(Result == AK_Success, "Failed to Set Base Path");
		CoreLogger::Warn("Wwise Error: {0} {1}", ProcessResultErrorCode(Result), ProcessResultErrorCode(Result));

	}
#if 0
	void Wwise::LoadBank(const std::string& Name)
	{
		uint32_t BankID;
		AKRESULT eResult = AK::SoundEngine::LoadBank(Name.c_str(), BankID);
		AGE_CORE_ASSERT(eResult == AK_Success, "LoadBank() Failed to Load Soundbank!");

		/**
		const char* pszEvent = EventName.c_str();
		eResult = AK::SoundEngine::PrepareEvent(AK::SoundEngine::Preparation_Load, &pszEvent, 1);
		AGE_CORE_ASSERT(eResult == AK_Success, "Failed to Prepare Load Event!");
		*/
	}

	void Wwise::LoadBank(const uint32_t Name)
	{
		AkBankType BankType = AkBankTypeEnum::AkBankType_User;
		AKRESULT eResult = AK::SoundEngine::LoadBank(Name, BankType);
		AGE_CORE_ASSERT(eResult == AK_Success, "LoadBank() Failed to Load Soundbank!");
	}
#endif
	void Wwise::UnloadBank(const std::string& Name)
	{
		/**
		const char* pszEvent = EventName.c_str();
		AKRESULT eResult = AK::SoundEngine::PrepareEvent(AK::SoundEngine::Preparation_Unload, &pszEvent, 1);
		AGE_CORE_ASSERT(eResult != AK_Success, "Failed to Prepare Unload Event");
		*/

		AKRESULT eResult = AK::SoundEngine::UnloadBank(Name.c_str(), 0);
		AGE_CORE_ASSERT(eResult == AK_Success, "LoadBank() Returned AK_Success!");

	}

	void Wwise::UnloadBank(const uint32_t Name)
	{
		AKRESULT eResult = AK::SoundEngine::UnloadBank(Name, 0);
		AGE_CORE_ASSERT(eResult == AK_Success, "LoadBank() Returned AK_Success!");
	}

	AkPlayingID Wwise::PostMarkerEvent(const char* EventID, uint64_t GameObjID)
	{
		AkPlayingID PlayingID = AK::SoundEngine::PostEvent(EventID, GameObjID);
		return PlayingID;
	}

	AkPlayingID Wwise::PostMarkerEvent(const uint32_t EventID, uint64_t GameObjID)
	{
		AkPlayingID PlayingID = AK::SoundEngine::PostEvent(EventID, GameObjID);

		return PlayingID;
	}

	AKRESULT Wwise::SetPosition(uint64_t GameObjID, AkSoundPosition SoundPos)
	{
		return AK::SoundEngine::SetPosition(GameObjID, SoundPos);
	}

	AKRESULT Wwise::SetRTPCValue(const char* Name, AkRtpcValue nRPM)
	{
		return AK::SoundEngine::SetRTPCValue(Name, nRPM);
	}

	AKRESULT Wwise::SetState(uint32_t StateGroupID, uint32_t StateID)
	{
		return AK::SoundEngine::SetState(StateGroupID, StateID);
	}

	AKRESULT Wwise::SetState(const char* Name, const char* Group)
	{
		return AK::SoundEngine::SetState(Name, Group);
	}

	AKRESULT Wwise::SetSwitch(uint32_t SwitchGroupID, uint32_t SwitchID, uint64_t GameObjID)
	{
		return AK::SoundEngine::SetSwitch(SwitchGroupID, SwitchID, GameObjID);
	}

	AKRESULT Wwise::SetSwitch(const char* SwitchGroup, const char* Switch, uint64_t GameObjID)
	{
		return AK::SoundEngine::SetSwitch(SwitchGroup, Switch, GameObjID);
	}

	void Wwise::ParseSoundBankFile(const std::string& Filepath)
	{


	}

	AKRESULT Wwise::RegisterGameObj(uint64_t GameObjID, const char* Name)
	{

		AKRESULT Result = AK::SoundEngine::RegisterGameObj(GameObjID, Name);
		AGE_CORE_ASSERT(Result == AK_Success, "Failed to Register Game Object!");
		return Result;
	}



	AKRESULT Wwise::UnregisterGameObj(uint64_t GameObjID)
	{
		AKRESULT Result = AK::SoundEngine::UnregisterGameObj(GameObjID);
		AGE_CORE_ASSERT(Result == AK_Success, "Failed to Unregister Game Object!");
		return Result;
	}


	void Wwise::MIDICallback(bool LastCall)
	{
		AkMIDIPost aPosts[2];

		const uint8_t byNote = 60;
		const uint8_t byChan = 0;
		const uint32_t OnOffset = 2;
		const uint32_t OnSamples = 0;
		const uint32_t OffSamples = OnOffset + m_AudioSettings.uNumSamplesPerFrame / 2;

		AkMIDIPost& NoteOn = aPosts[0];
		NoteOn.byType = AK_MIDI_EVENT_TYPE_NOTE_ON;
		NoteOn.byChan = byChan;
		NoteOn.NoteOnOff.byNote = byNote;
		NoteOn.NoteOnOff.byVelocity = 72;
		NoteOn.uOffset = OnSamples;

		AkMIDIPost& NoteOff = aPosts[1];
		NoteOff.byType = AK_MIDI_EVENT_TYPE_NOTE_OFF;
		NoteOff.byChan = byChan;
		NoteOff.NoteOnOff.byNote = byNote;
		NoteOff.NoteOnOff.byVelocity = 0;
		NoteOff.uOffset = OffSamples;

		AkUniqueID EventID = AK::SoundEngine::GetIDFromString("MIDIEventName");
		const AkGameObjectID REGISTERED_MIDI_GAME_OBJECT = 001;

		PostMIDIOnEvent(EventID, REGISTERED_MIDI_GAME_OBJECT, aPosts, 2);
	}
	AkPlayingID Wwise::PostMIDIOnEvent(uint32_t EventID, uint64_t GameObjID, AkMIDIPost* Posts, uint16_t NumPosts)
	{
		return AK::SoundEngine::PostMIDIOnEvent(EventID, GameObjID, Posts, NumPosts);
	}



	const char* Wwise::ProcessResultErrorCode(AKRESULT Code)
	{
		switch (Code)
		{
		case 0:
			return "AK_NotImplemented";
			break;
		case 1:
			return "AK_Success";
			break;
		case 2:
			return "AK_Fail";
			break;
		case 3:
			return "AK_PartialSuccess";
			break;
		case 4:
			return "AK_NotCompatible";
			break;
		case 5:
			return "AK_AlreadyConnected";
			break;
		case 7:
			return "AK_InvalidFile";
			break;
		case 8:
			return "AK_AudioFileHeaderTooLarge";
			break;
		case 9:
			return "AK_MaxReached";
			break;
		case 14:
			return "AK_InvalidID";
			break;
		case 15:
			return "AK_IDNotFound";
			break;
		case 16:
			return "AK_InvalidInstanceID";
			break;
		case 17:
			return "AK_NoMoreData";
			break;
		case 20:
			return "AK_InvalidStateGroup";
			break;
		case 21:
			return "AK_ChildAlreadyHasAParent";
			break;
		case 22:
			return "AK_InvalidLanguage";
			break;
		case 23:
			return "AK_CannotAddItselfAsAChild";
			break;
		case 31:
			return "AK_InvalidParameter";
			break;
		case 35:
			return "AK_ElementAlreadyInList";
			break;
		case 36:
			return "AK_PathNotFound";
			break;
		case 37:
			return "AK_PathNoVertices";
			break;
		case 38:
			return "AK_PathNotRunning";
			break;
		case 39:
			return "AK_PathNotPaused";
			break;
		case 40:
			return "AK_PathNodeAlreadyInList";
			break;
		case 41:
			return "AK_PathNodeNotInList";
			break;
		case 43:
			return "AK_DataNeeded";
			break;
		case 44:
			return "AK_NoDataNeeded";
			break;
		case 45:
			return "AK_DataReady";
			break;
		case 46:
			return "AK_NoDataReady";
			break;
		case 52:
			return "AK_InsufficientMemory";
			break;
		case 53:
			return "AK_Cancelled";
			break;
		case 54:
			return "AK_UnknownBankID";
			break;
		case 56:
			return "AK_BankReadError";
			break;
		case 57:
			return "AK_InvalidSwitchType";
			break;
		case 63:
			return "AK_FormatNotReady";
			break;
		case 64:
			return "AK_WrongBankVersion";
			break;
		case 66:
			return "AK_FileNotFound";
			break;
		case 67:
			return "AK_DeviceNotReady";
			break;
		case 69:
			return "AK_BankAlreadyLoaded";
			break;
		case 71:
			return "AK_RenderedFX";
			break;
		case 72:
			return "AK_ProcessNeeded";
			break;
		case 73:
			return "AK_ProcessDone";
			break;
		case 74:
			return "AK_MemManagerNotInitialized";
			break;
		case 75:
			return "AK_StreamMgrNotInitialized";
			break;
		case 76:
			return "AK_SSEInstructionsNotSupported";
			break;
		case 77:
			return "AK_Busy";
			break;
		case 78:
			return "AK_UnsupportedChannelConfig";
			break;
		case 79:
			return "AK_PluginMediaNotAvailable";
			break;
		case 80:
			return "AK_MustBeVirtualized";
			break;
		case 81:
			return "AK_CommandTooLarge";
			break;
		case 82:
			return "AK_RejectedByFilter";
			break;
		case 83:
			return "AK_InvalidCustomPlatformName";
			break;
		case 84:
			return "AK_DLLCannotLoad";
			break;
		case 85:
			return "AK_DLLPathNotFound";
			break;
		case 86:
			return "AK_NoJavaVM";
			break;
		case 87:
			return "AK_OpenSLError";
			break;
		case 88:
			return "AK_PluginNotRegistered";
			break;
		case 89:
			return "AK_DataAlignmentError";
			break;
		case 90:
			return "AK_DeviceNotCompatible";
			break;
		case 91:
			return "AK_DuplicateUniqueID";
			break;
		case 92:
			return "AK_InitBankNotLoaded";
			break;
		case 93:
			return "AK_DeviceNotFound";
			break;
		case 94:
			return "AK_PlayingIDNotFound";
			break;
		case 95:
			return "AK_InvalidFloatValue";
			break;
		case 96:
			return "AK_FileFormatMismatch";
			break;
		case 97:
			return "AK_NoDistinctListener";
			break;
		case 98:
			return "AK_ACP_Error";
			break;
		case 99:
			return "AK_ResourceInUse";
			break;
		case 100:
			return "AK_InvalidBankType";
			break;
		case 101:
			return "AK_AlreadyInitialized";
			break;
		case 102:
			return "AK_NotInitialized";
			break;
		case 103:
			return "AK_FilePermissionError";
			break;
		case 104:
			return "AK_UnknownFileError";
			break;
		case 105:
			return "AK_TooManyConcurrentOperations";
			break;
		case 106:
			return "AK_InvalidFileSize";
			break;
		case 107:
			return "AK_Deferred";
			break;
		case 108:
			return "AK_FilePathTooLong";
			break;
		case 109:
			return "AK_InvalidState";
			break;
		}

		return "Code Not Recognized!";
	}

	template<>
	Wwise* AudioEngine::As()
	{
		return (Wwise*)this;
	}
}