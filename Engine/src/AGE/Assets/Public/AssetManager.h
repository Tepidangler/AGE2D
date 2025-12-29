#pragma once
#include "Core/Public/Core.h"
#include "Texture/Public/Texture.h"
#include "Render/Public/Shader.h"
#include "Core/Public/UUID.h"
#include "Scene/Public/Scene.h"
#include "Render/Public/Font.h"
#include "Sprite/Public/Aseprite.h"
#include "Core/Public/DeviceManager.h"
#include "Audio/Wwise/Public/WWiseEngine.h"
#include "Audio/Fmod/Public/FmodEngine.h"
#include "Audio/AGESound/Public/Sound.h"
#include "Utils/Public/Serializers.h"
#include "Statics/Public/Statics.h"
#include <filesystem>
#include <unordered_map>
#include <vector>

#include "Audio/AudioEngine/Public/Soundbank.h"

namespace AGE 
{

	struct AssetRegistry final
	{
		AssetRegistry(AudioManager* AudioManagerPtr)
		{
			m_ShaderLibrary = CreateRef<ShaderLibrary>();
			m_AespriteManager = CreateScope<Aseprite>();
			m_AudioManager = AudioManagerPtr;
		}
		~AssetRegistry() = default;
		AssetRegistry(const AssetRegistry&) = delete;
		AssetRegistry(AssetRegistry&&) = delete;
		
		Ref<Texture2D> LoadTexture(const std::filesystem::path& FilePath)
		{
			UUID ID;
			if (IsTextureLoaded(FilePath, ID))
			{
				return GetTexture(ID);
			}

			if (FilePath.extension().string() == ".aseprite")
			{
				m_AespriteManager->ReadData(FilePath);
				std::filesystem::path Path = FilePath;
				Ref<Texture2D> Tex = m_AespriteManager->CreateImage(Utils::EngineStatics::GetFilename(Path), true, true);
				Tex->SetAssetID(UUID());
				m_TextureAssets.emplace(Tex->GetAssetID(), Tex);

				return GetTexture(Tex->GetAssetID());
			}

			Ref<Texture2D> Tex = Texture2D::Create(FilePath.string());
			Tex->SetAssetID(UUID());
			m_TextureAssets.emplace(Tex->GetAssetID(), Tex);

			return GetTexture(Tex->GetAssetID());
		}

		Ref<Texture2D> GetTexture(UUID ID)
		{
			auto it = m_TextureAssets.find(ID);

			if (it != m_TextureAssets.end())
			{
				return it->second;
			}
			else
			{
				AGE::CoreLogger::Error("Texture with ID {0} not found, returning nullptr", (uint64_t)ID);
				return Ref<Texture2D>(nullptr);
			}
		}
		Ref<Texture2D> GetTexture(const std::string& Name)
		{
			for (auto& T : m_TextureAssets)
			{
				if (T.second->GetName() == Name)
				{
					return T.second;
				}
			}
			AGE::CoreLogger::Error("Texture with Name {0} not found, returning nullptr", Name.c_str());
			return Ref<Texture2D>(nullptr);
		}

		bool IsTextureLoaded(const std::filesystem::path& Path)
		{
			for (auto& T : m_TextureAssets)
			{
				if (T.second->GetTextureFilePath() == Path.string())
				{
					return true;
				}
			}
			return false;
		}

		bool IsTextureLoaded(const UUID ID)
		{
			return m_TextureAssets[ID] == nullptr;
		}


		bool IsTextureLoaded(const std::filesystem::path& Path, UUID& OutID)
		{
			for (auto& T : m_TextureAssets)
			{
				if (T.second->GetTextureFilePath() == Path.string())
				{
					OutID = T.first;
					return true;
				}
			}
			return false;
		}

		void LoadShader(const std::string& FilePath)
		{
			m_ShaderLibrary->Load(FilePath);
		}
		void LoadShader(const std::string& FilePath1, const std::string& FilePath2)
		{
			m_ShaderLibrary->Load(FilePath1, FilePath2);
		}
		void LoadShader(const int Name, const std::string& Source)
		{
			m_ShaderLibrary->Load(Name, Source);
		}
		Ref<Shader> GetShader(const std::string& Name)
		{
			return m_ShaderLibrary->Get(Name);
		}

		bool DoesShaderExist(const std::string& Name)
		{
			return m_ShaderLibrary->Exists(Name);
		}

		Ref<Scene> LoadScene(const std::filesystem::path& Filepath)
		{
			CoreLogger::Info("Attempting to Load Scene from path {0}", Filepath.string());
			Ref<Scene> Asset = CreateRef<Scene>();
			SceneSerializer Serializer(Asset);
			const bool bLoaded = Serializer.Deserialize(Filepath.string());
			
			if (bLoaded)
			{
				m_Scenes.emplace(std::pair<UUID,Ref<Scene>>(Asset->GetAssetID(), Asset));
				return GetScene(Asset->GetAssetID());
			}
			CoreLogger::Error("Failed To Load Scene with path: {0}, returning nullptr!", Filepath.string());
			return Ref<Scene>(nullptr);
		}

		Ref<Scene> GetScene(const UUID ID)
		{
			return m_Scenes[ID];
		}

		Ref<Scene> GetScene(const std::string& Name)
		{
			for (auto& S : m_Scenes)
			{
				if (S.second->GetName() == Name)
				{
					return S.second;
				}
			}

			CoreLogger::Error("Unable to Find Scene with name {0}", Name.c_str());
		}

		std::vector<Ref<Scene>> GetAllScenes()
		{
			std::vector<Ref<Scene>> Scenes;
			for (auto& S : m_Scenes)
			{
				Scenes.emplace_back(S.second);
			}

			return Scenes;
		}

		bool IsSceneLoaded(const std::filesystem::path& Path)
		{
			std::filesystem::path P = Path;
			std::string Name = Utils::EngineStatics::GetFilename(P);
			for (auto& S : m_Scenes)
			{
				if (S.second->GetName() == Name)
				{
					return true;
				}
			}

			return false;
		}

		Ref<Font> LoadFont(const std::filesystem::path& Filepath)
		{
			Ref<Font> NewFont = CreateRef<Font>(Filepath);

			UUID ID = UUID();
			NewFont->GetAtlasTexture()->SetAssetID(ID);

			m_Fonts.emplace(NewFont->GetAtlasTexture()->GetAssetID(), NewFont);

			return GetFont(ID);
		}

		Ref<Font> GetFont(const UUID& ID)
		{
			auto it = m_Fonts.find(ID);

			if (it != m_Fonts.end())
			{
				return it->second;
			}
			return Ref<Font>(nullptr);
		}

		Ref<Font> GetFont(const std::string& Name)
		{
			for (auto& F : m_Fonts)
			{
				if (F.second->GetAtlasTexture()->GetName() == Name)
				{
					return F.second;
				}
			}

			return Ref<Font>(nullptr);
		}
		const std::vector<std::string>& GetFontNames()
		{
			if (m_FontNames.empty())
			{
				for (auto& F : m_Fonts)
				{
					m_FontNames.emplace_back(F.second->GetAtlasTexture()->GetName());
				}
			}
			return m_FontNames;
		}

		bool IsFontLoaded(const std::filesystem::path& Filepath)
		{
			for (auto& F : m_Fonts)
			{
				if (F.second->GetAtlasTexture()->GetTextureFilePath() == Filepath)
				{
					return true;
				}
			}

			return false;
		}


		bool LoadSoundbank(const std::filesystem::path& Filepath)
		{
			std::filesystem::path Path = Filepath;
			switch (m_AudioManager->GetAudioEngineType())
			{
			case AudioEngineType::WWiseEngine:
			{
				m_AudioManager->GetAudioEngine()->LoadBank(CreateRef<SoundBank>(Filepath, UUID()));
				return true;
				break;
			}

			case AudioEngineType::FModEngine:
			{
				Ref<SoundBank> Bank = CreateRef<SoundBank>(Filepath, UUID());
				m_AudioManager->GetAudioEngine()->LoadBank(Bank);
				m_SoundBanks.emplace(std::pair<UUID, Ref<SoundBank>>(Bank->GetAssetID(), Bank));
				return true;
				break;
			}
			}

			return false;
		}

		bool IsSoundbankLoaded(const std::filesystem::path& Filepath)
		{
			std::filesystem::path Path = Filepath;
			switch (m_AudioManager->GetAudioEngineType())
			{
			case AudioEngineType::WWiseEngine:
			{
				AGE_CORE_ASSERT(false, "Checking for loaded soundbanks with Wwise is not Implemented yet!")
				return false;
				break;
			}

			case AudioEngineType::FModEngine:
			{
				if (m_AudioManager->GetAudioEngine()->As<FmodEngine>()->GetBanks()[Utils::EngineStatics::GetFilename(Path)])
				{
					return true;
				}
				break;
			}
			}

			return false;
		}
		Ref<AudioSource> LoadSound(const std::filesystem::path& Filepath)
		{
			Ref<AudioSource> Sound = CreateRef<AudioSource>(Filepath.string());
			UUID ID = UUID();
			Sound->SetAssetID(ID);

			m_Sounds.emplace(ID, Sound);

			return GetSound(ID);
		}

		Ref<AudioSource> GetSound(const UUID& ID)
		{
			auto it = m_Sounds.find(ID);

			if (it != m_Sounds.end())
			{
				return it->second;
			}

			return Ref<AudioSource>(nullptr);
		}

		Ref<AudioSource> GetSound(const std::string& Name)
		{
			for (auto& S : m_Sounds)
			{
				if (S.second->GetName() == Name)
				{
					return S.second;
				}
			}

			return Ref<AudioSource>(nullptr);
		}

		bool IsSoundLoaded(const std::filesystem::path& Filepath)
		{
			for (auto& S : m_Sounds)
			{
				if (S.second->GetFilePath() == Filepath)
				{
					return true;
				}
			}

			return false;
		}


		std::unordered_map<UUID, Ref<Scene>>& GetScenes()
		{
			return m_Scenes;
		}
		std::unordered_map<UUID, Ref<Texture2D>>& GetTextures()
		{
			return m_TextureAssets;
		}
		std::unordered_map<UUID, Ref<Font>>& GetFonts()
		{
			return m_Fonts;
		}
		std::unordered_map<UUID, Ref<AudioSource>>& GetSounds()
		{
			return m_Sounds;
		}
		std::unordered_map<UUID, Ref<SoundBank>>& GetSoundbanks()
		{
			return m_SoundBanks;
		}
		Ref<ShaderLibrary>& GetShaders()
		{
			return m_ShaderLibrary;
		}
		std::unordered_map<UUID,Ref<Scene>> m_Scenes;
		std::unordered_map<UUID, Ref<Texture2D>> m_TextureAssets;
		std::unordered_map<UUID, Ref<Font>> m_Fonts;
		std::unordered_map<UUID, Ref<AudioSource>> m_Sounds;
		std::unordered_map<UUID, Ref<SoundBank>> m_SoundBanks;
		std::vector<std::string> m_FontNames;
		Ref<ShaderLibrary> m_ShaderLibrary;

		AudioManager* m_AudioManager;
		Scope<Aseprite> m_AespriteManager;
	};

	class AssetPak final
	{
	public:
		AssetPak() = default;
		~AssetPak() = default;
		AssetPak(const AssetPak&) = delete;
		AssetPak(AssetPak&&) = delete;

	private:

		size_t m_OffsetTableSize = 0;
		std::vector<std::tuple<uint64_t, uint32_t, size_t>> m_OffsetTable;
	};


	class AssetManager final
	{
	public:

		static AssetManager& Get() { return *s_Instance; }

		AssetManager() = default;
		AssetManager(const std::filesystem::path& GameContentPath);
		AssetManager(void* AddrToPakFile, size_t SizeOfPakFile = 0);

		std::filesystem::path& GetGameContentPath() { return m_GameContentPath; }
		bool LoadPakFile(void* AddrToPakFile, size_t SizeOfPakFile = 0);

		Ref<Texture2D> LoadTexture(const std::filesystem::path& FilePath);
		Ref<Texture2D> LoadTexture(void* Addr, size_t Size);

		Ref<Texture2D> GetTexture(UUID ID);
		Ref<Texture2D> GetTexture(const std::string& Name);

		bool IsTextureLoaded(const std::filesystem::path& Filepath);

		void LoadShader(const std::string& FilePath);
		void LoadShader(const std::string& FilePath1, const std::string& FilePath2);
		void LoadShader(const int Name, const std::string& Source);
		Ref<Shader> GetShader(const std::string& Name);
		bool DoesShaderExist(const std::string& Name);

		Ref<Scene> LoadScene(const std::filesystem::path& Filepath);
		Ref<Scene> GetScene(const UUID& ID);
		Ref<Scene> GetScene(const std::string& Name);
		bool IsSceneLoaded(const std::filesystem::path& Filepath);

		void GetSceneNames(std::vector<std::string>& OutArray);

		Ref<Texture2D> LoadAsepriteFile(const std::filesystem::path& Filepath);
		Ref<Texture2D> GetAsepriteTexture(const UUID& ID);
		Ref<Texture2D> GetAsepriteTexture(const std::string& Name);
		bool IsAsepriteFileLoaded(const std::filesystem::path& Filepath);

		Ref<Font> LoadFont(const std::filesystem::path& Filepath);
		Ref<Font> GetFont(const UUID& ID);
		Ref<Font> GetFont(const std::string& Name);
		bool IsFontLoaded(const std::filesystem::path& Filepath);

		void LoadSoundbank(const std::filesystem::path& Filepath);

		bool IsSoundbankLoaded(const std::filesystem::path& Filepath);

		Ref<AudioSource> LoadSound(const std::filesystem::path& Filepath);
		Ref<AudioSource> GetSound(const UUID& ID);
		Ref<AudioSource> GetSound(const std::string& Name);

		bool IsSoundLoaded(const std::filesystem::path& Filepath);

		Ref<AssetRegistry> GetAssetRegistry() const { return m_Registry; }
	private:

		static AssetManager* s_Instance;
		Ref<AssetRegistry> m_Registry;
		std::filesystem::path m_GameContentPath;
		std::pair<AssetPak*, size_t> m_PakPair;
	};
}
