#include "AGEpch.hpp"
#include "DeviceManager.h"
#include "Render/Public/Renderer.h"

namespace AGE
{
	DeviceManager::DeviceManager(AudioEngineType AudioEngine, bool UseXInput)
	{
		m_Window = Scope<AGEWindow>(AGEWindow::Create());
		m_AudioManager = CreateScope<AudioManager>(AudioEngine);
#ifdef AG_PLATFORM_WINDOWS
		if (UseXInput)
		{
			m_XInput = CreateScope<XInput>();
		}
		m_XInput = nullptr;
#endif
		CoreLogger::Info("Device Manager Initialized!");
	}
	//AUDIO MANAGER

	AudioManager::AudioManager(AudioEngineType Type)
		:m_Type(Type)
	{
		m_AudioEngine = Ref<AudioEngine>(AudioEngine::Create(Type));
		CoreLogger::Info("Audio Manager Initialized!");
	}

	void AudioManager::SwitchAudioEngine(AudioEngineType Type)
	{
		m_AudioEngine.reset();
		m_AudioEngine = Ref<AudioEngine>(AudioEngine::Create(Type));
		m_Type = Type;
	}
}

