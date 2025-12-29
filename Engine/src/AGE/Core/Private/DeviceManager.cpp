#include "AGEpch.hpp"
#include "DeviceManager.h"
#include "Render/Public/Renderer.h"

namespace AGE
{
	DeviceManager::DeviceManager(AudioEngineType AudioEngine, bool UseXInput)
	{
		m_Window = Scope<Window>(Window::Create());
		m_AudioManager = CreateScope<AudioManager>(AudioEngine);
		if (UseXInput)
		{
			m_XInput = CreateScope<XInput>();
		}
		m_XInput = nullptr;

		CoreLogger::Info("Device Manager Initialized!");
	}

	Scope<DeviceManager> DeviceManager::Create(AudioEngineType AudioEngine, bool UseXInput)
	{
		return Scope<DeviceManager>(new DeviceManager(AudioEngine));
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

