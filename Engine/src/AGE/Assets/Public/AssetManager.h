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
		/**
 * @brief Constructs an AssetRegistry object.
 * 
 * This constructor initializes the ShaderLibrary, Aseprite manager and sets the AudioManager pointer.
 * 
 * @param AudioManagerPtr Pointer to the AudioManager instance.
 */
AssetRegistry(AudioManager* AudioManagerPtr)
		{
			m_ShaderLibrary = CreateRef<ShaderLibrary>();
			m_AespriteManager = CreateScope<Aseprite>();
			m_AudioManager = AudioManagerPtr;
		}
		COMMENT:
/**
 * @brief Default destructor for the AssetRegistry class.
 *
 * This function is responsible for releasing any resources that were acquired by the AssetRegistry instance, such as memory or file handles. It does not perform any operations on the actual assets stored in the registry. 
 *
 * @return void
 */
CONFIDENCE: 1.0;

~AssetRegistry() = default;
		/**
 * @brief This function is a copy constructor for the AssetRegistry class and it has been explicitly deleted to prevent copying of objects.
 * 
 * @param[in] other The object to be copied from.
 * 
 * @return None as this function does not return anything.
 */
AssetRegistry(const AssetRegistry&) = delete;
		/**
 * @brief AssetRegistry is a class that manages assets in the game engine. It provides methods for loading and unloading assets, as well as querying information about them.
 * The move constructor of this class has been explicitly deleted to prevent copying of AssetRegistry objects. This is because AssetRegistry objects are meant to be 
 * moved around rather than copied, which could lead to inefficient memory usage or other issues.
 * @param rhs The object to be moved from.
 */
AssetRegistry(AssetRegistry&&) = delete;
		
		/**
 * Loads a texture from the given file path and returns it as a reference. If the texture is already loaded, it will return that instance instead of loading again.
 * The function checks if the texture is already loaded by its UUID (which is generated when the texture is first loaded). If so, it directly returns the existing texture. 
 * If not, it checks the file extension to determine how to load the texture: for .aseprite files, it uses an AespriteManager to read and create a Texture2D object; for all other extensions, it creates a new Texture2D object using the provided path.
 * The function also generates a UUID for each loaded texture and stores them in a map for later retrieval. 
 */
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

		/**
 * @brief Retrieves a texture from the map using its UUID.
 *
 * This function searches for a Texture2D object in the m_TextureAssets map with the given ID. If it finds one, it returns a reference to that object. 
 * If no such object is found, it logs an error message and returns a null reference.
 *
 * @param ID The UUID of the texture to retrieve.
 * @return A reference to the Texture2D object if it exists in the map, otherwise a null reference.
 */
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
		/**
 * @brief Retrieves a reference to the Texture2D object associated with the given name.
 * 
 * This function iterates over all stored texture assets and checks if any of them have the same name as the input parameter 'Name'. If it finds one, it returns a reference to that asset. Otherwise, it logs an error message and returns a null reference.
 * 
 * @param Name The name of the Texture2D object to retrieve.
 * @return A reference to the Texture2D object with the given name, or nullptr if no such object exists.
 */
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

		/**
 * @brief Checks if a texture is loaded based on its file path.
 *
 * This function iterates over the map of textures (m_TextureAssets) and checks each one to see if its 
 * GetTextureFilePath() matches the provided path. If it does, the function returns true indicating that 
 * the texture is loaded. Otherwise, it returns false.
 *
 * @param Path The file path of the texture to check for.
 * @return True if the texture is loaded, false otherwise.
 */
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

		/**
 * @brief Checks whether a texture with the given UUID is loaded or not.
 * 
 * This function checks if the texture associated with the provided UUID has been loaded into memory. It does this by comparing the value of `m_TextureAssets[ID]` to `nullptr`. If it's equal, then the texture hasn't been loaded and the function returns false; otherwise, it returns true.
 * 
 * @param ID The UUID of the texture to check for.
 * @return True if the texture is loaded (i.e., its value in `m_TextureAssets[ID]` isn't null), False otherwise.
 */
bool IsTextureLoaded(const UUID ID)
		{
			return m_TextureAssets[ID] == nullptr;
		}


		/**
 * @brief Checks if a texture is loaded based on its file path.
 * 
 * This function iterates over the map of textures (m_TextureAssets) and checks if any of them have the same file path as provided in 'Path'. If it finds one, it sets 'OutID' to the UUID associated with that texture and returns true. Otherwise, it returns false.
 * 
 * @param Path The file path of the texture to check for.
 * @param OutID A reference to a UUID variable where the ID of the loaded texture will be stored if found.
 * @return True if a texture is loaded with the same file path as 'Path', False otherwise.
 */
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

		/**
 * @brief This function loads a shader from the specified file path.
 * 
 * @param FilePath The path to the shader file.
 * @return void
 */
void LoadShader(const std::string& FilePath)
		{
			m_ShaderLibrary->Load(FilePath);
		}
		/**
 * @brief Loads two shaders from the given file paths.
 * 
 * This function loads and compiles two shaders specified by their file paths. The first shader is loaded from the path provided in `FilePath1`, while the second one is loaded from the path provided in `FilePath2`.
 *
 * @param FilePath1 A constant reference to a string representing the file path of the first shader.
 * @param FilePath2 A constant reference to a string representing the file path of the second shader.
 */
void LoadShader(const std::string& FilePath1, const std::string& FilePath2)
		{
			m_ShaderLibrary->Load(FilePath1, FilePath2);
		}
		/**
 * @brief Loads a shader into the library.
 * 
 * This function loads a shader with a given name and source code string into the shader library.
 * The shader's name is an integer identifier, and its source code is a string representation of the shader's GLSL code.
 * @param Name Integer identifier for the shader.
 * @param Source String representing the GLSL code of the shader.
 * @return void
 */
void LoadShader(const int Name, const std::string& Source)
		{
			m_ShaderLibrary->Load(Name, Source);
		}
		/**
 * @brief Gets a shader from the library.
 * 
 * This function retrieves a shader object with the specified name from the shader library. If no such shader exists, it returns an empty reference.
 * 
 * @param Name The name of the shader to retrieve.
 * @return A reference to the requested shader if found; otherwise, an empty reference.
 */
Ref<Shader> GetShader(const std::string& Name)
		{
			return m_ShaderLibrary->Get(Name);
		}

		/**
 * @brief Checks if a shader exists in the library.
 * 
 * This function takes a constant reference to a string representing the name of the shader. It then uses this name to check if the shader exists within the shader library. The result is returned as a boolean value, indicating whether or not the shader exists.
 * 
 * @param Name A const std::string& representing the name of the shader to be checked for in the library.
 * @return bool Returns true if the shader exists and false otherwise.
 */
bool DoesShaderExist(const std::string& Name)
		{
			return m_ShaderLibrary->Exists(Name);
		}

		/**
 * @brief Loads a scene from the specified file path and returns it as a reference.
 * 
 * The function attempts to load a scene from the provided file path using the SceneSerializer class. If successful, it adds the loaded scene to the scenes map with its UUID as key and returns a reference to it. Otherwise, it logs an error message and returns a null reference.
 * 
 * @param Filepath The path of the file containing the serialized scene data.
 * @return A reference to the loaded Scene object if successful; otherwise, a null reference.
 */
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

		/**
 * @brief Retrieves a scene from the scenes map using its unique identifier (UUID).
 * 
 * @param ID The unique identifier of the scene to be retrieved.
 * @return A reference to the requested Scene object. If no such scene exists, an empty reference is returned.
 */
Ref<Scene> GetScene(const UUID ID)
		{
			return m_Scenes[ID];
		}

		/**
 * @brief GetScene is a function that retrieves a scene from the map of scenes by its name.
 *
 * @param[in] Name The name of the scene to be retrieved.
 * 
 * @return A reference to the Scene object if it exists, otherwise nullptr.
 */
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
			return nullptr;
		}

		/**
 * @brief GetAllScenes returns a vector of all scenes in the scene manager.
 * 
 * This function iterates over the map m_Scenes, where each element is a pair of an identifier and a reference to a Scene object. It emplaces back every second element (the actual Scene objects) into the vector Scenes which it then returns.
 * 
 * @return A vector containing all scenes in the scene manager.
 */
std::vector<Ref<Scene>> GetAllScenes()
		{
			std::vector<Ref<Scene>> Scenes;
			for (auto& S : m_Scenes)
			{
				Scenes.emplace_back(S.second);
			}

			return Scenes;
		}

		/**
 * @brief Checks if a scene with the given path is loaded.
 *
 * This function checks whether there exists a scene in the manager's list of scenes that has the same name as the file at the provided path.
 * 
 * @param Path The filesystem path to the scene file.
 * @return True if a scene with the same filename exists, false otherwise.
 */
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

		/**
 * @brief Load a font from the specified file path and return its reference.
 * 
 * This function creates a new instance of AGEFont with the provided file path, generates a UUID for it, stores the font in the map m_Fonts using the generated UUID as key, and finally returns the newly created font's reference.
 * 
 * @param Filepath The path to the font file.
 * @return Reference to the loaded font.
 */
Ref<AGEFont> LoadFont(const std::filesystem::path& Filepath)
		{
			Ref<AGEFont> NewFont = CreateRef<AGEFont>(Filepath);

			UUID ID = UUID();
			NewFont->GetAtlasTexture()->SetAssetID(ID);

			m_Fonts.emplace(NewFont->GetAtlasTexture()->GetAssetID(), NewFont);

			return GetFont(ID);
		}

		/**
 * @brief Get the font with a given UUID.
 * 
 * This function retrieves the font associated with the provided UUID from the map of fonts (m_Fonts). If the font is found, it returns a reference to that font; otherwise, it returns an empty reference.
 * 
 * @param ID The UUID of the font to retrieve.
 * @return A reference to the requested font if it exists in m_Fonts; otherwise, an empty reference.
 */
Ref<AGEFont> GetFont(const UUID& ID)
		{
			auto it = m_Fonts.find(ID);

			if (it != m_Fonts.end())
			{
				return it->second;
			}
			return Ref<AGEFont>(nullptr);
		}

		/**
 * @brief Retrieves a font from the collection based on its name.
 * 
 * This function iterates over all fonts in the collection and checks if their atlas texture's name matches the provided one. If it does, the corresponding font is returned. Otherwise, nullptr is returned to indicate that no such font exists.
 * 
 * @param Name The name of the font to retrieve.
 * @return A reference to the font with the given name or nullptr if no such font exists.
 */
Ref<AGEFont> GetFont(const std::string& Name)
		{
			for (auto& F : m_Fonts)
			{
				if (F.second->GetAtlasTexture()->GetName() == Name)
				{
					return F.second;
				}
			}

			return Ref<AGEFont>(nullptr);
		}
		/**
 * @brief Get the names of all available fonts.
 * 
 * This function retrieves a list of all font names that are currently loaded in the system. If the list is empty, it populates it by iterating over all loaded fonts and adding their respective names to the list.
 * 
 * @return A const reference to the vector containing the names of all available fonts.
 */
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

		/**
 * @brief Checks if a font is loaded.
 *
 * This function checks whether the given file path corresponds to any of the fonts in the system. 
 * It does this by iterating over all stored fonts and comparing their atlas texture paths with the provided one.
 * If there's a match, it returns true; otherwise, false.
 *
 * @param Filepath The path of the font file to check for.
 * @return True if the font is loaded, False otherwise.
 */
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
			default:
			{
				return false;
			}
			}

			return false;
		}

		/**
 * @brief Checks if a soundbank is loaded based on the provided file path.
 * 
 * This function checks whether a soundbank with the given filepath has been loaded by comparing it to the list of loaded banks in the audio engine.
 * It handles two different types of engines: Wwise and FMod, each with its own specific implementation. If no engine type is specified or if an unsupported one is provided, the function returns false.
 * 
 * @param Filepath The path to the soundbank file.
 * @return True if the soundbank is loaded, false otherwise.
 */
bool IsSoundbankLoaded(const std::filesystem::path& Filepath)
		{
			std::filesystem::path Path = Filepath;
			switch (m_AudioManager->GetAudioEngineType())
			{
			case AudioEngineType::WWiseEngine:
			{
#if WITH_WWISE
				CoreLogger::Assert(false, "Checking for loaded soundbanks with Wwise is not Implemented yet!");
				return false;
#else
				CoreLogger::Error("Engine was not build with Wwise Support! Enable WITH_WWISE and provide a path to the SDK directory in CMake!");
				return false;
#endif
				break;
			}

			case AudioEngineType::FModEngine:
			{
#if WITH_FMOD
				if (m_AudioManager->GetAudioEngine()->As<FmodEngine>()->GetBanks()[Utils::EngineStatics::GetFilename(Path)])
				{
					return true;
				}
#else
				CoreLogger::Error("Engine was not build with FMod Support! Enable WITH_FMOD and provide a path to the SDK directory in CMake!");
#endif
				break;
			}
			default:
			{
				return false;
			}
			}

			return false;
		}
		/**
 * @brief Loads a sound file from the given path and returns a reference to it. The sound is stored in an internal map with its UUID as key for later retrieval.
 * 
 * @param Filepath Path of the sound file to be loaded.
 * @return Reference to the newly created AudioSource object.
 */
Ref<AudioSource> LoadSound(const std::filesystem::path& Filepath)
		{
			Ref<AudioSource> Sound = CreateRef<AudioSource>(Filepath.string());
			UUID ID = UUID();
			Sound->SetAssetID(ID);

			m_Sounds.emplace(ID, Sound);

			return GetSound(ID);
		}

		/**
 * @brief Retrieves an AudioSource with the given UUID from the map of sounds.
 * 
 * This function takes a UUID as input and attempts to find it in the m_Sounds map. If the UUID is found, the corresponding Ref<AudioSource> object is returned. Otherwise, a null Ref<AudioSource> object is returned.
 * 
 * @param ID The UUID of the AudioSource to retrieve.
 * @return A Ref<AudioSource> object that corresponds to the input UUID, or a null object if no such UUID exists in m_Sounds.
 */
Ref<AudioSource> GetSound(const UUID& ID)
		{
			auto it = m_Sounds.find(ID);

			if (it != m_Sounds.end())
			{
				return it->second;
			}

			return Ref<AudioSource>(nullptr);
		}

		/**
 * @brief Retrieves an AudioSource with a specific name from the map of sounds.
 * 
 * This function iterates over all entries in the m_Sounds map and checks if the GetName() method of each AudioSource matches the provided Name parameter. If it does, that AudioSource is returned. If no match is found, a nullptr-initialized Ref<AudioSource> object is returned.
 * 
 * @param[in] Name The name to search for in the map of sounds.
 * @return A reference to an AudioSource with the specified name if it exists, otherwise a nullptr-initialized Ref<AudioSource> object.
 */
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

		/**
 * @brief Checks if a sound is loaded from the given file path.
 *
 * This function iterates over all sounds stored in the m_Sounds container and checks 
 * if any of them has the same file path as provided. If it finds one, it returns true; 
 * otherwise, it returns false.
 *
 * @param Filepath The file path to check for.
 * @return True if a sound is loaded from the given file path, false otherwise.
 */
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


		/**
 * @brief Returns a reference to the unordered map containing all scenes.
 * 
 * This function returns a reference to an unordered map that contains all the scenes in the system. The key is of type UUID and the value is of type Ref<Scene>, which represents a scene object.
 * 
 * @return std::unordered_map<UUID, Ref<Scene>>& A reference to the unordered map containing all scenes.
 */
std::unordered_map<UUID, Ref<Scene>>& GetScenes()
		{
			return m_Scenes;
		}
		/**
 * @brief Returns a reference to the unordered map containing all Texture2D assets.
 * 
 * This function returns a reference to an unordered map that contains all Texture2D assets. The key-value pairs in this map are UUIDs and their corresponding Texture2D objects.
 * 
 * @return A reference to the unordered_map<UUID, Ref<Texture2D>> containing all Texture2D assets.
 */
std::unordered_map<UUID, Ref<Texture2D>>& GetTextures()
		{
			return m_TextureAssets;
		}
		/**
 * @brief Returns a reference to the unordered map containing all fonts.
 * 
 * This function returns a reference to an unordered map that contains all the fonts in the system. The UUID is used as the key and Ref<AGEFont> is the value.
 * 
 * @return std::unordered_map<UUID, Ref<AGEFont>>& A reference to the unordered map containing all fonts.
 */
std::unordered_map<UUID, Ref<AGEFont>>& GetFonts()
		{
			return m_Fonts;
		}
		/**
 * @brief Returns a reference to the unordered map containing all Audio Sources.
 * 
 * This function returns a reference to an unordered map that contains all instances of Audio Source objects in the system. The UUIDs are used as keys for this map, and each value is a shared pointer (Ref) to an instance of AudioSource.
 *
 * @return A reference to the unordered_map<UUID, Ref<AudioSource>> m_Sounds.
 */
std::unordered_map<UUID, Ref<AudioSource>>& GetSounds()
		{
			return m_Sounds;
		}
		/**
 * @brief Returns a reference to the unordered map containing all SoundBanks.
 * 
 * This function returns a reference to an unordered map that contains all SoundBanks in the system. The UUIDs are used as keys, and the corresponding values are references (Ref<SoundBank>).
 * 
 * @return A reference to the unordered_map containing all SoundBanks.
 */
std::unordered_map<UUID, Ref<SoundBank>>& GetSoundbanks()
		{
			return m_SoundBanks;
		}
		/**
 * @brief Returns a reference to the shader library object.
 * 
 * This function returns a reference to the ShaderLibrary object, which contains all the shaders used in the application.
 * The returned reference allows for modification of the shaders if necessary.
 * 
 * @return A reference to the ShaderLibrary object.
 */
Ref<ShaderLibrary>& GetShaders()
		{
			return m_ShaderLibrary;
		}
		std::unordered_map<UUID,Ref<Scene>> m_Scenes;
		std::unordered_map<UUID, Ref<Texture2D>> m_TextureAssets;
		std::unordered_map<UUID, Ref<AGEFont>> m_Fonts;
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
		/**
 * @brief Default constructor for the AssetPak class.
 *
 * This function initializes an instance of the AssetPak class with default values. It does not take any parameters and returns nothing.
 */
AssetPak() = default;
		COMMENT:
/**
 * @brief Default destructor for the AssetPak class.
 * 
 * This function is used to clean up any resources that are being used by an instance of the AssetPak class. It does not take any parameters and returns void.
 */
CONFIDENCE: 1.0;

~AssetPak() = default;
		/**
 * @brief This function is a copy constructor for the AssetPak class and it has been explicitly deleted to prevent copying of objects.
 * 
 * @param[in] other The object to be copied.
 * 
 * @return None as this function does not return anything.
 */
AssetPak(const AssetPak&) = delete;
		/**
 * @brief Move constructor for AssetPak class.
 *
 * This function is marked as deleted to prevent copying of AssetPak objects, which would lead to unnecessary memory usage and potential issues with multi-threading.
 * 
 * @param other The AssetPak object to be moved from.
 */
AssetPak(AssetPak&&) = delete;

	private:

		size_t m_OffsetTableSize = 0;
		std::vector<std::tuple<uint64_t, uint32_t, size_t>> m_OffsetTable;
	};


	class AssetManager final
	{
	public:

		/**
 * @brief Returns a reference to the global instance of AssetManager.
 * @return Reference to the global AssetManager instance.
 */
static AssetManager& Get() { return *s_Instance; }

		/**
 * @brief Default constructor for the AssetManager class.
 */
AssetManager() = default;
		AssetManager(const std::filesystem::path& GameContentPath);
		AssetManager(void* AddrToPakFile, size_t SizeOfPakFile = 0);

		/**
 * @brief Returns the game content path.
 *
 * This function returns a reference to the game content path, which is used as the root directory for all game-related content files.
 * The returned path may be empty if it has not been set yet.
 * 
 * @return A reference to the game content path.
 */
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

		Ref<AGEFont> LoadFont(const std::filesystem::path& Filepath);
		Ref<AGEFont> GetFont(const UUID& ID);
		Ref<AGEFont> GetFont(const std::string& Name);
		bool IsFontLoaded(const std::filesystem::path& Filepath);

		void LoadSoundbank(const std::filesystem::path& Filepath);

		bool IsSoundbankLoaded(const std::filesystem::path& Filepath);

		Ref<AudioSource> LoadSound(const std::filesystem::path& Filepath);
		Ref<AudioSource> GetSound(const UUID& ID);
		Ref<AudioSource> GetSound(const std::string& Name);

		bool IsSoundLoaded(const std::filesystem::path& Filepath);

		/**
 * @brief Retrieves the Asset Registry object associated with this instance.
 * @return A reference to the Asset Registry object.
 */
Ref<AssetRegistry> GetAssetRegistry() const { return m_Registry; }
	private:

		static AssetManager* s_Instance;
		Ref<AssetRegistry> m_Registry;
		std::filesystem::path m_GameContentPath;
		std::pair<AssetPak*, size_t> m_PakPair;
	};
}
