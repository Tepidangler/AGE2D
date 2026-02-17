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

		inline AGEWindow& GetWindow() { return *m_Window; }
		inline AudioManager& GetAudioManager() { return *m_AudioManager; }
#ifdef AG_PLATFORM_WINDOWS
		inline XInput& GetXInput() { return *m_XInput; }
#endif
		inline void UpdateWindow() { m_Window->OnUpdate(); }
#ifdef AG_PLATFORM_WINDOWS
		inline void PollInput() { m_XInput->PollControllers(); }
#endif
		static Scope<DeviceManager> Create(AudioEngineType AudioEngine = AudioEngineType::AGESoundEngine, bool UseXInput = false);

	private:
		DeviceManager(AudioEngineType AudioEngine, bool UseXInput = false);

	private:
		Scope<AGEWindow> m_Window;
		Scope<AudioManager> m_AudioManager;
#ifdef AG_PLATFORM_WINDOWS
		Scope<XInput> m_XInput;
#endif
		friend class App;
	};



}