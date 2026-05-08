#include "AGEpch.hpp"

#if WITH_WWISE
#include "Audio/Wwise/Public/WWiseEngine.h"
#include "Core/Public/Log.h"

namespace AGE
{
	/**
 * @brief Constructor for the Wwise class. Initializes the low-level IO object and calls Init().
 */
Wwise::Wwise()
	{
		g_LowLevelIO = new CAkFilePackageLowLevelIODeferred();
		Init();
	}

	/**
 * @brief Destructor for the Wwise class.
 * 
 * This function is responsible for cleaning up any resources that were allocated during the lifetime of the object, such as shutting down the audio engine.
 */
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
			CoreLogger::Assert(false, "Could Not Create The Memory Manager!");
			return;

		}

		CoreLogger::Trace("Initialized Wwise Memory Manager!");
		AkStreamMgrSettings StmSettings;
		AK::StreamMgr::GetDefaultSettings(StmSettings);
		if (!AK::StreamMgr::Create(StmSettings))
		{
			CoreLogger::Assert(false, "Could Not Create The Streaming Manager!");
			return;
		}
		CoreLogger::Trace("Initialized Wwise Streaming Manager!");


		AkDeviceSettings DeviceSettings;
		AK::StreamMgr::GetDefaultDeviceSettings(DeviceSettings);

		if (g_LowLevelIO->Init(DeviceSettings) != AK_Success)
		{
			CoreLogger::Assert(false, "Could Not Create The Streaming Device and Low-Level I/O System!");
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
			CoreLogger::Assert(false, "Could Not Initialize The Sound Engine!");
			return;
		}
		CoreLogger::Trace("Initialized Wwise Sound Engine!");

		//AK::SoundEngine::RegisterGlobalCallback(&MIDICallback, AkGlobalCallbackLocation_PreProcessMessageQueueForRender);

		AK::SoundEngine::GetAudioSettings(m_AudioSettings);

		AkMusicSettings MusicSettings;
		AK::MusicEngine::GetDefaultInitSettings(MusicSettings);
		if (AK::MusicEngine::Init(&MusicSettings) != AK_Success)
		{
			CoreLogger::Assert(false, "Could Not Initialize The Music Engine!");
			return;
		}
		CoreLogger::Trace("Initialized Wwise Music Engine!");

		AkSpatialAudioInitSettings SAInitSettings;
		if (AK::SpatialAudio::Init(SAInitSettings) != AK_Success)
		{
			CoreLogger::Assert(false, "Could Not Initialize The Spatial Audio!");
			return;
		}
		CoreLogger::Trace("Initialized Wwise Spatial Audio!");
#ifndef AK_OPTIMIZED
		AkCommSettings CommSettings;
		AK::Comm::GetDefaultInitSettings(CommSettings);
		if (AK::Comm::Init(CommSettings) != AK_Success)
		{
			CoreLogger::Assert(false, "Could Not Initialize Communication!");
			return;
		}
		CoreLogger::Trace("Initialized Wwise Communication");
#endif // !AK_OPTIMIZED

		//InitPlugins();
	}

	/**
 * @brief Start the audio engine.
 *
 * This function initializes and starts the audio engine. It does not start any sounds or music, it only prepares the 
 * environment for them.
 *
 * @return void
 */
void Wwise::Start()
	{
	}

	/**
 * @brief This function updates the audio engine.
 *
 * The Update function is responsible for processing all events and updating the state of the audio engine. 
 * It does not take any parameters and returns void.
 */
void Wwise::Update()
	{
	}

	/**
 * @brief Stops all currently playing audio in the Wwise engine.
 * 
 * This function is used to stop all sounds that are currently being played by the Wwise engine. It will not interrupt any ongoing sound sequences or music tracks, but it will halt all other types of sounds immediately.
 * 
 * @return void
 */
void Wwise::Stop()
	{
	}

	/**
 * @brief This function is used to shutdown the Wwise audio engine. 
 * It includes terminating various components of the Wwise system such as the communication module, music and sound engines, low-level I/O, stream manager, and memory manager.
 * The function does not take any parameters and returns void.
 */
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

	/**
 * @brief Loads a collection of Sound Banks into the Wwise engine.
 * 
 * This function takes in a vector of references to Sound Bank objects and loads them into the Wwise engine for use.
 * Each SoundBank object contains information about a particular audio bank that can be loaded into the Wwise engine.
 * The function does not return anything, it simply modifies the state of the Wwise engine based on the input parameters.
 * 
 * @param Banks A vector of references to Sound Bank objects to load.
 */
void Wwise::LoadBanks(const std::vector<Ref<SoundBank>> &Banks)
	{
	}

	/**
 * @brief Loads a SoundBank into the Wwise engine.
 * 
 * This function takes in a reference to a SoundBank object and loads it into the Wwise engine. The exact behavior of this function depends on how the SoundBank is implemented, but generally it should involve some form of loading operation that sets up the sound data for use by the Wwise engine.
 * 
 * @param Bank A reference to a SoundBank object containing the sound data to be loaded into the Wwise engine.
 * @return void This function does not return any value.
 */
void Wwise::LoadBank(Ref<SoundBank> Bank)
	{
	}

	/**
 * @brief Get the name of the current event in the Wwise sound engine.
 *
 * This function returns a reference to the string that holds the label for the currently playing event in the Wwise sound engine. 
 * The returned string is updated whenever an event starts or changes, so it represents the most recent event.
 *
 * @return A reference to the current event name string.
 */
std::string & Wwise::GetCurrentEventName()
	{
		return m_MarkerLabel;
	}

	/**
 * @brief This function sets the current event name in the Wwise audio engine.
 *
 * @param Name The new name for the current event.
 */
void Wwise::SetCurrentEventName(const std::string &Name)
	{
	}

	/**
 *  @brief Checks if the given event name is valid in the Wwise system.
 *  
 *  This function takes an event name as input and checks whether it exists in the Wwise system or not.
 *  
 *  @param EventName The name of the event to be checked.
 *  @return Returns true if the event is valid, false otherwise. If the event name is empty or contains only whitespace characters, this function will return false.
 */
bool Wwise::IsEventValid(const std::string& EventName)
	{
		return false;
	}

	/**
 * @brief This function sets a parameter by its name in the Wwise sound engine.
 * 
 * @param Name The name of the parameter to be set.
 * @param Value The new value for the parameter.
 * 
 * @return void
 */
void Wwise::SetParameterByName(const std::string &Name, float Value)
	{
	}

	/**
 * @brief This function sets the 3D attributes for a sound object in the Wwise audio engine.
 * 
 * @param Attributes A pointer to an instance of the Wwise::AK::SpatialAudioParams structure, which contains the new 3D attributes for the sound object.
 * 
 * @return void This function does not return any value.
 */
void Wwise::Set3DAttributes(void *Attributes)
	{
	}

	/**
 * @brief This function processes the audio using Wwise's Sound Engine.
 *
 * The function checks if the AK::SoundEngine is initialized by calling IsInitialized(). If it is, 
 * then RenderAudio() is called to process the audio.
 */
void Wwise::ProcessAudio()
	{
		if (AK::SoundEngine::IsInitialized())
		{
			AK::SoundEngine::RenderAudio();
		}
	}

	/**
 * @brief This function sets the base path for Wwise.
 *
 * @param Path The new base path to be set.
 * 
 * @return void
 */
void Wwise::SetBasePath(const AkOSChar* Path)
	{
		AKRESULT Result = g_LowLevelIO->SetBasePath(Path);
		CoreLogger::Assert(Result == AK_Success, "Failed to Set Base Path");
		CoreLogger::Warn("Wwise Error: {0} {1}", ProcessResultErrorCode(Result), ProcessResultErrorCode(Result));

	}
#if 0
	/**
 * @brief This function loads a soundbank into the Wwise SoundEngine.
 *
 * The function takes in a string parameter 'Name' which represents the name of the bank file that needs to be loaded. 
 * It then uses this name to load the bank using AK::SoundEngine::LoadBank() method. If the loading is successful, it returns AK_Success; otherwise, an error message is logged and thrown.
 * The function does not return any value as indicated by @return statement.
 * 
 * @param Name The name of the bank file to be loaded.
 */
void Wwise::LoadBank(const std::string& Name)
	{
		uint32_t BankID;
		AKRESULT eResult = AK::SoundEngine::LoadBank(Name.c_str(), BankID);
		CoreLogger::Assert(eResult == AK_Success, "LoadBank() Failed to Load Soundbank!");

		/**
		const char* pszEvent = EventName.c_str();
		eResult = AK::SoundEngine::PrepareEvent(AK::SoundEngine::Preparation_Load, &pszEvent, 1);
		CoreLogger::Assert(eResult == AK_Success, "Failed to Prepare Load Event!");
		*/
	}

	/**
 * @brief This function loads a sound bank into the Wwise audio engine.
 * 
 * @param Name The name of the sound bank file without extension.
 * @return void
 */
void Wwise::LoadBank(const uint32_t Name)
	{
		AkBankType BankType = AkBankTypeEnum::AkBankType_User;
		AKRESULT eResult = AK::SoundEngine::LoadBank(Name, BankType);
		CoreLogger::Assert(eResult == AK_Success, "LoadBank() Failed to Load Soundbank!");
	}
#endif
	/**
 * @brief Unloads a sound bank from the Wwise Sound Engine.
 *
 * This function takes in a string parameter representing the name of the sound bank to be unloaded. 
 * It prepares an event for unloading and then unloads the specified bank using AK::SoundEngine::UnloadBank(). 
 * If the unloading operation fails, it logs an error message via CoreLogger::Assert().
 *
 * @param Name The name of the sound bank to be unloaded.
 */
void Wwise::UnloadBank(const std::string& Name)
	{
		/**
		const char* pszEvent = EventName.c_str();
		AKRESULT eResult = AK::SoundEngine::PrepareEvent(AK::SoundEngine::Preparation_Unload, &pszEvent, 1);
		CoreLogger::Assert(eResult != AK_Success, "Failed to Prepare Unload Event");
		*/

		AKRESULT eResult = AK::SoundEngine::UnloadBank(Name.c_str(), 0);
		CoreLogger::Assert(eResult == AK_Success, "LoadBank() Returned AK_Success!");

	}

	/**
 * @brief Unloads a sound bank from the Wwise Sound Engine.
 *
 * This function attempts to unload a soundbank with the given name from the Wwise Sound Engine. 
 * It uses the AK::SoundEngine::UnloadBank() function for this purpose, which expects an unsigned integer parameter representing the name of the bank and an additional flag indicating whether or not to wait for the operation to complete.
 * The function then checks if the result is equal to AK_Success. If it's not, a CoreLogger Assertion will be triggered with an error message indicating that LoadBank() did not return AK_Success. 
 * This indicates that there was an issue unloading the bank and should be investigated for potential sound engine issues.
 */
void Wwise::UnloadBank(const uint32_t Name)
	{
		AKRESULT eResult = AK::SoundEngine::UnloadBank(Name, 0);
		CoreLogger::Assert(eResult == AK_Success, "LoadBank() Returned AK_Success!");
	}

	/**
 * @brief Posts a marker event to the Wwise sound engine.
 *
 * This function posts an event with the specified EventID and GameObjID to the Wwise sound engine. 
 * The function returns the playing ID of the posted event, which can be used for further control over the audio playback.
 *
 * @param EventID A string representing the identifier of the event to post.
 * @param GameObjID An unsigned 64-bit integer representing the game object associated with the event.
 *
 * @return The playing ID of the posted event, which can be used for further control over the audio playback.
 */
AkPlayingID Wwise::PostMarkerEvent(const char* EventID, uint64_t GameObjID)
	{
		AkPlayingID PlayingID = AK::SoundEngine::PostEvent(EventID, GameObjID);
		return PlayingID;
	}

	/**
 * @brief Posts a marker event to the Wwise sound engine.
 *
 * This function posts an event with the given Event ID and Game Object ID to the Wwise sound engine. 
 * The function returns the playing ID of the posted event, which can be used for further control over the event.
 *
 * @param EventID The ID of the event to post.
 * @param GameObjID The ID of the game object associated with the event.
 * @return The playing ID of the posted event.
 */
AkPlayingID Wwise::PostMarkerEvent(const uint32_t EventID, uint64_t GameObjID)
	{
		AkPlayingID PlayingID = AK::SoundEngine::PostEvent(EventID, GameObjID);

		return PlayingID;
	}

	/**
 * @brief Set the position of a sound object in the 3D space.
 *
 * This function sets the position and orientation of a sound object in the 3D space. The GameObjID is used to identify the sound object, while SoundPos contains the new position and orientation data for this object.
 *
 * @param GameObjID Unique identifier for the sound object.
 * @param SoundPos Structure containing the new position and orientation of the sound object.
 *
 * @return AKRESULT indicating success or failure of the operation.
 */
AKRESULT Wwise::SetPosition(uint64_t GameObjID, AkSoundPosition SoundPos)
	{
		return AK::SoundEngine::SetPosition(GameObjID, SoundPos);
	}

	/** 
 * @brief This function sets the real-time parameter control (RTPC) value for a specified RTPC.
 * @param Name The name of the RTPC to set.
 * @param nRPM The new value for the RTPC.
 * @return AKRESULT indicating success or failure of the operation.
 */
AKRESULT Wwise::SetRTPCValue(const char* Name, AkRtpcValue nRPM)
	{
		return AK::SoundEngine::SetRTPCValue(Name, nRPM);
	}

	/**
 * @brief This function sets the state of a given group in Wwise sound engine.
 * 
 * @param StateGroupID The ID of the state group to be set.
 * @param StateID The ID of the state within the specified state group.
 * 
 * @return AKRESULT Returns the result of setting the state, indicating success or failure.
 */
AKRESULT Wwise::SetState(uint32_t StateGroupID, uint32_t StateID)
	{
		return AK::SoundEngine::SetState(StateGroupID, StateID);
	}

	/**
 * @brief This function sets the state of a sound object in the Wwise Sound Engine.
 * 
 * @param Name The name of the state to be set.
 * @param Group The group that contains the state to be set.
 * 
 * @return AKRESULT Returns the result of the SetState operation.
 */
AKRESULT Wwise::SetState(const char* Name, const char* Group)
	{
		return AK::SoundEngine::SetState(Name, Group);
	}

	/**
 * @brief Set a switch in the Wwise sound engine.
 * 
 * This function sets a specific switch within a group to a certain value for a given game object. The switch is identified by its Group ID, Switch ID and Game Object ID.
 * 
 * @param SwitchGroupID The unique identifier of the switch group.
 * @param SwitchID The unique identifier of the switch within the group.
 * @param GameObjID The unique identifier of the game object for which to set the switch.
 * 
 * @return AKRESULT indicating success or failure of the operation.
 */
AKRESULT Wwise::SetSwitch(uint32_t SwitchGroupID, uint32_t SwitchID, uint64_t GameObjID)
	{
		return AK::SoundEngine::SetSwitch(SwitchGroupID, SwitchID, GameObjID);
	}

	/**
 * @brief Set a Wwise switch for a specific game object.
 * 
 * This function sets the value of a Wwise switch for a given group and name in the SoundEngine. The switch is associated with a particular game object, specified by its ID.
 *
 * @param SwitchGroup The name of the switch group to set.
 * @param Switch The name of the switch to set within the group.
 * @param GameObjID The unique identifier for the game object whose sound environment should be modified.
 * 
 * @return An AKRESULT indicating whether the operation was successful or not.
 */
AKRESULT Wwise::SetSwitch(const char* SwitchGroup, const char* Switch, uint64_t GameObjID)
	{
		return AK::SoundEngine::SetSwitch(SwitchGroup, Switch, GameObjID);
	}

	/**
 * @brief Parses a sound bank file using the given file path.
 * 
 * This function reads and parses a sound bank file specified by its file path, which is passed as an argument to this function. The format of the sound bank file can vary depending on the specific implementation of Wwise used in your project.
 *
 * @param Filepath A constant string reference representing the file path of the sound bank file to be parsed. This parameter should contain the full or relative path to the sound bank file that you want to parse.
 * 
 * @return void No return value is expected from this function as it directly modifies internal data structures based on the content of the sound bank file.
 */
void Wwise::ParseSoundBankFile(const std::string& Filepath)
	{


	}

	/**
 * @brief Registers a game object with the Wwise sound engine.
 *
 * This function registers a game object with the Wwise sound engine using its ID and name. 
 * The result of this operation is returned, indicating whether the registration was successful or not.
 *
 * @param GameObjID The unique identifier for the game object to be registered.
 * @param Name A string representing the name of the game object to be registered.
 * @return An enumeration value indicating the success (AK_Success) or failure of the operation.
 */
AKRESULT Wwise::RegisterGameObj(uint64_t GameObjID, const char* Name)
	{

		AKRESULT Result = AK::SoundEngine::RegisterGameObj(GameObjID, Name);
		CoreLogger::Assert(Result == AK_Success, "Failed to Register Game Object!");
		return Result;
	}



	/**
 * @brief This function unregisters a game object from the Wwise sound engine.
 * 
 * @param GameObjID The ID of the game object to be unregistered.
 * @return AKRESULT Returns the result of the operation, indicating success or failure.
 */
AKRESULT Wwise::UnregisterGameObj(uint64_t GameObjID)
	{
		AKRESULT Result = AK::SoundEngine::UnregisterGameObj(GameObjID);
		CoreLogger::Assert(Result == AK_Success, "Failed to Unregister Game Object!");
		return Result;
	}


	/**
 * @brief This function is responsible for handling MIDI events. It generates two MIDI notes (NoteOn and NoteOff) based on the provided parameters and sends them to the Sound Engine using PostMIDIOnEvent().
 * 
 * @param LastCall A boolean value indicating whether this is the last call in a sequence of calls. If true, it means that all subsequent calls will be the final ones in the sequence.
 * 
 * @return void
 */
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
	/**
 * @brief This function posts a MIDI event to the Wwise sound engine.
 * 
 * @param EventID The ID of the MIDI event to be posted.
 * @param GameObjID The ID of the game object associated with the MIDI event.
 * @param Posts A pointer to an array of AkMIDIPost structures containing information about the MIDI events.
 * @param NumPosts The number of elements in the Posts array.
 * 
 * @return Returns the ID of the playing instance that corresponds to the posted event. If no such instance exists, it returns AK_INVALID_PLAYING_ID.
 */
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
	/**
 * @brief This function returns a pointer to the Wwise object associated with this instance of AudioEngine.
 * @return A pointer to the Wwise object, or nullptr if no such association exists.
 */
Wwise* AudioEngine::As()
	{
		return (Wwise*)this;
	}
}
#endif //WITH_WWISE