#pragma once
#include "Core/Public/Core.h"
#include "Statics/Public/Statics.h"
#include "Structs/Public/DataStructures.h"
#include "Serializers/Public/DataReader.h"
#include "Serializers/Public/DataWriter.h"
#include "Sprite/Public/Image.h"
#include <vector>
#include <filesystem>


namespace AGE
{
	class Texture2D;

	//This class will operate more like a manager than an individual object that represents a file
	//I just simply can't see the value in having a bunch of Aseprite Objects being made if all we care about is reading and writing data
	class Aseprite
	{
	public:
		/**
 * @brief Default constructor for Aseprite class.
 *
 * This function initializes an instance of the Aseprite class with its default values.
 * It does not take any parameters and returns nothing.
 */
Aseprite() = default;
		/**
 * @brief Copy constructor for class Aseprite is deleted to prevent copying of objects.
 *
 * The copy constructor is implicitly provided by the compiler, but it's not needed in this context as we don't want to allow copies of our Aseprite objects. 
 * This function simply throws a compilation error if someone tries to use it.
 *
 * @param other The object being copied. Not used because copying is disabled.
 */
Aseprite(const Aseprite&) = delete; // Despite not wanting a bunch of objects floating around we might still need to copy the data from place to place idk yet though.
		/**
 * @brief This function is a move constructor for the class Aseprite and it's marked as deleted to prevent copying of objects.
 * 
 * @param other The object to be moved from.
 */
Aseprite(const Aseprite&&) = delete;

		void ReadData(const std::filesystem::path& Filepath);

		Ref<Texture2D> CreateImage(const std::string& Filename, bool ShouldCreateTexture, bool ShouldFlipOnLoad = false);

	protected:
		std::vector<AsepriteFrameData>& GetSpriteFrameData(const std::string& SpriteName);


	private:
		void ReadFrameData(const std::string& Filename, FileStreamReader* Stream, size_t Size);
		void ReadOldPaletteChunk( AsepriteFileData& Data);
		void ReadLayerChunk( AsepriteFileData& Data);
		AsepriteCelChunk ReadCelChunk( AsepriteFileData& Data);
		void ReadColorProfileChunk( AsepriteFileData& Data);
		void ReadExternalFilesChunk( AsepriteFileData& Data);
		//While this is currently deprecated in the newest versions of Aseprite I have no clue what version people are using so this might be important
		void ReadMaskChunk( AsepriteFileData& Data);
		void ReadTagsChunk( AsepriteFileData& Data);
		void ReadNewPaletteChunk( AsepriteFileData& Data);
		void ReadUserDataChunk( AsepriteFileData& Data);
		void ReadSliceChunk( AsepriteFileData& Data);
		/**
 * @brief This function reads a tileset chunk from an Aseprite file.
 *
 * The function is currently implemented to throw an error message indicating that AGE (Age of Empires) does not support Tilesets made in Aseprite. 
 * It's important to note that this function should ideally be able to read and parse the tileset chunk from a valid Aseprite file, but as of now it only throws an error message.
 *
 * @param Data The AsepriteFileData object containing the data of the Aseprite file. This parameter is not used in this function because the function does not perform any operations on it.
 * 
 * @return Nothing is returned as the function directly outputs an error message to the console.
 */
void ReadTilesetChunk( AsepriteFileData& Data) { CoreLogger::Error("AGE does not support Tilesets made in Aseprite!"); }

		void ReorderLayers(const std::string& Filename);
		Ref<Texture2D> CreateTexture(std::string ImageName);


		std::string GetFileName(const std::filesystem::path& Path);

		AsepritePropertyTypes ConvertToType(uint16_t T);
		void ProcessElement(MemoryStreamReader* Stream, AsepritePropertyTypes T, AsepriteUserProps& Data);

		/**
 * @brief Copy assignment operator for class Aseprite.
 * 
 * This function is used to assign the value of one instance of Aseprite to another. It takes as a parameter an object of type Aseprite (Other).
 * The function does not return anything, so it has void return type.
 * 
 * @param Other An instance of Aseprite that will be copied into the current instance.
 */
void operator=(const Aseprite& Other)
		{

		}

	private:

		std::ifstream m_Stream;
		std::unordered_map <std::string, AsepriteFileData> m_AsepriteData;
		std::unordered_map<std::string, Ref<Image>> m_ImagePairs;

		friend class Renderer2D;
		friend struct SpriteRendererComponent;

	};
}