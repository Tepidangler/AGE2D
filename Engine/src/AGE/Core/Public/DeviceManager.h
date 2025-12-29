#pragma once
#include "Core/Public/Core.h"
#include "Core/Public/Window.h"
#include "Audio/AudioEngine/Public/AudioEngine.h"
#include "Platform/Microsoft/XInput/Public/XInput.h"

namespace AGE
{
	class AudioManager
	{
	public:

		AudioManager(AudioEngineType Type);

		Ref<AudioEngine> GetAudioEngine() { return m_AudioEngine; }
		AudioEngineType GetAudioEngineType() { return m_Type; }

		void SwitchAudioEngine(AudioEngineType Type);

	private:

		Ref<AudioEngine> m_AudioEngine;

		AudioEngineType m_Type;
	};

	class DeviceManager
	{
	public:

		virtual ~DeviceManager() = default;

		inline Window& GetWindow() { return *m_Window; }
		inline AudioManager& GetAudioManager() { return *m_AudioManager; }
		inline XInput& GetXInput() { return *m_XInput; }

		inline void UpdateWindow() { m_Window->OnUpdate(); }

		inline void PollInput() { m_XInput->PollControllers(); }

		static Scope<DeviceManager> Create(AudioEngineType AudioEngine = AudioEngineType::AGESoundEngine, bool UseXInput = false);

	private:
		DeviceManager(AudioEngineType AudioEngine, bool UseXInput = false);

	private:
		Scope<Window> m_Window;
		Scope<AudioManager> m_AudioManager;
		Scope<XInput> m_XInput;

		friend class App;
	};



}