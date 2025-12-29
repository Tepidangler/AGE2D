#include "AGEpch.hpp"
#include "Sprite/Public/Aseprite.h"
#include "Statics/Public/Statics.h"
#include "Texture/Public/Texture.h"
#include <intrin.h>

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

		for (auto& F : m_AsepriteData[Filename].Frames)
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

	Ref<Texture2D> Aseprite::CreateTexture(std::string ImageName)
	{
		auto& Img = m_ImagePairs[ImageName];
		return Texture2D::Create(Img.get(), Img->GetImageSpec().GetWidth(), Img->GetImageSpec().GetHeight(), Img->GetImageSpec().GetChannels(), Img->GetImageByteSize());
	}

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

		for (int i = 0; i < Size; i++)
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
							Chunk.Colors[x] = Color;
						}
					}
					F.OldPaletteChunks.push_back(Chunk);
				}

			}
		}

	}

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

	AsepriteCelChunk Aseprite::ReadCelChunk(AsepriteFileData& Data)
	{
		AsepriteCelChunk CelChunk;
		uint8_t Useless;
		int Index = 0;

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

					for (int i = 0; i < Chunk.NumOfTags; i++)
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

	void Aseprite::ReadNewPaletteChunk( AsepriteFileData& Data)
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

	void Aseprite::ReadUserDataChunk( AsepriteFileData& Data)
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
									int32_t C;
									int32_t D;
									Stream.ReadRaw<int32_t>(A);
									Stream.ReadRaw<int32_t>(B);
									Stream.ReadRaw<int32_t>(C);
									Stream.ReadRaw<int32_t>(D);
									KV.PropData.Rect = { A,B, C,D };
									break;
								}
								case AsepritePropertyTypes::Vector:
								{
									//We probably need to do some sort of recursion here
									Stream.ReadRaw<uint32_t>(KV.NumofElementsInVec);
									Stream.ReadRaw<uint16_t>(KV.ElementsType);
									if (KV.ElementsType == 0)
									{
										for (uint32_t i = 0; i < KV.NumofElementsInVec; i++)
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
										for (uint32_t i = 0; i < KV.NumofElementsInVec; i++)
										{
											Stream.ReadBytes(Bytes, 4);
										}
									}
									CoreLogger::Error("Not Implemented");
									break;
								}
								case AsepritePropertyTypes::NestedMapProps:
								{
									uint32_t NumOfProps;
									Stream.ReadRaw<uint32_t>(NumOfProps);
									std::vector<std::byte> Bytes;
									CoreLogger::Error("Not Implemented");

									for (uint32_t i = 0; i < NumOfProps; i++)
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

	void Aseprite::ReadSliceChunk( AsepriteFileData& Data)
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

	void Aseprite::ReorderLayers(const std::string& Filename)
	{
		bool ZIndexExist = false;


		for (auto& F : m_AsepriteData[Filename].Frames)
		{
			for (auto& L : F.Layers)
			{
				for (int i = 0; i < (int)L.CelChunks.size(); ++i)
				{
					const int z = L.CelChunks[i].zIndex;
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

	std::string Aseprite::GetFileName(const std::filesystem::path& Path)
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
	AsepritePropertyTypes Aseprite::ConvertToType(uint16_t T)
	{
		return (AsepritePropertyTypes)T;
	}
	void Aseprite::ProcessElement(MemoryStreamReader* Stream, AsepritePropertyTypes T, AsepriteUserProps& Data)
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