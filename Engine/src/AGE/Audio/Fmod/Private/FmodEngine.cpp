#include "AGEpch.hpp"
#include "Audio/Fmod/Public/FmodEngine.h"
#include "Audio/AGESound/Public/Sound.h"

namespace AGE
{
	namespace Util
	{
		//TODO: Complete this
		static std::string FMOD_ErrorString(FMOD_RESULT& Code)
		{
			return "";
		}
	}

	FmodEngine::FmodEngine()
	{
		Init();
	}
	FmodEngine::~FmodEngine()
	{
		Shutdown();
	}
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

	void FmodEngine::Start()
	{
		m_CurrentEventInstance->start();

	}

	void FmodEngine::Update()
	{
		m_System->update();
	}

	void FmodEngine::Stop()
	{
		m_CurrentEventInstance->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT);
	}

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

	void FmodEngine::LoadBanks(const std::vector<Ref<SoundBank>>& Banks)
	{
		for (auto& B : Banks)
		{
			LoadBankFromFile(B->GetFilePath().string());
		}
	}

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
			delete[] Retrieved;
		}

		for (auto S : BankStrings)
		{
			if (S.starts_with("event:/"))
			{
				CreateEvent(S);
			}
		}
	}

	void FmodEngine::SetCurrentEventName(const std::string &Name)
	{
		m_CurrentEventInstanceName = Name;

		if (m_Events.contains(m_CurrentEventInstanceName))
		{
			m_CurrentEventInstance = m_Events[m_CurrentEventInstanceName];
			return;
		}

	}

	bool FmodEngine::IsEventValid(const std::string& EventName)
	{
		return m_Events[EventName]->isValid();
	}

	void FmodEngine::SetParameterByName(const std::string &Name, float Value)
	{
		GetCurrentEvent()->setParameterByName(Name.c_str(),Value);
	}

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

	void FmodEngine::LoadBankFromMemory(const char* Data)
	{
		AGE_CORE_ASSERT(false, "Not Implemented!");
	}

	void FmodEngine::CreateEvent(const std::string &EventString)
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
	FmodEngine* AudioEngine::As()
	{
		return (FmodEngine*)this;
	}
}