#include "AGEpch.hpp"
#include "Assets/Public/AssetManager.h"
#include "Core/Public/App.h"
#include "Audio/AGESound/Public/Sound.h"

namespace AGE
{
	AssetManager* AssetManager::s_Instance = nullptr;

	AssetManager::AssetManager(const std::filesystem::path& GameContentPath)
		:m_GameContentPath(GameContentPath)
	{
		m_Registry = CreateRef<AssetRegistry>(&App::Get().GetDeviceManager().GetAudioManager());
		AGE_CORE_ASSERT(!s_Instance, "Asset Manager Already Exists");
		s_Instance = this;
	}
	AssetManager::AssetManager(void* AddrToPakFile, size_t SizeOfPakFile)
	{
		m_PakPair.first = (AssetPak*)AddrToPakFile;
		m_PakPair.second = SizeOfPakFile;
		AGE_CORE_ASSERT(!s_Instance, "Asset Manager Already Exists");
		s_Instance = this;
	}
	bool AssetManager::LoadPakFile(void* AddrToPakFile, size_t SizeOfPakFile)
	{
		m_PakPair.first = reinterpret_cast<AssetPak*>(AddrToPakFile);
		m_PakPair.second = SizeOfPakFile;
		return m_PakPair.first != nullptr;
	}
	Ref<Texture2D> AssetManager::LoadTexture(const std::filesystem::path& FilePath)
	{
		return m_Registry->LoadTexture(FilePath);
	}
	Ref<Texture2D> AssetManager::LoadTexture(void* Addr, size_t Size)
	{
		AGE::CoreLogger::Warn("Binary loading of Assets is currently not implemented!, returning nullptr!");
		return Ref<Texture2D>(nullptr);
	}
	Ref<Texture2D> AssetManager::GetTexture(UUID ID)
	{
		return m_Registry->GetTexture(ID);
	}
 /**
     @brief  Much slower option considering I had to implement the find function for this myself, however in the event that you don't know
	 the ID for the particular texture you want to load you can search for it based on the name which == the filename
     @param  Name - Name of Texture
     @retval      - A newly created shared_ptr with the texture
 **/
	Ref<Texture2D> AssetManager::GetTexture(const std::string& Name)
	{
		return m_Registry->GetTexture(Name);
	}
	bool AssetManager::IsTextureLoaded(const std::filesystem::path& Filepath)
	{
		return m_Registry->IsTextureLoaded(Filepath);
	}
	void AssetManager::LoadShader(const std::string& FilePath)
	{
		m_Registry->LoadShader(FilePath);
	}
	void AssetManager::LoadShader(const std::string& FilePath1, const std::string& FilePath2)
	{
		m_Registry->LoadShader(FilePath1, FilePath2);
	}
	void AssetManager::LoadShader(const int Name, const std::string& Source)
	{
		m_Registry->LoadShader(Name, Source);
	}
	Ref<Shader> AssetManager::GetShader(const std::string& Name)
	{
		return m_Registry->GetShader(Name);
	}
	bool AssetManager::DoesShaderExist(const std::string& Name)
	{
		return m_Registry->DoesShaderExist(Name);
	}
	Ref<Scene> AssetManager::LoadScene(const std::filesystem::path& Filepath)
	{
		return m_Registry->LoadScene(Filepath);
	}
	void AssetManager::GetSceneNames(std::vector<std::string>& OutArray)
	{
		std::vector<Ref<Scene>> Scenes = m_Registry->GetAllScenes();
		if (Scenes.size() == 0)
		{
			CoreLogger::Warn("There where no scenes Loaded!");
			return;
		}
		OutArray.clear();
		OutArray.shrink_to_fit();
		OutArray.resize(Scenes.size());
		for (int i = 0; i < OutArray.size(); ++i)
		{
			OutArray[i] = Scenes[i]->GetName();
		}

	}
	Ref<Texture2D> AssetManager::LoadAsepriteFile(const std::filesystem::path& Filepath)
	{
		return m_Registry->LoadTexture(Filepath);
	}
	Ref<Texture2D> AssetManager::GetAsepriteTexture(const UUID& ID)
	{
		return m_Registry->GetTexture(ID);
	}
	Ref<Texture2D> AssetManager::GetAsepriteTexture(const std::string& Name)
	{
		return m_Registry->GetTexture(Name);
	}
	bool AssetManager::IsAsepriteFileLoaded(const std::filesystem::path& Filepath)
	{
		return m_Registry->IsTextureLoaded(Filepath);
	}
	Ref<Font> AssetManager::LoadFont(const std::filesystem::path& Filepath)
	{		
		return m_Registry->LoadFont(Filepath);
	}
	Ref<Font> AssetManager::GetFont(const UUID& ID)
	{
		return m_Registry->GetFont(ID);
	}
	Ref<Font> AssetManager::GetFont(const std::string& Name)
	{
		return m_Registry->GetFont(Name);
	}
	bool AssetManager::IsFontLoaded(const std::filesystem::path& Filepath)
	{
		return m_Registry->IsFontLoaded(Filepath);
	}
	void AssetManager::LoadSoundbank(const std::filesystem::path& Filepath)
	{
		m_Registry->LoadSoundbank(Filepath);
	}
	bool AssetManager::IsSoundbankLoaded(const std::filesystem::path& Filepath)
	{
		return m_Registry->IsSoundbankLoaded(Filepath);
	}
	bool AssetManager::IsSceneLoaded(const std::filesystem::path& Filepath)
	{
		return m_Registry->IsSceneLoaded(Filepath);
	}
	Ref<Scene> AssetManager::GetScene(const UUID& ID)
	{
		return m_Registry->GetScene(ID);
	}
	Ref<Scene> AssetManager::GetScene(const std::string& Name)
	{
		return m_Registry->GetScene(Name);
	}
	Ref<AudioSource> AssetManager::LoadSound(const std::filesystem::path& Filepath)
	{
		return m_Registry->LoadSound(Filepath);
	}
	Ref<AudioSource> AssetManager::GetSound(const UUID& ID)
	{
		return m_Registry->GetSound(ID);
	}
	Ref<AudioSource> AssetManager::GetSound(const std::string& Name)
	{
		return m_Registry->GetSound(Name);
	}
	bool AssetManager::IsSoundLoaded(const std::filesystem::path& Filepath)
	{
		return m_Registry->IsSoundLoaded(Filepath);
	}

}