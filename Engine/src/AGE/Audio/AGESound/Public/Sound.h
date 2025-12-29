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

		std::string GetFilePath() const { return m_FilePath; }
		std::string GetName() const { return m_Name; }
		UUID& GetAssetID() { return m_AssetID; }

		void SetAssetID(const UUID& ID) { m_AssetID = ID; }
		void SetPosition(const Vector3& P);
		void SetPosition(float x, float y, float z);
		void SetGain(float Gain);
		void SetPitch(float Pitch);
		void SetSpatial(bool Spatial);
		void SetLoop(bool Loop);
		void SetPlaying(bool Playing) { bIsPlaying = Playing; }
		void SetSoundData(std::vector<char> Data) { m_SoundData = Data; }

		std::pair<uint32_t, uint32_t> GetLengthMinutesAndSeconds() const;


		static AudioSource LoadFromFile(const std::string& File, bool Spatial = false);

		bool IsLooping() { return bLoop; }
		bool IsLoaded() const { return bLoaded; }
		bool IsPlaying() const { return bIsPlaying; }

	private:
		AudioSource() = default;
		AudioSource(const AudioSource&) = default;
		AudioSource(uint32_t Handle, bool Loaded, float Length);
		AudioSource(uint32_t Handle, bool Loaded, float Length, std::vector<char> Data);


	private:

		uint32_t m_BufferHandle = 0;
		uint32_t m_SourceHandle = 0;
		UUID m_AssetID;

		bool bLoaded = false;
		bool bSpatial = false;
		bool bIsPlaying = false;
		float m_TotalDuration = 0; //Seconds

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