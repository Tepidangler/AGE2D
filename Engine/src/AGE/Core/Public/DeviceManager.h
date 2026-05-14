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

		/**
 * @brief Returns the Audio Engine instance.
 *
 * This function returns a reference to an AudioEngine object which is currently being used by the application.
 * The returned object can be used for various audio processing tasks.
 *
 * @return Reference to the current AudioEngine instance.
 */
Ref<AudioEngine> GetAudioEngine() { return m_AudioEngine; }
		/**
 * @brief This function returns the type of audio engine being used by the application.
 * @return The type of AudioEngine as an enumeration value (e.g., kAudioEngineType1, kAudioEngineType2).
 */
AudioEngineType GetAudioEngineType() { return m_Type; }

		void SwitchAudioEngine(AudioEngineType Type);

	private:

		Ref<AudioEngine> m_AudioEngine;

		AudioEngineType m_Type;
	};

	class DeviceManager
	{
	public:

		DeviceManager(AudioEngineType AudioEngine, bool UseXInput = false);
		/**
 * @brief Virtual destructor for the DeviceManager class.
 *
 * This function is responsible for releasing any resources that were acquired by the DeviceManager instance, such as memory or file handles. It does not return anything and has no parameters.
 */
virtual ~DeviceManager() = default;

		/**
 * @brief Returns a reference to the main application window.
 *
 * This function returns a reference to the main application window, which is used throughout the program for various operations such as rendering and user input handling.
 *
 * @return A reference to the main application window (AGEWindow&).
 */
inline AGEWindow& GetWindow() { return *m_Window; }
		/**
 * @brief Returns a reference to the global instance of the AudioManager class.
 *
 * This function returns a reference to the globally accessible instance of the
 * AudioManager class, which is used for managing audio in the application. The
 * returned object can be used to interact with the audio system.
 *
 * @return Reference to the global AudioManager instance.
 */
inline AudioManager& GetAudioManager() { return *m_AudioManager; }
#ifdef AG_PLATFORM_WINDOWS
		/**
 * @brief This function returns a reference to the XInput object.
 * @return A reference to the XInput object.
 */
inline XInput& GetXInput() { return *m_XInput; }
#endif
		/**
 * @brief This function updates the window by calling OnUpdate method of m_Window object.
 * 
 * The function does not take any parameters and returns nothing. It directly calls the OnUpdate() method on the m_Window object, which presumably handles updating the window's content or properties based on some internal state.
 */
inline void UpdateWindow() { m_Window->OnUpdate(); }
#ifdef AG_PLATFORM_WINDOWS
		/**
 * @brief This function polls the controllers connected to the system.
 *
 * The function calls the `PollControllers` method of the `m_XInput` object, which is presumably a class that manages input devices and provides methods for their polling. 
 * It does not take any parameters and returns void. This means it doesn't return anything to the caller.
 */
inline void PollInput() { m_XInput->PollControllers(); }
#endif

	private:

	private:
		Scope<AGEWindow> m_Window;
		Scope<AudioManager> m_AudioManager;
#ifdef AG_PLATFORM_WINDOWS
		Scope<XInput> m_XInput;
#endif
		friend class App;
	};



}