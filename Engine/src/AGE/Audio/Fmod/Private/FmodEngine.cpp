#include "AGEpch.hpp"
#if WITH_FMOD
#include "Audio/Fmod/Public/FmodEngine.h"
#include "Audio/AGESound/Public/Sound.h"
#include "Core/Public/Log.h"

namespace AGE
{
	namespace Util
	{
		//TODO: Complete this
		/**
 * @brief Converts an FMOD result code to its corresponding string representation.
 *
 * This function takes in a reference to an FMOD_RESULT and returns the string representation of that result code.
 * The returned string is specific to the FMOD library, providing detailed information about any errors or warnings that may have occurred during audio playback.
 * 
 * @param Code A reference to an FMOD_RESULT representing the error code to be converted.
 * @return A string representation of the provided FMOD result code. If the input is not a valid FMOD result code, an empty string is returned.
 */
/**
 * @brief This function returns a string representation of an FMOD result code.
 * @param[in] Code The FMOD result code to be converted into a string.
 * @return A string representing the input FMOD result code, or "Unknown" if the code is not recognized.
 */
static std::string FMOD_ErrorString(FMOD_RESULT& Code)
		{
			return "";
		}
	}

	/**
 * @brief FmodEngine is a class that initializes the FMOD engine for audio playback in the game.
 * 
 * The constructor of this class, `FmodEngine::FmodEngine()`, calls the `Init()` function to initialize the FMOD system. This function sets up all necessary parameters and resources for audio playback.
 * 
 * @return An instance of the FmodEngine class with the FMOD engine initialized.
 */
/**
 * @brief FmodEngine is a class that initializes the FMOD engine for audio playback in the game. 
 * It has an initialization function Init().
 */
FmodEngine::FmodEngine()
	{
		Init();
	}
	/**
 * @brief Destructor for the FMOD engine class.
 * 
 * This function is responsible for cleaning up any resources used by the FMOD engine when it's no longer needed. It calls the Shutdown() method to ensure all sounds and other resources are properly cleaned up.
 */
/**
 * @brief Destructor for the FMOD engine class.
 * 
 * This function is responsible for cleaning up any resources used by the FMOD engine, such as sound objects and channels. It calls the Shutdown() method to perform this cleanup.
 */
FmodEngine::~FmodEngine()
	{
		Shutdown();
	}
	"/**\n * @brief Initialize the FMOD engine.\n * This function sets up basic settings for FMOD system.\n * It creates a new instance of FMOD Studio System,\n * checks if creation was successful, sets number of listeners to 1,\n * enables advanced settings, gets core system pointer,\n * sets output type and software format.\n * Then it initializes the FMOD system with buffer size\n * and normal priority. If any step fails, an error message is logged and program exits."

void FmodEngine::Init()
	{
		FMOD_RESULT Result;
		FMOD_STUDIO_ADVANCEDSETTINGS Settings{};
		FMOD::System* Sys;
		Sys = 0;

		Result = FMOD::Studio::System::create(&m_System);
		if (Result != FMOD_OK)
		{
			CoreLogger::Error("FMOD Error! \n{0}\n\t Failed to Create FMod System Instance!", (int)Result); // Write a util to basically convert that enum to a string
			CoreLogger::Critical("Fmod Not Initialized! Exiting!");
			return;
		}
		CoreLogger::Info("FMod Initialized Successfully!");
		m_System->setNumListeners(1);
		m_System->setAdvancedSettings(&Settings);
		m_System->getCoreSystem(&Sys);
		Sys->setOutput(FMOD_OUTPUTTYPE_AUTODETECT);
		Sys->setSoftwareFormat(44100, FMOD_SPEAKERMODE_STEREO, 2);

		Result = m_System->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0);
		if (Result != FMOD_OK)
		{
			CoreLogger::Error("FMOD Error! \n{0}\n\t Failed to Initialize FMod System Instance!", (int)Result); // Write a util to basically convert that enum to a string
			CoreLogger::Critical("Fmod Not Initialized! Exiting!");
			return;
		}

	}

	/**
 * @brief Starts the current event instance.
 * 
 * This function starts the currently playing or paused audio event instance. It uses FMOD's start() method to do so.
 *
 * @return void
 */
/**
 * @brief Starts the current event instance.
 * 
 * This function starts the currently playing or paused event instance. If no event is currently playing, this will start a new one.
 */
void FmodEngine::Start()
	{
		m_CurrentEventInstance->start();

	}

	/**
 * @brief This function updates the FMOD system. 
 * It is used to update the internal state of the FMOD engine, which includes processing any events that have occurred since the last call to this function.
 *
 * @return void
 */
/**
 * @brief This function updates the FMOD system. 
 * It is used to update all sound devices and channels in the system, which are necessary for proper operation of audio playback.
 *
 * @return void
 */
void FmodEngine::Update()
	{
		m_System->update();
	}

	/**
 * @brief Stops the current event instance.
 * 
 * This function stops the currently playing event instance with a fadeout allowing it to finish its playback before being stopped.
 * It does not handle any exceptions or errors that might occur during the execution of this function.
 *
 * @return void
 */
/** 
 * @brief Stops the current event instance.
 *
 * This function stops the currently playing event instance with a fadeout allowing it to finish its playback before being stopped.
 *
 * @return void
 */
void FmodEngine::Stop()
	{
		m_CurrentEventInstance->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT);
	}

	/**
 * @brief Shuts down the FMOD engine and releases all resources associated with it.
 * 
 * This function iterates over two maps (`m_Events`, `m_Sounds`) and three vectors (`m_Banks`), each of which contain pointers to objects that have been allocated using the FMOD API. It calls the release method on these objects to free up their resources. Finally, it releases the main system object with the release method.
 * 
 * @return void
 */
/**
 * @brief Shuts down the FMOD engine and releases all resources associated with it.
 * 
 * This function iterates over two maps (`m_Events`, `m_Sounds`) and three vectors (`m_Banks`), each of which contain pointers to objects that have been created using the FMOD API. It calls the `release()` method on these objects to free up their resources. Finally, it releases the main system object with the `release()` method.
 * 
 * @return void
 */
void FmodEngine::Shutdown()
	{
		for (auto K : m_Events)
		{
			K.second->release();
		}

		for (auto K : m_Sounds)
		{
			K.second->release();
		}

		for (auto K : m_Banks)
		{
			K.second->unloadSampleData();
			K.second->unload();
		}

		m_System->release();
	}

	/**
 * @brief Loads a collection of SoundBanks from the given list.
 *
 * This function iterates over each SoundBank in the provided vector and loads it using the 
 * `LoadBankFromFile` method, passing the file path of each SoundBank to do so.
 *
 * @param Banks A constant reference to a vector of SoundBanks that need to be loaded. Each SoundBank's 
 *              file path is used as an argument for the `LoadBankFromFile` method.
 */
/**
 * @brief Loads a collection of SoundBanks from the given list.
 *
 * This function iterates over each SoundBank in the provided vector and loads it using the 
 * `LoadBankFromFile` method, passing the file path of each SoundBank to do so.
 *
 * @param Banks A constant reference to a vector of SoundBanks that need to be loaded.
 */
void FmodEngine::LoadBanks(const std::vector<Ref<SoundBank>>& Banks)
	{
		for (auto& B : Banks)
		{
			LoadBankFromFile(B->GetFilePath().string());
		}
	}

	/**
 * @brief Loads a sound bank into the FMOD engine.
 * 
 * This function takes a reference to a SoundBank object and loads its associated file into the FMOD engine using the `LoadBankFromFile` method. The path of the soundbank file is obtained from the SoundBank object's GetFilePath() method.
 *
 * @param Bank A reference to the SoundBank object that contains information about the bank to be loaded.
 */
/** 
 * @brief Loads a sound bank into the FMOD engine.
 * @param Bank A reference to the SoundBank object that contains information about the bank to be loaded.
 * @return void
 */
void FmodEngine::LoadBank(Ref<SoundBank> Bank)
	{
		LoadBankFromFile(Bank->GetFilePath().string());
	}

	

void FmodEngine::LoadEvents()
	{
		for (auto KV : m_Banks)
		{
			KV.second->loadSampleData();
		}

		int StringCount = 0;
		m_Banks["Master.strings"]->getStringCount(&StringCount);
		std::vector<std::string> BankStrings(StringCount);
		for (int i= 0; i < StringCount; ++i)
		{
			FMOD_GUID ID;
			char* Path = new char[2048];
			int* Retrieved = new int;
			m_Banks["Master.strings"]->getStringInfo(i,&ID,Path, 2048, Retrieved);
			BankStrings[i] = Path;
			delete[] Path;
			delete Retrieved;
		}

		for (auto S : BankStrings)
		{
			if (S.starts_with("event:/"))
			{
				CreateFmodEvent(S);
			}
		}
	}

	/**
 * @brief Sets the name of the current event instance. If the provided name corresponds to an existing event, it sets the current event instance to that event.
 * 
 * @param Name The new name for the current event instance.
 */
/**
 * @brief Sets the name of the current event instance. If the provided name corresponds to an existing event, it sets the current event instance to that event.
 * 
 * @param Name The new name for the current event instance.
 */
void FmodEngine::SetCurrentEventName(const std::string &Name)
	{
		m_CurrentEventInstanceName = Name;

		if (m_Events.contains(m_CurrentEventInstanceName))
		{
			m_CurrentEventInstance = m_Events[m_CurrentEventInstanceName];
			return;
		}

	}

	/**
 * @brief Checks if the event with given name is valid.
 * 
 * This function takes a string parameter representing the name of an event, and returns a boolean indicating whether or not this event exists in the FMOD engine's events map.
 * 
 * @param EventName The name of the event to check for validity.
 * @return True if the event is valid (exists in the m_Events map), false otherwise.
 */
/** 
 * @brief Checks if an event is valid.
 * 
 * This function takes a string parameter representing the name of an event and checks if it exists in the events map. If the event exists, it returns true; otherwise, false.
 * 
 * @param EventName The name of the event to check for validity.
 * @return True if the event is valid (exists in the events map), false otherwise.
 */
bool FmodEngine::IsEventValid(const std::string& EventName)
	{
		return m_Events[EventName]->isValid();
	}

	/**
 * @brief Sets a parameter value by its name in the FMOD engine.
 *
 * This function sets the value of a parameter specified by its name. The parameter is identified by its name, which must be unique within the event system. 
 * If the parameter does not exist, this function will have no effect.
 *
 * @param Name A constant reference to a string representing the name of the parameter.
 * @param Value A float representing the new value for the parameter.
 *
 * @return void
 */
/**
 * @brief Sets a parameter by its name in the FMOD engine.
 *
 * This function sets a parameter value by its name in the FMOD engine. The parameter is identified by its name, which must be unique within the event. 
 * If the parameter does not exist, this function will have no effect and return immediately.
 *
 * @param Name A const reference to std::string representing the name of the parameter.
 * @param Value A float representing the new value for the parameter.
 *
 * @return void
 */
void FmodEngine::SetParameterByName(const std::string &Name, float Value)
	{
		GetCurrentEvent()->setParameterByName(Name.c_str(),Value);
	}

	/**
 * @brief Sets the 3D attributes for the current event.
 * 
 * This function sets the 3D attributes of the current FMOD event using a pointer to an instance of `FMOD_3D_ATTRIBUTES` struct. The struct contains information about the position, velocity and occlusion of the sound source in 3D space.
 * 
 * @param Attributes A pointer to an instance of `FMOD_3D_ATTRIBUTES` struct containing the 3D attributes for the event.
 * 
 * @return void
 */
/**
 * @brief Sets the 3D attributes for the current event.
 * 
 * This function sets the 3D attributes of the current FMOD event using a pointer to an instance of `FMOD_3D_ATTRIBUTES` struct. The struct contains information about the position, velocity and occlusion of the sound source in 3D space.
 * @param Attributes A pointer to an instance of `FMOD_3D_ATTRIBUTES` struct containing the 3D attributes for the event.
 */
void FmodEngine::Set3DAttributes(void *Attributes)
	{
		FMOD_3D_ATTRIBUTES* Attribs{};
		Attribs = reinterpret_cast<FMOD_3D_ATTRIBUTES*>(Attributes);
		GetCurrentEvent()->set3DAttributes(Attribs);
	}

	

void FmodEngine::LoadBankFromFile(const std::string& FileName)
	{
		FMOD_RESULT Result;
		std::string Tmp;
		FMOD::Studio::Bank* Bank;
		Result = m_System->loadBankFile(FileName.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &Bank);
		if (Result != FMOD_OK)
		{
			CoreLogger::Error("FMOD Error! \n{0}\n\t Failed to Load Bank at {1}!", (int)Result, FileName); // Write a util to basically convert that enum to a string
			return;
		}
		Tmp = FileName.substr(FileName.find_last_of("/\\") + 1);
		std::string::size_type const p(Tmp.find_last_of("."));
		std::string Name = Tmp.substr(0, p);
		CoreLogger::Info("Bank: {0} Loaded Sucessfully!", Name);

		m_Banks.emplace(std::pair<std::string, FMOD::Studio::Bank*>(Name, Bank));

	}

	/**
 * @brief Loads a bank of sound effects and music from memory.
 *
 * This function loads a bank of sound effects and music into the FMOD engine from a block of memory. The data is expected to be in the format that FMOD can understand, such as .bank files. 
 *
 * @param Data A pointer to the start of the memory block containing the sound bank data.
 * @return void
 */
/**
 * @brief Loads a bank of sound effects and music from memory.
 *
 * This function loads a bank of sound effects and music into the FMOD engine from a block of memory. The data is expected to be in a format that FMOD can understand, such as an .bnk file for FMOD Studio projects or an .pak file for FMOD Ex projects. 
 *
 * @param Data A pointer to the start of the sound bank data. This should point to a block of memory containing the sound bank data.
 *
 * @return void
 */
void FmodEngine::LoadBankFromMemory(const char* Data)
	{
		CoreLogger::Assert(false, "Not Implemented!");
	}

	/**
 * @brief Creates a new Fmod event instance from the provided string.
 * 
 * The function takes an event string as input and creates a new FMOD event instance using it. It extracts the name of the event from the string, which is then used as the key for storing the event instance in a map. If the event description does not exist, no action is taken.
 * 
 * @param EventString The string representation of the event to be created. This should include the path and filename of the event.
 * 
 * @return void No return value.
 */

void FmodEngine::CreateFmodEvent(const std::string &EventString)
	{
		FMOD::Studio::EventDescription* Desc;
		GetSystem()->getEvent(EventString.c_str(), &Desc);
		std::string Tmp;
		Tmp = EventString.substr(EventString.find_last_of("/\\") + 1);
		std::string::size_type const p(Tmp.find_last_of("\n"));
		std::string Name = Tmp.substr(0, p);

		if (Desc)
		{
			FMOD::Studio::EventInstance* Instance;
			Desc->createInstance(&Instance);
			m_Events.emplace(std::pair<std::string, FMOD::Studio::EventInstance*>(Name, Instance));
		}
	}

	template<>
	/**
 * @brief This function returns a pointer to the FmodEngine object.
 *
 * The function is used to return an instance of the FmodEngine class as its base type, which allows for polymorphism and dynamic binding. 
 * It does this by returning 'this' casted to the FmodEngine* type. This means that it returns a pointer to itself but with the type of FmodEngine*.
 *
 * @return A pointer to an instance of the FmodEngine class.
 */
/**
 * @brief This function returns a pointer to the FmodEngine object.
 * 
 * @return A pointer to an instance of FmodEngine.
 */
FmodEngine* AudioEngine::As()
	{
		return (FmodEngine*)this;
	}
}
#endif //WITH_FMOD