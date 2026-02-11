#pragma once
#if WITH_FMOD
#include "Core/Public/Core.h"
#include "Audio/AudioEngine/Public/AudioEngine.h"
#include "fmod_studio.hpp"
#include "fmod.hpp"
#include <map>


namespace AGE
{
	class FmodEngine : public AudioEngine
	{
	public:
		FmodEngine();
		virtual ~FmodEngine();

		virtual void Init() override;
		virtual void Start() override;
		virtual void Update() override;
		virtual void Stop() override;
		virtual void Shutdown() override;
		virtual void LoadBanks(const std::vector<Ref<SoundBank>>& Banks) override;
		virtual void LoadBank(Ref<SoundBank> Bank) override;
		virtual void LoadEvents() override;
		virtual std::string& GetCurrentEventName() override {return m_CurrentEventInstanceName;}
		virtual void SetCurrentEventName(const std::string& Name) override;
		virtual bool IsEventValid(const std::string& EventName) override;

		virtual void SetParameterByName(const std::string& Name, float Value) override;
		virtual void Set3DAttributes(void* Attributes) override;

		FMOD::Studio::EventInstance* GetCurrentEvent() {return m_CurrentEventInstance;}

		void LoadBankFromFile(const std::string& FileName);
		void LoadBankFromMemory(const char* Data);

		FMOD::Studio::System* GetSystem() { return m_System; }
		std::map<std::string, FMOD::Studio::Bank*>& GetBanks() { return m_Banks; }
		std::map<std::string, FMOD::Studio::EventInstance*>& GetEvents() { return m_Events; }
		std::map<std::string, FMOD::Sound*>& GetSounds() { return m_Sounds; }

	private:
		void CreateFmodEvent(const std::string& EventString);

	private:
		FMOD::Studio::System* m_System = nullptr;

		std::map<std::string, FMOD::Studio::Bank*> m_Banks;
		std::map<std::string, FMOD::Studio::EventInstance*> m_Events;
		std::map<int, FMOD::Channel*> m_Channels;
		std::map<std::string, FMOD::Sound*> m_Sounds;

		std::string m_CurrentEventInstanceName;
		FMOD::Studio::EventInstance* m_CurrentEventInstance;

	};
}
#endif //WITH_FMOD