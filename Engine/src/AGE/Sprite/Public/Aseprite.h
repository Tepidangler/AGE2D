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
		Aseprite() = default;
		Aseprite(const Aseprite&) = default; // Despite not wanting a bunch of objects floating around we might still need to copy the data from place to place idk yet though.
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
		void ReadTilesetChunk( AsepriteFileData& Data) { CoreLogger::Error("AGE does not support Tilesets made in Aseprite!"); }

		void ReorderLayers(const std::string& Filename);
		Ref<Texture2D> CreateTexture(std::string ImageName);


		std::string GetFileName(const std::filesystem::path& Path);

		AsepritePropertyTypes ConvertToType(uint16_t T);
		void ProcessElement(MemoryStreamReader* Stream, AsepritePropertyTypes T, AsepriteUserProps& Data);

	private:

		std::ifstream m_Stream;
		std::unordered_map <std::string, AsepriteFileData> m_AsepriteData;
		std::unordered_map<std::string, Ref<Image>> m_ImagePairs;

		friend class Renderer2D;
		friend struct SpriteRendererComponent;

	};
}