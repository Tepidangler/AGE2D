#pragma once
#include "Core/Public/Core.h"
#include "Audio/AudioEngine/Public/Soundbank.h"
#include <memory>

namespace AGE
{
	enum AudioEngineType : uint16_t
	{
		AGESoundEngine = 0,
		WWiseEngine,
		FModEngine
	};

	class AudioEngine
	{
	public:

		template<typename T>
		T* As();
		static Ref<AudioEngine> Create(AudioEngineType Type);

		virtual void Init() = 0;
		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void Stop() = 0;
		virtual void Shutdown() = 0;

		virtual void LoadBanks(const std::vector<Ref<SoundBank>>& Banks) = 0;
		virtual void LoadBank(Ref<SoundBank> Bank) = 0;

		virtual std::string& GetCurrentEventName() = 0;
		virtual void SetCurrentEventName(const std::string& Name) = 0;

		virtual bool IsEventValid(const std::string& EventName) = 0;

		virtual void SetParameterByName(const std::string& Name, float Value) = 0;
		virtual void Set3DAttributes(void* Attributes) =0;


		virtual void LoadEvents() = 0;


	private:

	};
}