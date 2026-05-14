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
		~FmodEngine() override;

		virtual void Init() override;
		virtual void Start() override;
		virtual void Update() override;
		virtual void Stop() override;
		virtual void Shutdown() override;
		virtual void LoadBanks(const std::vector<Ref<SoundBank>>& Banks) override;
		virtual void LoadBank(Ref<SoundBank> Bank) override;
		virtual void LoadEvents() override;
		/**
 * @brief Returns the name of the current event instance.
 *
 * This function returns a reference to the string that holds the name of the current event instance. The returned value is not const, meaning it can be modified by the caller. 
 *
 * @return A reference to the string holding the name of the current event instance.
 */
/**
 * @brief This function returns the name of the current event instance.
 * @return A reference to a string containing the name of the current event instance.
 */
virtual std::string& GetCurrentEventName() override {return m_CurrentEventInstanceName;}
		virtual void SetCurrentEventName(const std::string& Name) override;
		virtual bool IsEventValid(const std::string& EventName) override;

		virtual void SetParameterByName(const std::string& Name, float Value) override;
		virtual void Set3DAttributes(void* Attributes) override;

		/**
 * @brief This function returns the current event instance.
 *
 * @return Pointer to FMOD::Studio::EventInstance representing the currently playing event.
 */
/**
 * @brief This function returns the current event instance.
 * @return Pointer to FMOD::Studio::EventInstance object representing the currently playing event.
 */
FMOD::Studio::EventInstance* GetCurrentEvent() {return m_CurrentEventInstance;}

		void LoadBankFromFile(const std::string& FileName);
		void LoadBankFromMemory(const char* Data);

		/**
 * @brief This function returns the FMOD Studio system instance.
 * @return Pointer to the FMOD Studio System object, or nullptr if it fails to initialize.
 */
/**
 * @brief This function returns the FMOD Studio system instance.
 * @return Pointer to the FMOD Studio System object.
 */
FMOD::Studio::System* GetSystem() { return m_System; }
		/**
 * @brief Returns a reference to the map of loaded banks.
 * @return A reference to the map of loaded banks.
 */
/**
 * @brief Returns a reference to the map of banks loaded in the system.
 * @return A reference to the map of banks.
 */
std::map<std::string, FMOD::Studio::Bank*>& GetBanks() { return m_Banks; }
		/**
 * @brief Retrieves the map of event instances associated with this object.
 * @return A reference to a std::map containing string keys and FMOD::Studio::EventInstance pointers.
 */
/**
 * @brief Gets the map of event instances.
 *
 * This function returns a reference to the internal map that holds all the event instances in this class. The map is keyed by string names, and values are pointers to FMOD::Studio::EventInstance objects. 
 *
 * @return A reference to the internal map of event instances.
 */
std::map<std::string, FMOD::Studio::EventInstance*>& GetEvents() { return m_Events; }
		/**
 * @brief This function returns a reference to the map of sounds.
 * @return A reference to the map of sounds.
 */
/**
 * @brief Returns a reference to the map of sounds.
 *
 * This function returns a reference to the internal map that holds all the sound objects in the game. The map is keyed by string names, and values are pointers to FMOD::Sound instances. 
 *
 * @return A reference to the map of sounds.
 */
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