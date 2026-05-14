#include "AGEpch.hpp"
#include "DeviceManager.h"
#include "Render/Public/Renderer.h"

namespace AGE
{
	/**
 * @brief Constructs a DeviceManager object.
 * 
 * This constructor initializes the device manager with an audio engine type and a boolean flag indicating whether to use XInput or not.
 * It creates an AGEWindow, AudioManager, and optionally an XInput instance based on the input parameters. The initialization is logged using CoreLogger::Info().
 * 
 * @param AudioEngine The type of audio engine to be used by the device manager.
 * @param UseXInput A boolean flag indicating whether or not to use XInput.
 */
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

	/**
 * @brief Constructs an instance of the AudioManager class.
 * 
 * This constructor initializes an instance of the AudioManager class with a specified audio engine type. It creates an instance of the appropriate audio engine based on the provided type and sets it as the current audio engine for the manager. The log message "Audio Manager Initialized!" is also printed to indicate successful initialization.
 * 
 * @param Type - The type of audio engine that should be used by this AudioManager instance. This can be one of the values defined in the AudioEngineType enum, such as kOpenAL or kFMOD.
 */
AudioManager::AudioManager(AudioEngineType Type)
		:m_Type(Type)
	{
		m_AudioEngine = Ref<AudioEngine>(AudioEngine::Create(Type));
		CoreLogger::Info("Audio Manager Initialized!");
	}

	/**
 * @brief Switches the audio engine being used by the AudioManager.
 *
 * This function resets the current audio engine and replaces it with a new one of the specified type. The new audio engine is initialized immediately after its creation.
 *
 * @param Type The type of the new audio engine to be created.
 */
void AudioManager::SwitchAudioEngine(AudioEngineType Type)
	{
		m_AudioEngine.reset();
		m_AudioEngine = Ref<AudioEngine>(AudioEngine::Create(Type));
		m_Type = Type;
	}
}

