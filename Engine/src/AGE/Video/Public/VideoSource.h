#pragma once
#if 0
#include "Core/Public/Core.h"
#include "Texture/Public/Texture.h"

#include <string>



namespace AGE
{

	class VideoSource
	{
	public:
		 VideoSource(const std::string& FilePath);

		/**
 * @brief This function returns the file name from the member variable m_FilePath.
 * @return std::string The filename as a string. If no file path is set, it will return an empty string.
 */
std::string GetFileName() { return m_FilePath; }

		/**
 * @brief Returns the number of frames in a video sequence.
 *
 * This function retrieves and returns the current count of frames in a video sequence.
 * The value is stored as a member variable 'm_NumberOfFrames' which should be updated elsewhere in the codebase.
 *
 * @return uint32_t - Current number of frames in the video sequence.
 */
uint32_t GetNumberOfFrames() { return m_NumberOfFrames; }
		/**
 * @brief Returns the number of frames played by the player.
 *
 * This function returns an integer representing the total number of frames that have been played by the player.
 * It does not take any parameters and does not modify any state.
 *
 * @return The number of frames played as an integer. If no frames have been played, it will return 0.
 */
int GetNumberOfFramesPlayed() { return m_FrameCount; }
		/**
 * @brief Returns the current frames per second value.
 *
 * This function returns the current Frames Per Second (FPS) value that is being used by the application for rendering and updating purposes.
 *
 * @return double - The current FPS value.
 */
double GetFramesPerSecond() { return m_FramesPerSecond; }
		/**
 * @brief Returns the width of an object.
 *
 * This function returns the current width value stored in 'm_Width'. It is used to get the width of any object that has a width property.
 *
 * @return uint32_t The width of the object.
 */
uint32_t GetWidth() { return m_Width; }
		/**
 * @brief Returns the height of an object.
 *
 * This function retrieves and returns the current height value stored in the 'm_Height' member variable.
 * The returned value is a uint32_t, representing the height of the object.
 *
 * @return The current height of the object as a uint32_t.
 */
uint32_t GetHeight() { return m_Height; }
		/**
 * @brief Returns the number of channels in the system.
 *
 * This function retrieves and returns the current number of channels in the communication system.
 * It does not take any parameters and does not modify anything.
 *
 * @return int The number of channels currently active in the system. If no channels are present, it will return 0.
 */
int GetChannels() { return m_Channels; }
		/**
 * @brief Gets the texture object reference.
 *
 * This function returns a reference to the Texture2D object stored in member variable 'm_Texture'. It is used to access and possibly modify this data if necessary.
 *
 * @return A reference to the Texture2D object.
 */
Ref<Texture2D>& GetTexture() { return m_Texture; }



		void SeekFrame();
		void ReadFrame();
		void MakeTexture();
		void IncrementFrameCount();


		/**
 * @brief This function sets the texture data.
 *
 * @param Data Pointer to an array of uint8_t values representing the new texture data.
 * The size of this data should be equal to the product of m_Width, m_Height and m_Channels.
 */
void SetTextureData(uint8_t* Data)
		{
			m_Texture->SetData(Data, (m_Width * m_Height * m_Channels));
		}

		/**
 * @brief Checks whether the texture is loaded or not.
 *
 * This function checks if both 'bLoaded' and 'm_Texture' are true, indicating that a texture has been loaded successfully.
 *
 * @return True if the texture is loaded, false otherwise.
 */
bool IsLoaded() { return bLoaded && m_Texture; }
		~VideoSource();

	private:

		COMMENT:
/**
 * @brief Default constructor for VideoSource class.
 *
 * This function initializes a new instance of the VideoSource class with default values.
 * It does not take any parameters and returns nothing.
 */
CONFIDENCE: 1.0;

VideoSource() = default;
		/**
 * @brief Default copy constructor for the VideoSource class.
 *
 * This function is used to create a new instance of the VideoSource class by copying an existing one. It uses the '= default' syntax, which tells the compiler to generate a default implementation for this member function.
 *
 * @param other The VideoSource object to be copied.
 * 
 * @return A new VideoSource object that is a copy of the input parameter.
 */
VideoSource(const VideoSource&) = default;

	private:
		std::string m_FilePath;

		bool bLoaded = false;

		uint32_t m_NumberOfFrames = 0;

		int m_FrameCount = 0;
		
		Ref<Texture2D> m_Texture;

		double m_FramesPerSecond = 0.f;

		uint32_t m_Width, m_Height;

		int m_Channels;
	};
}
#endif