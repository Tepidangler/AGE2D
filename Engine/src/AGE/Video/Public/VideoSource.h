#pragma once
#include "Core/Public/Core.h"
#include "Texture/Public/Texture.h"

#include <string>



namespace AGE
{

	class VideoSource
	{
	public:
		 VideoSource(const std::string& FilePath);

		std::string GetFileName() { return m_FilePath; }

		uint32_t GetNumberOfFrames() { return m_NumberOfFrames; }
		int GetNumberOfFramesPlayed() { return m_FrameCount; }
		double GetFramesPerSecond() { return m_FramesPerSecond; }
		uint32_t GetWidth() { return m_Width; }
		uint32_t GetHeight() { return m_Height; }
		int GetChannels() { return m_Channels; }
		Ref<Texture2D>& GetTexture() { return m_Texture; }



		void SeekFrame();
		void ReadFrame();
		void MakeTexture();
		void IncrementFrameCount();


		void SetTextureData(uint8_t* Data)
		{
			m_Texture->SetData(Data, (m_Width * m_Height * m_Channels));
		}

		bool IsLoaded() { return bLoaded && m_Texture; }
		~VideoSource();

	private:

		VideoSource() = default;
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
