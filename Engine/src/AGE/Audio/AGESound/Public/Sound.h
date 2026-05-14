#pragma once
#include "Core/Public/Core.h"
#include "Math/Public/MathStructures.h"
#include "Core/Public/UUID.h"
#include <string>

namespace AGE
{
	class AudioSource
	{
	public:
		AudioSource(const std::string& FilePath);
		//~AudioSource();

		/**
 * @brief This function returns the file path of the object.
 * @return A string containing the file path.
 */
/**
 * @brief This function returns the file path of a class instance.
 * @return A string containing the file path. If no file path is set, it will return an empty string.
 */
std::string GetFilePath() const { return m_FilePath; }
		/**
 * @brief Returns the name of the object.
 * @return A string containing the name of the object. If no name is set, returns an empty string.
 */
/**
 * @brief Returns the name of the object.
 * @return A string containing the name of the object. If no name is set, an empty string will be returned.
 */
std::string GetName() const { return m_Name; }
		/**
 * @brief Gets the Asset ID of the object.
 *
 * This function returns a reference to the UUID member variable 'm_AssetID'. It is used to access and manipulate the unique identifier for an asset in the system. 
 *
 * @return A reference to the UUID representing the Asset ID.
 */
/**
 * @brief Gets the Asset ID of the object.
 *
 * This function returns a reference to the private member variable 'm_AssetID'. It provides access to this data, but does not allow modification.
 *
 * @return A reference to UUID& representing the Asset ID.
 */
UUID& GetAssetID() { return m_AssetID; }

		/**
 * @brief Sets the Asset ID of an object.
 * @param ID The unique identifier for the asset.
 * @return void
 */
/**
 * @brief Sets the Asset ID of an object.
 * @param ID The unique identifier for the asset.
 */
void SetAssetID(const UUID& ID) { m_AssetID = ID; }
		void SetPosition(const Vector3& P);
		void SetPosition(float x, float y, float z);
		void SetGain(float Gain);
		void SetPitch(float Pitch);
		void SetSpatial(bool Spatial);
		void SetLoop(bool Loop);
		/**
 * @brief Sets the playing state of the object.
 * @param Playing The new playing state to set.
 */
/**
 * @brief Sets the playing state of the object.
 * @param Playing The new playing state to set.
 */
void SetPlaying(bool Playing) { bIsPlaying = Playing; }
		/**
 * @brief This function sets the sound data to a given vector of characters.
 * @param Data The new sound data as a std::vector of characters.
 */
/**
 * @brief This function sets the sound data to a given vector of characters.
 * @param Data The new sound data as a std::vector of characters.
 */
void SetSoundData(std::vector<char> Data) { m_SoundData = Data; }

		std::pair<uint32_t, uint32_t> GetLengthMinutesAndSeconds() const;


		static AudioSource LoadFromFile(const std::string& File, bool Spatial = false);

		/**
 * @brief Checks whether the looping condition is set or not.
 *
 * This function returns a boolean value indicating whether the 'bLoop' variable, which represents the looping condition in the code, has been set to true or false. 
 *
 * @return True if the looping condition is set (i.e., bLoop == true), False otherwise.
 */
/**
 * @brief Checks whether the looping condition is set.
 *
 * This function returns a boolean value indicating whether the 'bLoop' variable, which represents the looping condition in the code, has been set or not.
 *
 * @return True if the looping condition is set (i.e., bLoop is true), false otherwise.
 */
bool IsLooping() { return bLoop; }
		/**
 * @brief Checks whether the object is loaded or not.
 *
 * This function returns a boolean value indicating whether the object is loaded or not. It does this by returning the 'bLoaded' member variable of the class instance.
 * 
 * @return True if the object is loaded, false otherwise.
 */
/**
 * @brief Checks whether the object is loaded.
 *
 * This function returns a boolean value indicating whether the object has been loaded or not.
 *
 * @return True if the object is loaded, false otherwise.
 */
bool IsLoaded() const { return bLoaded; }
		/**
 * @brief Checks whether the game is currently playing or not.
 *
 * This function returns a boolean value indicating if the game is in play mode.
 * It does this by examining the 'bIsPlaying' member variable of the class instance.
 * 
 * @return True if the game is currently being played, false otherwise.
 */
/**
 * @brief This function checks whether the game is currently playing.
 * @return Returns true if the game is currently playing, false otherwise.
 */
bool IsPlaying() const { return bIsPlaying; }

	private:
		/**
 * @brief Default constructor for the AudioSource class.
 *
 * This function initializes an instance of the AudioSource class with its default settings. It does not take any parameters and returns nothing. The function is marked as default, meaning it can be used to create instances of the class without arguments.
 *
 * @return void
 */
/**
 * @brief Default constructor for the AudioSource class.
 *
 * This function initializes an instance of the AudioSource class with default values. It does not take any parameters and returns no value. The purpose of this constructor is to provide a clean slate when creating new instances of the AudioSource class, without needing to specify any specific configuration details.
 */
AudioSource() = default;
		/**
 * @brief Copy constructor for the AudioSource class.
 *
 * This function creates a new instance of an AudioSource object by copying all its attributes from another existing AudioSource object.
 * The copy is made using the 'default' keyword, which means that it uses the compiler-generated default copy constructor.
 * 
 * @param other An existing AudioSource object to be copied.
 */
/**
 * @brief Copy constructor for the AudioSource class.
 *
 * This function creates a new instance of an AudioSource object by copying all its properties from another existing AudioSource object.
 * The copy is done using the 'default' keyword, which means that it uses the compiler-generated default implementation.
 * 
 * @param other An existing AudioSource object to be copied.
 */
AudioSource(const AudioSource&) = default;
		AudioSource(uint32_t Handle, bool Loaded, double Length);
		AudioSource(uint32_t Handle, bool Loaded, double Length, std::vector<char> Data);


	private:

		uint32_t m_BufferHandle = 0;
		uint32_t m_SourceHandle = 0;
		UUID m_AssetID;

		bool bLoaded = false;
		bool bSpatial = false;
		bool bIsPlaying = false;
		double m_TotalDuration = 0.0; //Seconds

		Vector3 m_Position;
		float m_Gain = 1.f;
		float m_Pitch = 1.f;
		bool bLoop = false;

		std::vector<char> m_SoundData;
		std::string m_FilePath;

		std::string m_Name;

		friend class AGESound;
	};


}