#include "AGEpch.hpp"
#include "Sprite/Public/Aseprite.h"
#include "Statics/Public/Statics.h"
#include "Texture/Public/Texture.h"
#ifdef AG_PLATFORM_WINDOWS
#include <intrin.h>
#else
#include <x86intrin.h>
#endif

namespace AGE
{

	//Aseprite uses little endian byte order
	

void Aseprite::ReadData(const std::filesystem::path& Filepath)
	{
		std::string Name = GetFileName(Filepath);
		AsepriteHeader Header;
		AsepriteFileData FileData;

		FileStreamReader Stream(Filepath);
		uint32_t NotNeeded;
		uint8_t IgnoreThese;
		uint8_t ForFutureUse;
		if (Stream)
		{
			Stream.ReadRaw<uint32_t>(Header.FileSize);
			Stream.ReadRaw<uint16_t>(Header.MagicNumber);
			Stream.ReadRaw<uint16_t>(Header.Frames);
			Stream.ReadRaw<uint16_t>(Header.Width);
			Stream.ReadRaw<uint16_t>(Header.Height);
			Stream.ReadRaw<uint16_t>(Header.Depth);
			Stream.ReadRaw<uint32_t>(Header.Flags);
			Stream.ReadRaw<uint16_t>(Header.Speed);
			Stream.ReadRaw<uint32_t>(NotNeeded);
			Stream.ReadRaw<uint32_t>(NotNeeded);
			Stream.ReadRaw<uint8_t>(Header.EntryIndex);
			Stream.ReadRaw<uint8_t>(IgnoreThese);
			Stream.ReadRaw<uint8_t>(IgnoreThese);
			Stream.ReadRaw<uint8_t>(IgnoreThese);
			Stream.ReadRaw<uint16_t>(Header.NumOfColors);
			Stream.ReadRaw<uint8_t>(Header.PixelWidth);
			Stream.ReadRaw<uint8_t>(Header.PixelHeight);
			Stream.ReadRaw<int16_t>(Header.x);
			Stream.ReadRaw<int16_t>(Header.y);
			Stream.ReadRaw<uint16_t>(Header.GridWidth);
			Stream.ReadRaw<uint16_t>(Header.GridHeight);
			for (int i = 0; i < 84; i++)
			{
				Stream.ReadRaw<uint8_t>(ForFutureUse);
			}
			FileData.Header = Header;
			FileData.Frames.resize(Header.Frames);
			m_AsepriteData[Name] = FileData;
			m_AsepriteData[Name].Frames.resize(Header.Frames);
			ReadFrameData(Name, &Stream, Header.Frames);



		}
	}

	"/**\n \
* @brief Creates an image from the given Aseprite file.\n \
* This function reads data from a specified Aseprite file, processes it and creates an image object. The created image can optionally be converted into a texture.\n \
* @param Filename The name of the Aseprite file to read from.\n \
* @param ShouldCreateTexture If true, a texture will be created from the image data. Otherwise, only the image object is returned.\n \
* @param ShouldFlipOnLoad If true, the loaded image will be flipped vertically.\n \
* @return A reference to the created image or texture (if any). Returns nullptr if no image was created and the function should not create a texture.\n \
*/"
"Creates an image from a given Aseprite file and optionally creates a texture."
Ref<Texture2D> Aseprite::CreateImage(const std::string& Filename, bool ShouldCreateTexture, bool ShouldFlipOnLoad)
	{
		std::vector<uint8_t> ImgData;

		uint32_t Width = m_AsepriteData[Filename].Header.Width;
		uint32_t Height = m_AsepriteData[Filename].Header.Height;
		int Channels = m_AsepriteData[Filename].Header.Depth == 32 ? 4:3;
		uint8_t RGBType = m_AsepriteData[Filename].Header.Depth == 32 ? 2:1;


		ReadLayerChunk(m_AsepriteData[Filename]);
		ReadCelChunk(m_AsepriteData[Filename]);
		ReorderLayers(Filename);

		for ([[maybe_unused]] auto& F : m_AsepriteData[Filename].Frames)
		{ 
			ReadOldPaletteChunk(m_AsepriteData[Filename]);
			ReadNewPaletteChunk(m_AsepriteData[Filename]);
		}
		
		ImageSpecification Spec(Width, Height, Channels, RGBType, m_AsepriteData[Filename]);
		Ref<Image> Img = CreateRef<Image>(Spec, ShouldFlipOnLoad);

		m_ImagePairs[Filename] = Img;

		if (ShouldCreateTexture)
		{
			return CreateTexture(Filename);
		}

		return nullptr;
	}

	/**
 * @brief Creates a Texture2D from an image specified by the ImageName.
 * 
 * This function takes in a string, which is used as a key to access an image pair stored in m_ImagePairs map. The image data associated with this key is then used to create and return a new Texture2D object.
 *
 * @param ImageName A string representing the name of the image for which a texture is being created.
 * 
 * @return Ref<Texture2D> Returns a reference to the newly created Texture2D object.
 */
/**
 * @brief Creates a Texture2D from an image specified by its name.
 * 
 * This function takes in the name of an image, retrieves the corresponding ImagePair object from m_ImagePairs map, and then creates a new Texture2D using this ImagePair's data. The width, height, number of channels, and byte size are extracted from the ImageSpec of the ImagePair.
 * 
 * @param ImageName The name of the image to create a texture for.
 * @return A reference to the newly created Texture2D object.
 */
Ref<Texture2D> Aseprite::CreateTexture(std::string ImageName)
	{
		auto& Img = m_ImagePairs[ImageName];
		return Texture2D::Create(Img.get(), Img->GetImageSpec().GetWidth(), Img->GetImageSpec().GetHeight(), Img->GetImageSpec().GetChannels(), Img->GetImageByteSize());
	}

	/**
 * @brief Get the frame data of a specific sprite.
 * 
 * This function retrieves the frame data for a given sprite name from the Aseprite data map. If the sprite does not exist in the map, an exception is thrown.
 * 
 * @param SpriteName The name of the sprite to retrieve the frame data for.
 * @return Reference to the vector of frames associated with the given sprite name.
 * @throws std::out_of_range If the provided sprite name does not exist in the Aseprite data map.
 */
/**
 * @brief Get the frame data of a specific sprite.
 * 
 * This function retrieves the frame data for a given sprite name from the Aseprite data map. If the sprite does not exist, it will return an empty vector.
 * 
 * @param SpriteName The name of the sprite to retrieve the frame data for.
 * @return std::vector<AsepriteFrameData>& Reference to the frame data vector of the specified sprite. If the sprite does not exist, it will return an empty vector.
 */
std::vector<AsepriteFrameData>& Aseprite::GetSpriteFrameData(const std::string& SpriteName)
	{
		return m_AsepriteData[SpriteName].Frames;
	}

	

void Aseprite::ReadFrameData(const std::string& Filename,  FileStreamReader* Stream, size_t Size)
	{
		AsepriteFrameData Data;
		AsepriteChunk Chunk;
		uint8_t NotNeeded[2];
		//uint16_t Type;

		for (size_t i = 0; i < Size; i++)
		{
			//Read Frame header data
			Stream->ReadRaw<uint32_t>(Data.BytesInFrame);
			Stream->ReadRaw<uint16_t>(Data.MagicNumber);
			Stream->ReadRaw<uint16_t>(Data.NumOfChunks);
			Stream->ReadRaw<uint16_t>(Data.FrameDuration);
			Stream->ReadRaw<uint8_t>(NotNeeded[0]);
			Stream->ReadRaw<uint8_t>(NotNeeded[1]);
			Stream->ReadRaw<uint32_t>(Data.NewNumOfChunks);

			//Read each chunk

			if (Data.NewNumOfChunks == 0)
			{
				Data.ChunkData.resize(Data.NumOfChunks);
				for (uint16_t x = 0; x < Data.NumOfChunks; x++)
				{
					Stream->ReadRaw<uint32_t>(Chunk.Size);
					Stream->ReadRaw<AsepriteChunkType>(Chunk.Type);
					Chunk.Data.resize(Chunk.Size - 6);
					Stream->ReadBytes(Chunk.Data, Chunk.Size - 6);
					Data.ChunkData[x] = Chunk;
				}

			}
			else
			{
				Data.ChunkData.resize(Data.NewNumOfChunks);
				for (uint32_t x = 0; x < Data.NewNumOfChunks; x++)
				{
					Stream->ReadRaw<uint32_t>(Chunk.Size);
					Stream->ReadRaw<AsepriteChunkType>(Chunk.Type);
					Chunk.Data.resize(Chunk.Size - 6);
					Stream->ReadBytes(Chunk.Data, Chunk.Size - 6);
					Data.ChunkData[x] = Chunk;
				}
			}		

			//Add Data to vector
			m_AsepriteData[Filename].Frames[i] = Data;
		}
	}
	

void Aseprite::ReadOldPaletteChunk(AsepriteFileData& Data)
	{
		AsepriteOldPaletteChunk Chunk;
		uint8_t Color[3];

		for (auto& F : Data.Frames)
		{
			for (auto& C : F.ChunkData)
			{
				if (C.Type == AsepriteChunkType::OldPaletteChunk1 || C.Type == AsepriteChunkType::OldPaletteChunk2)
				{
					Chunk.Type = C.Type;

					MemoryStreamReader Stream((void*)C.Data.data(), C.Size);

					Stream.ReadRaw<uint16_t>(Chunk.NumOfPackets);
					Stream.ReadRaw<uint8_t>(Chunk.NumOfPalettesToSkip);
					for (int i = (int)Chunk.NumOfPalettesToSkip; i < Chunk.NumOfPackets; i++)
					{
						Stream.ReadRaw<uint8_t>(Chunk.NumOfColors);
						if ((int)Chunk.NumOfColors == 0)
						{
							Chunk.Colors.resize(256);
						}
						else
						{
							Chunk.Colors.resize((size_t)Chunk.NumOfColors);
						}
						for (int x = 0; x < (int)Chunk.NumOfColors; x++)
						{
							Stream.ReadRaw<uint8_t[3]>(Color);
							Chunk.Colors[(size_t)x] = Color;
						}
					}
					F.OldPaletteChunks.push_back(Chunk);
				}

			}
		}

	}

	/**
 * @brief Reads and stores layer chunk data in a provided AsepriteFileData object.
 * 
 * The function iterates over all frames, then for each frame it checks if any of the chunks are LayerChunk type. If they are, it reads the layer chunk data from the chunk and stores it in an AsepriteLayer object.
 * 
 * @param Data The AsepriteFileData object that contains all frames to be read from. This function modifies this object by adding the layer chunks to its Frames member.
 */
"/**\n" \
" * @brief Reads layer chunk data from an Aseprite file.\n" \
" * This function iterates over all frames in a given AsepriteFileData object, then for each frame,\n" \
" * it checks if any of the chunks are of type LayerChunk. If they are, it reads the layer chunk data\n" \
" * into an AsepriteLayer object and adds this to the Frame's list of layers.\n" \
" * @param Data The AsepriteFileData object that contains all frames and chunks from the Aseprite file.\n" \
" */\n"
void Aseprite::ReadLayerChunk(AsepriteFileData& Data)
	{
		AsepriteLayer LayerChunk;
		uint8_t Useless;
		uint16_t Ignored[2];

		for (auto& F : Data.Frames)
		{
			for (auto& C : F.ChunkData)
			{
				if (C.Type == AsepriteChunkType::LayerChunk)
				{
					MemoryStreamReader Stream((void*)C.Data.data(), C.Size);

					Stream.ReadRaw<uint16_t>(LayerChunk.Flags);
					Stream.ReadRaw<uint16_t>(LayerChunk.Type);
					Stream.ReadRaw<uint16_t>(LayerChunk.Child);
					Stream.ReadRaw<uint16_t>(Ignored[0]);
					Stream.ReadRaw<uint16_t>(Ignored[1]);
					Stream.ReadRaw<uint16_t>(LayerChunk.BlendMode);
					Stream.ReadRaw<uint8_t>(LayerChunk.Opacity);
					for (int i = 0; i < 3; i++)
					{
						Stream.ReadRaw<uint8_t>(Useless);
					}
					Stream.ReadString(LayerChunk.Name);

					if (LayerChunk.Type == 2)
					{
						CoreLogger::Error("Tilesets Currently not Supported!");
					}
					F.Layers.push_back(LayerChunk);
				}

			}
		}
	}

	
"/**\n * @brief Reads a cel chunk from the given Aseprite file data.\n * \n * This function reads and parses cel chunks from an Aseprite file, which are used to define the appearance of individual frames in animations. The parsed information is stored in the `AsepriteCelChunk` struct.\n * \n * @param Data Reference to the AsepriteFileData object containing the data to be read from.\n * \n * @return An instance of `AsepriteCelChunk` filled with parsed cel chunk information.\n */"
AsepriteCelChunk Aseprite::ReadCelChunk(AsepriteFileData& Data)
	{
		AsepriteCelChunk CelChunk;
		uint8_t Useless;
		size_t Index = 0;

		for (auto& F : Data.Frames)
		{
			for (auto& C : F.ChunkData)
			{
				if (C.Type == AsepriteChunkType::CelChunk)
				{
					MemoryStreamReader Stream((char*)C.Data.data(), C.Size);

					Stream.ReadRaw<uint16_t>(CelChunk.LayerIndex);
					Stream.ReadRaw<int16_t>(CelChunk.x);
					Stream.ReadRaw<int16_t>(CelChunk.y);
					Stream.ReadRaw<uint8_t>(CelChunk.Opacity);
					Stream.ReadRaw<uint16_t>(CelChunk.CelType);
					Stream.ReadRaw<int16_t>(CelChunk.zIndex);
					for (int i = 0; i < 5; i++)
					{
						Stream.ReadRaw<uint8_t>(Useless);
					}
					
					switch (CelChunk.CelType)
					{
					case 0:
					{
						CelChunk.PixelDatas.resize(CelChunk.PixelDatas.size() + 1);
						Stream.ReadRaw<uint16_t>(CelChunk.Width);
						Stream.ReadRaw<uint16_t>(CelChunk.Height);
						for (uint32_t i = 0; i < (C.Size - 20);++i)
						{
							uint8_t Pixel;
							Stream.ReadRaw<uint8_t>(Pixel);
							CelChunk.PixelDatas[Index].Pixels.push_back(Pixel);
						}
						F.Layers[CelChunk.LayerIndex].CelChunks.push_back(CelChunk);
						Index++;
						break;
					}
					case 1:
					{
						Stream.ReadRaw<uint16_t>(CelChunk.FramePosition);
						F.Layers[CelChunk.LayerIndex].CelChunks.push_back(CelChunk);
						break;
					}
					case 2:
					{
						CelChunk.PixelDatas.resize(CelChunk.PixelDatas.size() + 1);
						Stream.ReadRaw<uint16_t>(CelChunk.Width);
						Stream.ReadRaw<uint16_t>(CelChunk.Height);
						for (uint32_t i = 0; i < (C.Size - 26); ++i)
						{
							uint8_t Pixel;
							Stream.ReadRaw<uint8_t>(Pixel);
							CelChunk.PixelDatas[Index].Pixels.push_back(Pixel);
						}
						F.Layers[CelChunk.LayerIndex].CelChunks.push_back(CelChunk);
						Index++;
						break;
					}
					default:
					{
						CoreLogger::Warn("Cel Chunk Type not supported!");
						break;
					}
					}
				}
			}
		}


		return CelChunk;
	}

	/**
 * @brief Reads color profile data from an Aseprite file.
 * 
 * This function iterates over all frames and chunks in a given AsepriteFileData, looking for ColorProfileChunk types. When it finds one, it reads its data into an AsepriteColorProfileChunk object. The color profile chunk contains information about the gamma correction used by the sprite sheet.
 * 
 * @param Data An AsepriteFileData containing the frames and chunks to be read.
 */

void Aseprite::ReadColorProfileChunk( AsepriteFileData& Data)
	{
		AsepriteColorProfileChunk Chunk;
		uint8_t Useless;

		for (auto& F: Data.Frames)
		{
			for (auto& C : F.ChunkData)
			{
				if (C.Type == AsepriteChunkType::ColorProfileChunk)
				{
					MemoryStreamReader Stream((void*)C.Data.data(), C.Size);

					Stream.ReadRaw<uint16_t>(Chunk.Type);
					Stream.ReadRaw<uint16_t>(Chunk.Flags);
					Stream.ReadRaw<double>(Chunk.Gamma);

					for (int i = 0; i < 8; i++)
					{
						Stream.ReadRaw<uint8_t>(Useless);
					}

					if (Chunk.Type == 2)
					{
						Stream.ReadRaw<uint32_t>(Chunk.ICCProfileDataLength);
						Stream.ReadBytes(Chunk.ICCProfileData, Chunk.ICCProfileDataLength);
					}
				}

				
			}
		}
	}

	/**
 * @brief Reads the ExternalFilesChunk from a given AsepriteFileData object.
 * 
 * This function reads the ExternalFilesChunk from the provided AsepriteFileData and populates it with data about external files referenced by the sprite. The chunk contains details about these files like their IDs, types and names.
 * 
 * @param Data An instance of AsepriteFileData containing all the data read from an Aseprite file.
 */

void Aseprite::ReadExternalFilesChunk( AsepriteFileData& Data)
	{
		AsepriteExternalFilesChunk Chunk;
		uint8_t Useless;

		for (auto& F : Data.Frames)
		{
			for (auto& C : F.ChunkData)
			{
				if (C.Type == AsepriteChunkType::ExternalFilesChunk)
				{
					MemoryStreamReader Stream((void*)C.Data.data(), C.Size);

					Stream.ReadRaw<uint32_t>(Chunk.NumOfEntries);

					Chunk.Entries.resize(Chunk.NumOfEntries);
					for (uint32_t i = 0; i < Chunk.NumOfEntries; i++)
					{
						Stream.ReadRaw<uint32_t>(Chunk.Entries[i].ID);
						Stream.ReadRaw<uint8_t>(Chunk.Entries[i].Type);
						for (int x = 0; x < 7; x++)
						{
							Stream.ReadRaw<uint8_t>(Useless);
						}

						Stream.ReadString(Chunk.Entries[i].Name);

					}
				}
			}
		}
	}

	/**
 * @brief Reads the mask chunk data from an Aseprite file.
 *
 * This function iterates over all frames and chunks in the given AsepriteFileData object, looking for a specific type of chunk (AsepriteChunkType::MaskChunk). 
 * If it finds such a chunk, it reads its data into an AsepriteMaskChunk object. The mask data is stored as raw bytes in Chunk.Data and can be decoded using the appropriate functions provided by the Aseprite library.
 *
 * @param Data An instance of AsepriteFileData that contains all frames and chunks from an Aseprite file.
 */
/**
 * @brief Reads the mask chunk data from an Aseprite file.
 *
 * This function iterates over all frames and chunks in the given AsepriteFileData object, looking for a specific type of chunk (AsepriteChunkType::MaskChunk). 
 * If it finds such a chunk, it reads its data into an AsepriteMaskChunk object. The function then proceeds to read various properties from the chunk: x and y coordinates, width and height of the mask, and a name for the mask. Finally, it reads the actual pixel data for the mask.
 *
 * @param Data An instance of AsepriteFileData containing all frames and chunks in an Aseprite file.
 */
void Aseprite::ReadMaskChunk( AsepriteFileData& Data)
	{
		AsepriteMaskChunk Chunk;
		uint8_t Useless;

		for (auto& F : Data.Frames)
		{
			for (auto& C : F.ChunkData)
			{
				if (C.Type == AsepriteChunkType::MaskChunk)
				{
					MemoryStreamReader Stream((void*)C.Data.data(), C.Size);

					Stream.ReadRaw<int16_t>(Chunk.x);
					Stream.ReadRaw<int16_t>(Chunk.y);
					Stream.ReadRaw<uint16_t>(Chunk.Width);
					Stream.ReadRaw<uint16_t>(Chunk.Height);

					for (int i = 0; i < 8; i++)
					{
						Stream.ReadRaw<uint8_t>(Useless);
					}


					Stream.ReadString(Chunk.Name);
					Stream.ReadBytes(Chunk.Data, (Chunk.Height * ((Chunk.Width + 7) / 8)));


				}
			}
		}
	}

	"/**\n" \
" * @brief Reads the Tags chunk from an Aseprite file and stores it in a data structure.\n" \
" * \n" \
" * This function iterates over all frames of the given AsepriteFileData object, checks if each Chunk'<｜begin▁of▁sentence｜>\n" \
" * type is AsepriteChunkType::TagsChunk, and if so, reads the Tags chunk from that Chunk's data into an AsepriteTagsChunk structure.\n" \
" * \n" \
" * @param Data The AsepriteFileData object to read from. This contains all frames of the animation.\n" \
" */\n"
void Aseprite::ReadTagsChunk( AsepriteFileData& Data)
	{
		AsepriteTagsChunk Chunk;
		uint8_t Useless;

		for (auto& F : Data.Frames)
		{
			for (auto& C : F.ChunkData)
			{
				if (C.Type == AsepriteChunkType::TagsChunk)
				{
					MemoryStreamReader Stream((void*)C.Data.data(), C.Size);

					Stream.ReadRaw<uint16_t>(Chunk.NumOfTags);
					Chunk.Tags.resize(Chunk.NumOfTags);
					for (int i = 0; i < 8; i++)
					{
						Stream.ReadRaw<uint8_t>(Useless);
					}

					for (size_t i = 0; i < Chunk.NumOfTags; i++)
					{
						Stream.ReadRaw<uint16_t>(Chunk.Tags[i].FromFrame);
						Stream.ReadRaw<uint16_t>(Chunk.Tags[i].ToFrame);
						Stream.ReadRaw<uint8_t>(Chunk.Tags[i].LoopDirection);
						Stream.ReadRaw<uint16_t>(Chunk.Tags[i].RepeatTimes);
						for (int x = 0; x < 6; x++)
						{
							Stream.ReadRaw<uint8_t>(Useless);
						}
						Stream.ReadRaw<uint8_t[3]>(Chunk.Tags[i].RGB);
						Stream.ReadRaw<uint8_t>(Useless);
						Stream.ReadString(Chunk.Tags[i].Name);
					}



				}
			}
		}
	}

	
void Ase
prite::ReadNewPaletteChunk( AsepriteFileData& Data)
	{
		AsepritePaletteChunk Chunk;
		uint8_t Useless;
		for (auto& F : Data.Frames)
		{
			for (auto& C : F.ChunkData)
			{
				if (C.Type == AsepriteChunkType::NewPaletteChunk)
				{
					MemoryStreamReader Stream((void*)C.Data.data(), C.Size);

					Stream.ReadRaw<uint32_t>(Chunk.Size);
					Chunk.Entries.resize(Chunk.Size);
					Stream.ReadRaw<uint32_t>(Chunk.FirstIndexToChange);
					Stream.ReadRaw<uint32_t>(Chunk.LastIndexToChange);
					for (int i = 0; i < 8; i++)
					{
						Stream.ReadRaw<uint8_t>(Useless);
					}

					for (auto& E : Chunk.Entries)
					{
						uint8_t Pixel;
						E.ChunkType = AsepriteChunkType::NewPaletteChunk;
						Stream.ReadRaw<uint16_t>(E.Flags);
						Stream.ReadRaw<uint8_t>(Pixel);
						E.Pixels.push_back(Pixel);
						Stream.ReadRaw<uint8_t>(Pixel);
						E.Pixels.push_back(Pixel);
						Stream.ReadRaw<uint8_t>(Pixel);
						E.Pixels.push_back(Pixel);
						Stream.ReadRaw<uint8_t>(Pixel);
						E.Pixels.push_back(Pixel);

						if (E.Flags == 1)
						{
							Stream.ReadString(E.Name);
						}
					}

					F.NewPaletteChunks.push_back(Chunk);
				}
				
			}
		}
	}

	
void Ase
prite::ReadUserDataChunk( AsepriteFileData& Data)
	{
		AsepriteUserData Chunk;
		//uint8_t Useless;
		for (auto& F : Data.Frames)
		{
			for (auto& C : F.ChunkData)
			{
				if (C.Type == AsepriteChunkType::UserDataChunk)
				{
					MemoryStreamReader Stream((void*)C.Data.data(), C.Size);

					Stream.ReadRaw<uint32_t>(Chunk.Flags);



					if (Utils::EngineStatics::IsBitSet<uint32_t>(Chunk.Flags, 1))
					{
						Stream.ReadString(Chunk.Text);
					}
					if (Utils::EngineStatics::IsBitSet<uint32_t>(Chunk.Flags, 2))
					{
						Stream.ReadRaw<uint8_t[4]>(Chunk.RGBA);
					}
					if (Utils::EngineStatics::IsBitSet<uint32_t>(Chunk.Flags, 4))
					{
						Stream.ReadRaw<uint32_t>(Chunk.Size);
						Stream.ReadRaw<uint32_t>(Chunk.NumOfPropMaps);
						
						for (uint32_t i = 0; i < Chunk.NumOfPropMaps; i++)
						{
							uint32_t Value;

							Stream.ReadRaw<uint32_t>(Value);

							Chunk.PropMapKeyPairs.push_back(std::pair<uint32_t, uint32_t>(i, Value));
							uint32_t NumOfProps;
							Stream.ReadRaw<uint32_t>(NumOfProps);
							Chunk.UserProps[i].resize(NumOfProps);

							for (auto& KV : Chunk.UserProps[i])
							{
								Stream.ReadString(KV.Name);
								Stream.ReadRaw<uint16_t>(KV.Type);

								switch ((AsepritePropertyTypes)KV.Type)
								{
								case AsepritePropertyTypes::Boolean:
								{
									KV.PropData.Type = KV.Type;
									Stream.ReadRaw<bool>(KV.PropData.Boolean);
									break;
								}
								case AsepritePropertyTypes::Int8:
								{
									KV.PropData.Type = KV.Type;
									Stream.ReadRaw<int8_t>(KV.PropData.Int8);
									break;
								}
								case AsepritePropertyTypes::Int16:
								{
									KV.PropData.Type = KV.Type;
									Stream.ReadRaw<int16_t>(KV.PropData.Int16);
									break;
								}
								case AsepritePropertyTypes::Uint16:
								{
									KV.PropData.Type = KV.Type;
									Stream.ReadRaw<uint16_t>(KV.PropData.Uint16);
									break;
								}
								case AsepritePropertyTypes::Int32:
								{
									KV.PropData.Type = KV.Type;
									Stream.ReadRaw<int32_t>(KV.PropData.Int32);
									break;
								}
								case AsepritePropertyTypes::Uint32:
								{
									KV.PropData.Type = KV.Type;
									Stream.ReadRaw<uint32_t>(KV.PropData.Uint32);
									break;
								}
								case AsepritePropertyTypes::Int64:
								{
									KV.PropData.Type = KV.Type;
									Stream.ReadRaw<int64_t>(KV.PropData.Int64);
									break;
								}
								case AsepritePropertyTypes::Uint64:
								{
									KV.PropData.Type = KV.Type;
									Stream.ReadRaw<uint64_t>(KV.PropData.Uint64);
									break;
								}
								case AsepritePropertyTypes::Fixed:
								{
									KV.PropData.Type = KV.Type;
									Stream.ReadRaw<double>(KV.PropData.Fixed);
									break;
								}
								case AsepritePropertyTypes::Float:
								{
									KV.PropData.Type = KV.Type;
									Stream.ReadRaw<float>(KV.PropData.Float);
									break;
								}
								case AsepritePropertyTypes::Double:
								{
									KV.PropData.Type = KV.Type;
									Stream.ReadRaw<double>(KV.PropData.Double);
									break;
								}
								case AsepritePropertyTypes::String:
								{
									KV.PropData.Type = KV.Type;
									Stream.ReadString(KV.PropData.String);
									break;
								}
								case AsepritePropertyTypes::Point:
								{
									KV.PropData.Type = KV.Type;
									int32_t A;
									int32_t B;
									Stream.ReadRaw<int32_t>(A);
									Stream.ReadRaw<int32_t>(B);
									KV.PropData.Point = { A,B };
									break;
								}
								case AsepritePropertyTypes::Size:
								{
									KV.PropData.Type = KV.Type;
									int32_t A;
									int32_t B;
									Stream.ReadRaw<int32_t>(A);
									Stream.ReadRaw<int32_t>(B);
									KV.PropData.Size = { A,B };
									break;
								}
								case AsepritePropertyTypes::Rect:
								{
									int32_t A;
									int32_t B;
									int32_t W;
									int32_t H;
									Stream.ReadRaw<int32_t>(A);
									Stream.ReadRaw<int32_t>(B);
									Stream.ReadRaw<int32_t>(W);
									Stream.ReadRaw<int32_t>(H);
									KV.PropData.Rect = { A,B, W,H };
									break;
								}
								case AsepritePropertyTypes::Vector:
								{
									//We probably need to do some sort of recursion here
									Stream.ReadRaw<uint32_t>(KV.NumofElementsInVec);
									Stream.ReadRaw<uint16_t>(KV.ElementsType);
									if (KV.ElementsType == 0)
									{
										for ([[maybe_unused]] uint32_t e = 0; i < KV.NumofElementsInVec; e++)
										{
											//Get Type
											uint16_t Type;
											Stream.ReadRaw<uint16_t>(Type);
											//Convert Type

											//Start Recursion
											ProcessElement(&Stream, ConvertToType(Type), KV);
										}
		
									}
									else
									{
										std::vector<std::byte> Bytes;
										for (uint32_t e = 0; e < KV.NumofElementsInVec; e++)
										{
											Stream.ReadBytes(Bytes, 4);
										}
									}
									CoreLogger::Error("Not Implemented");
									break;
								}
								case AsepritePropertyTypes::NestedMapProps:
								{
									uint32_t NumOfProperties;
									Stream.ReadRaw<uint32_t>(NumOfProperties);
									std::vector<std::byte> Bytes;
									CoreLogger::Error("Not Implemented");

									for (uint32_t p = 0; p < NumOfProperties; p++)
									{
										Stream.ReadBytes(Bytes, sizeof(std::map<std::string, AsepriteVariant>));
									}

									break;
								}
								case AsepritePropertyTypes::UUID:
								{

									Stream.ReadRaw<uint8_t[16]>(KV.UUID);
									break;
								}
								}
							}
						}

					}

				}
			}
		}
	}

	
void Ase
prite::ReadSliceChunk( AsepriteFileData& Data)
	{
		AsepriteSliceChunk Chunk;
		uint32_t Useless;

		for (auto& F : Data.Frames)
		{
			for (auto& C : F.ChunkData)
			{
				if (C.Type == AsepriteChunkType::SliceChunk)
				{
					MemoryStreamReader Stream((void*)C.Data.data(), C.Size);

					Stream.ReadRaw<uint32_t>(Chunk.NumOfSliceKeys);
					Chunk.Slices.resize(Chunk.NumOfSliceKeys);
					Stream.ReadRaw<uint32_t>(Chunk.Flags);
					Stream.ReadRaw<uint32_t>(Useless);
					Stream.ReadString(Chunk.Name);

					for (auto& S: Chunk.Slices)
					{
						Stream.ReadRaw<uint32_t>(S.FrameNumber);
						Stream.ReadRaw<int32_t>(S.SliceX);
						Stream.ReadRaw<int32_t>(S.SliceY);
						Stream.ReadRaw<uint32_t>(S.SliceWidth);
						Stream.ReadRaw<uint32_t>(S.SliceHeight);

						if (Utils::EngineStatics::IsBitSet<uint32_t>(Chunk.Flags, 1))
						{
							Stream.ReadRaw<int32_t>(S.CenterX);
							Stream.ReadRaw<int32_t>(S.CenterY);
							Stream.ReadRaw<uint32_t>(S.CenterWidth);
							Stream.ReadRaw<uint32_t>(S.CenterHeight);
						}

						if (Utils::EngineStatics::IsBitSet<uint32_t>(Chunk.Flags, 2))
						{
							Stream.ReadRaw<int32_t>(S.PivotX);
							Stream.ReadRaw<int32_t>(S.PivotY);
						}
					}
				}
			}
		}
	}

	
void Ase
prite::ReorderLayers(const std::string& Filename)
	{
		bool ZIndexExist = false;


		for (auto& F : m_AsepriteData[Filename].Frames)
		{
			for (auto& L : F.Layers)
			{
				for (int s = 0; s < (int)L.CelChunks.size(); ++s)
				{
					const int z = L.CelChunks[(size_t)s].zIndex;
					if (z != 0)
					{
						ZIndexExist = true;
						break;
					}
				}
			}

		}

		if (!ZIndexExist)
		{
			return;
		}


		for (auto& F : m_AsepriteData[Filename].Frames)
		{
			for (auto& L : F.Layers)
			{
				std::sort(L.CelChunks.begin(), L.CelChunks.end(), [](const AsepriteCelChunk& A, const AsepriteCelChunk& B)
					{
						return (A.order() < B.order()) || (A.order() == B.order() && (A.zIndex < B.zIndex));
					});
			}

		}

	}

	/**
 * @brief Get the file name from a path string
 * @param Path The filesystem path to extract the file name from
 * @return The base file name without extension, or an empty string if no filename is found.
 */
std::str
ing Aseprite::GetFileName(const std::filesystem::path& Path)
	{

		std::string base = Path.string().substr(Path.string().find_last_of("/\\") + 1);
		std::string::size_type const p(base.find_last_of('.'));
		std::string filename = base.substr(0, p);

		if (!filename.empty())
		{
			return filename;
		}

		return std::string();
	}
	/**
 * @brief Converts a uint16_t to an AsepritePropertyTypes enum.
 *
 * This function takes in a uint16_t and casts it to the AsepritePropertyTypes enum type. 
 * It is used for converting raw data into meaningful enums that represent properties of an Aseprite object.
 *
 * @param T The uint16_t value to be converted.
 * @return An instance of AsepritePropertyTypes corresponding to the input uint16_t.
 */
Aseprite/**
 * @brief Converts a uint16_t to AsepritePropertyTypes.
 *
 * This function takes an unsigned 16-bit integer as input and returns the corresponding enum value from the AsepritePropertyTypes enumeration.
 *
 * @param T The unsigned 16-bit integer to convert.
 * @return The converted enum value, or UNKNOWN if the conversion is not possible.
 */
PropertyTypes Aseprite::ConvertToType(uint16_t T)
	{
		return (AsepritePropertyTypes)T;
	}
	<doxygen comment>
void Ase
prite::ProcessElement(MemoryStreamReader* Stream, AsepritePropertyTypes T, AsepriteUserProps& Data)
	{
		switch (T)
		{
		case AsepritePropertyTypes::Boolean:
		{
			bool b;
			Stream->ReadRaw<bool>(b);
			Data.PropData.Vec.push_back(b);
			break;
		}
		case AsepritePropertyTypes::Int8:
		{
			int8_t i8;
			Stream->ReadRaw<int8_t>(i8);
			Data.PropData.Vec.push_back(i8);
			break;
		}
		case AsepritePropertyTypes::Int16:
		{
			int16_t i16;
			Stream->ReadRaw<int16_t>(i16);
			Data.PropData.Vec.push_back(i16);
			break;
		}
		case AsepritePropertyTypes::Uint16:
		{
			uint16_t u16;
			Stream->ReadRaw<uint16_t>(u16);
			Data.PropData.Vec.push_back(u16);
			break;
		}
		case AsepritePropertyTypes::Int32:
		{
			int32_t i32;
			Stream->ReadRaw<int32_t>(i32);
			Data.PropData.Vec.push_back(i32);
			break;
		}
		case AsepritePropertyTypes::Uint32:
		{
			uint32_t u32;
			Stream->ReadRaw<uint32_t>(u32);
			Data.PropData.Vec.push_back(u32);
			break;
		}
		case AsepritePropertyTypes::Int64:
		{
			int64_t i64;
			Stream->ReadRaw<int64_t>(i64);
			Data.PropData.Vec.push_back(i64);
			break;
		}
		case AsepritePropertyTypes::Uint64:
		{
			uint64_t u64;
			Stream->ReadRaw<uint64_t>(u64);
			Data.PropData.Vec.push_back(u64);
			break;
		}
		case AsepritePropertyTypes::Fixed:
		{
			double d;
			Stream->ReadRaw<double>(d);
			Data.PropData.Vec.push_back(d);
			break;
		}
		case AsepritePropertyTypes::Float:
		{
			float f;
			Stream->ReadRaw<float>(f);
			Data.PropData.Vec.push_back(f);
			break;
		}
		case AsepritePropertyTypes::Double:
		{
			double d;
			Stream->ReadRaw<double>(d);
			Data.PropData.Vec.push_back(d);
			break;
		}
		case AsepritePropertyTypes::String:
		{
			std::string Str;
			Stream->ReadString(Str);
			Data.PropData.Vec.push_back(Str);
			break;
		}
		case AsepritePropertyTypes::Point:
		{
			int32_t A;
			int32_t B;
			Stream->ReadRaw<int32_t>(A);
			Stream->ReadRaw<int32_t>(B);
			Data.PropData.Vec.push_back(AGEPoint( A,B ));
			break;
		}
		case AsepritePropertyTypes::Size:
		{
			int32_t A;
			int32_t B;
			Stream->ReadRaw<int32_t>(A);
			Stream->ReadRaw<int32_t>(B);
			Data.PropData.Vec.push_back(AGESize( A,B ));
			break;
		}
		case AsepritePropertyTypes::Rect:
		{
			int32_t A;
			int32_t B;
			int32_t C;
			int32_t D;
			Stream->ReadRaw<int32_t>(A);
			Stream->ReadRaw<int32_t>(B);
			Stream->ReadRaw<int32_t>(C);
			Stream->ReadRaw<int32_t>(D);
			Data.PropData.Vec.push_back(AGERect(A,B,C,D ));
			break;
		}
		case AsepritePropertyTypes::Vector:
		{
			uint32_t Num;
			uint16_t ElemType;
			Stream->ReadRaw<uint32_t>(Num);
			Stream->ReadRaw<uint16_t>(ElemType);
			if (ElemType == 0)
			{
				for (uint32_t i = 0; i < Num; i++)
				{
					uint16_t Type;
					Stream->ReadRaw<uint16_t>(Type);

					//Continue Recursion
					ProcessElement(Stream, ConvertToType(Type), Data);
				}

			}
			else
			{
				std::vector<std::byte> Bytes;
				for (uint32_t i = 0; i < Num; i++)
				{
					Stream->ReadBytes(Bytes, 4);
				}
			}
			CoreLogger::Error("Not Implemented");  //This is here because even if it does work it's going to require a lot more code to actually be of use so i don't want people thinking they can use it as-is
			break;
		}
		case AsepritePropertyTypes::NestedMapProps:
		{
			break;
		}
		case AsepritePropertyTypes::UUID:
		{
			break;
		}
		}

	}
}