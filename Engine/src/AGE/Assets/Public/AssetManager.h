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
 * This function is responsible for releasing any resources that were acquired by the AssetRegistry object, such as memory or file handles. It does not perform any operations on the actual assets stored in the registry.
 * 
 * @return void
 */
CONFIDENCE: 1.0;

~AssetRegistry() = default;
		/**
 * @brief Deleted copy constructor for the AssetRegistry class to prevent copying.
 * @param other The instance of the AssetRegistry that is being copied.
 */
AssetRegistry(const AssetRegistry&) = delete;
		/**
 * @brief AssetRegistry is a class that manages assets in the game engine. It's designed to be efficient and secure, but it doesn't allow copying or moving instances of this class for safety reasons.
 * 
 * @return The function does not return any value.
 */
AssetRegistry(AssetRegistry&&) = delete;
		
		/**
 * Loads a texture from the given file path and returns it as a reference. If the texture is already loaded, it will return that instance instead of loading again.
 * The function checks if the texture is already loaded by its UUID. If so, it directly returns the existing texture. Otherwise, it creates a new Texture2D object based on the file type: .aseprite for AespriteManager, and regular image files otherwise. 
 * After creating the texture, it assigns an unique UUID to it and stores it in m_TextureAssets map with its UUID as key. Finally, it returns the loaded Texture2D object from m_TextureAssets using its UUID.
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
 * @brief Retrieves a texture from the asset manager using its UUID.
 * 
 * This function searches for a Texture2D object in the m_TextureAssets map with the given ID. If it finds one, it returns a reference to that object. Otherwise, it logs an error and returns a nullptr.
 * @param ID The UUID of the texture to retrieve.
 * @return A Reference (Ref) to the Texture2D object if found, otherwise nullptr.
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
 * This function iterates over all stored texture assets and checks if any of them have the same name as the input parameter 'Name'. If it finds one, it returns a reference to that Texture2D object. Otherwise, it logs an error message and returns a null reference.
 * 
 * @param Name The name of the Texture2D asset to retrieve.
 * @return A reference to the requested Texture2D object if found, otherwise nullptr.
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
 * This function iterates over the map of textures (m_TextureAssets) and checks if any 
 * texture's GetTextureFilePath() matches the provided path. If it does, the function 
 * returns true indicating that the texture is loaded. Otherwise, it returns false.
 *
 * @param Path The file path to check for a loaded texture.
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
 * @brief Checks whether a texture with the given ID is loaded or not.
 *
 * This function checks if the texture associated with the provided UUID (Universally Unique Identifier) is already loaded in memory. 
 * It does this by comparing the value of `m_TextureAssets[ID]` to `nullptr`. If it's equal, then the texture has not been loaded and the function returns false; otherwise, if it's not equal (i.e., the texture is loaded), the function returns true.
 * 
 * @param ID The UUID of the texture to check for.
 * @return True if the texture with the given ID is loaded, False otherwise.
 */
bool IsTextureLoaded(const UUID ID)
		{
			return m_TextureAssets[ID] == nullptr;
		}


		/**
 * @brief Checks if a texture is loaded based on its file path.
 *
 * This function iterates over the map of textures (m_TextureAssets) and checks if any of them have the same file path as the one provided. 
 * If it finds a match, it sets the OutID parameter to the UUID associated with that texture and returns true. Otherwise, it returns false.
 *
 * @param Path The file path of the texture to check for.
 * @param OutID A reference to an UUID variable which will be set if the texture is found.
 * 
 * @return Returns true if a texture with the given file path exists in m_TextureAssets, false otherwise.
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
 * @brief This function loads a shader from the given file path.
 * 
 * @param FilePath The path to the shader file.
 * @return void
 */
void LoadShader(const std::string& FilePath)
		{
			m_ShaderLibrary->Load(FilePath);
		}
		/** 
 * @brief This function loads two shaders from the given file paths.
 * @param[in] FilePath1 The path to the first shader file.
 * @param[in] FilePath2 The path to the second shader file.
 * @return void
 */
void LoadShader(const std::string& FilePath1, const std::string& FilePath2)
		{
			m_ShaderLibrary->Load(FilePath1, FilePath2);
		}
		/**
 * @brief This function loads a shader into the Shader Library.
 * 
 * @param Name The identifier for the shader to be loaded.
 * @param Source The source code of the shader.
 * 
 * @return void
 */
void LoadShader(const int Name, const std::string& Source)
		{
			m_ShaderLibrary->Load(Name, Source);
		}
		/**
 * @brief Gets a shader from the library by name.
 * 
 * This function retrieves a shader object from the library using the provided name. If the shader does not exist, it will return an empty reference.
 * 
 * @param Name The name of the shader to retrieve.
 * @return A reference to the shader with the given name, or an empty reference if no such shader exists in the library.
 */
Ref<Shader> GetShader(const std::string& Name)
		{
			return m_ShaderLibrary->Get(Name);
		}

		/**
 * @brief Checks if a shader with the given name exists.
 * 
 * This function checks whether a shader with the specified name exists in the shader library.
 * It returns true if the shader exists and false otherwise.
 * 
 * @param Name The name of the shader to check for.
 * @return True if the shader exists, false otherwise.
 */
bool DoesShaderExist(const std::string& Name)
		{
			return m_ShaderLibrary->Exists(Name);
		}

		/**
 * @brief Loads a scene from the specified file path and returns it as a reference.
 * 
 * If the function is unable to load the scene due to an error, it will log an error message and return nullptr.
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
 * @brief Retrieves a scene with the given UUID from the map of scenes.
 * 
 * This function takes in an UUID and returns the corresponding Scene object from the map 'm_Scenes'. If no such scene exists, it will return an empty Ref<Scene>.
 * 
 * @param ID The UUID of the scene to be retrieved.
 * @return A reference to the requested Scene if found in the map; otherwise, an empty Ref<Scene>.
 */
Ref<Scene> GetScene(const UUID ID)
		{
			return m_Scenes[ID];
		}

		/**
 * @brief GetScene is a function that retrieves a scene from the map of scenes by its name.
 * @param Name The name of the scene to be retrieved.
 * @return A reference to the Scene object if it exists, otherwise nullptr. If no such scene exists, an error message will be logged and nullptr will be returned.
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
 * @brief GetAllScenes returns a vector of all scenes in the system.
 * 
 * This function iterates over the map m_Scenes and emplaces each scene into the returned vector. The scenes are stored as Ref<Scene> objects, which allows for polymorphic usage.
 * 
 * @return std::vector<Ref<Scene>> A vector containing all scenes in the system.
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
 * @brief Checks if a scene is loaded based on its path.
 *
 * This function takes in the file system path of a potential scene and checks if it exists within the list of currently loaded scenes. 
 * It does this by comparing the filename part of the path with the names of all currently loaded scenes.
 *
 * @param Path The file system path to check for a loaded scene.
 * @return True if a scene is found at the given path, false otherwise.
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
 * @brief Load a font from the specified filepath and return its reference.
 * 
 * This function creates a new instance of AGEFont with the provided filepath, generates a UUID for it, stores the font in the map m_Fonts using the generated UUID as key, then returns the newly created font's reference.
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
 * @brief Retrieves a font with the given UUID from the map of fonts.
 * 
 * This function searches for a font in the map 'm_Fonts' using the provided UUID. If the font is found, it returns a reference to that font. Otherwise, it returns a null reference.
 * @param ID The UUID of the font to be retrieved.
 * @return A reference to the font with the given UUID if it exists in 'm_Fonts'. Otherwise, a null reference.
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
 * This function iterates over all fonts in the collection and checks if their atlas texture's name matches the provided one. If it does, that font is returned. Otherwise, nullptr is returned to indicate that no such font exists.
 * 
 * @param Name The name of the font to retrieve.
 * @return A reference to the requested font or a null reference if no matching font was found.
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
 * This function retrieves a list of font names from the internal map of fonts. If the list is empty, it populates it by iterating over each font in the map and adding its name to the list. The resulting list is then returned.
 * 
 * @return A const reference to a vector of strings representing the names of all available fonts.
 */
const std::vector<std::string>& GetFontNames()
		{
			if (m_FontNames.empty())
			{
				for (auto& F : m_Fonts)
				{
					m_FontNames.emplace_back(F.second->GetFontName());
				}
			}
			return m_FontNames;
		}

		/**
 * @brief Checks if a font is loaded.
 *
 * This function checks whether the given file path corresponds to any of the fonts in the system. 
 * It does this by iterating over all stored fonts and comparing their atlas texture paths with the provided one.
 * If it finds a match, it returns true indicating that the font is loaded. Otherwise, it returns false.
 *
 * @param Filepath The path of the file to check for.
 * 
 * @return True if the font is loaded, false otherwise.
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

		/**
 * @brief Registers a new font with the system.
 * 
 * This function takes in a reference to an AGEFont object and adds it to the map of registered fonts. The key for this entry is the AssetID of the font, which can be accessed using GetAssetID() method on the font object.
 *
 * @param[in] font - Reference to the font that needs to be registered.
 * 
 * @return void
 */
void RegisterFont(const Ref<AGEFont>& font)
		{
			m_Fonts.emplace(font->GetAssetID(), font);
		}


		/**
 * @brief Loads a sound bank from the specified file path.
 * 
 * This function loads a sound bank into the audio manager based on the type of audio engine currently in use. If the audio engine is WWise, it directly loads the bank into the audio engine using `AudioEngine::LoadBank`. For FModEngine, it creates a Sound Bank object and then loads that into the audio engine.
 * 
 * @param Filepath The path to the sound bank file.
 * @return True if the sound bank was successfully loaded, false otherwise.
 */
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
 * @brief Checks if a soundbank is loaded.
 * 
 * This function checks whether a soundbank with the given filepath is loaded based on the audio engine type in use by the AudioManager.
 * It supports two types of engines - Wwise and FMod. For each, it uses preprocessor directives to check if the corresponding SDKs are enabled during compilation.
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
 * @brief Loads a sound file from the specified path and returns a reference to it.
 * 
 * The function creates an AudioSource object with the given filepath, generates a UUID for the sound, stores the sound in the m_Sounds map under its ID, then retrieves and returns the sound using its ID.
 * 
 * @param Filepath The path of the sound file to load.
 * @return A reference to the loaded AudioSource object.
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
 * @brief Retrieves an AudioSource with the given UUID from the map m_Sounds.
 * 
 * This function takes a constant reference to a UUID (ID) and attempts to find it in the map m_Sounds. If the ID is found, the corresponding Ref<AudioSource> object is returned. Otherwise, a null pointer is returned.
 * 
 * @param ID The UUID of the AudioSource to retrieve from the map.
 * @return A Ref<AudioSource> object that corresponds to the given UUID in m_Sounds. If no such object exists, a null pointer is returned.
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
 * This function iterates over all entries in the m_Sounds map and checks if the GetName() method of each entry returns the same string as the input parameter 'Name'. If it does, that entry is returned. If no such entry exists, a nullptr is returned.
 * 
 * @param Name The name to search for in the AudioSource objects.
 * @return A Ref<AudioSource> object representing the found sound or nullptr if not found.
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
 * @brief Checks if a sound is loaded based on the file path.
 *
 * This function iterates over all sounds stored in the m_Sounds map and checks 
 * if any of them have the same file path as provided. If it finds one, it returns true; otherwise, false.
 *
 * @param Filepath The file path to check for.
 * @return True if a sound with the given file path is loaded, false otherwise.
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
 * This function returns a reference to an unordered map that contains all the scenes in the system. The key is of type UUID and the value is of type Ref<Scene>, which represents a scene reference.
 * 
 * @return A reference to the unordered map containing all scenes.
 */
std::unordered_map<UUID, Ref<Scene>>& GetScenes()
		{
			return m_Scenes;
		}
		/**
 * @brief Returns a reference to the unordered map containing all texture assets.
 * 
 * This function returns a reference to an unordered map that contains all Texture2D assets currently loaded in the game. The UUIDs of these textures are used as keys for this map.
 *
 * @return A reference to the unordered_map<UUID, Ref<Texture2D>> containing all texture assets.
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
 * @return std::unordered_map<UUID, Ref<AGEFont>>& A reference to the m_Fonts member variable.
 */
std::unordered_map<UUID, Ref<AGEFont>>& GetFonts()
		{
			return m_Fonts;
		}
		/**
 * @brief Returns a reference to the unordered map containing all audio sources.
 * 
 * This function returns a reference to an unordered map that contains all AudioSource objects in the system. The UUIDs of these objects are used as keys for this map.
 *
 * @return A reference to the unordered map m_Sounds.
 */
std::unordered_map<UUID, Ref<AudioSource>>& GetSounds()
		{
			return m_Sounds;
		}
		/**
 * @brief Returns a reference to the unordered map containing all SoundBanks.
 * 
 * This function returns a reference to an unordered map that contains all SoundBanks in the system. The keys of this map are UUIDs and the values are references (Ref) to SoundBank objects.
 * 
 * @return A reference to the unordered_map<UUID, Ref<SoundBank>> containing all SoundBanks.
 */
std::unordered_map<UUID, Ref<SoundBank>>& GetSoundbanks()
		{
			return m_SoundBanks;
		}
		/**
 * @brief Gets the shader library reference.
 * 
 * This function returns a reference to the shader library object, which can be used to access and manipulate the shaders in the library.
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
 */
AssetPak() = default;
		/**
 * @brief Default destructor for the AssetPak class.
 *
 * This function is used to clean up any resources that are being held by an instance of the AssetPak class. It should be called when an object of this class is no longer needed, to ensure proper memory management and prevent potential issues with dangling pointers or other resource leaks.
 */
~AssetPak() = default;
		/**
 * @brief This function is a copy constructor for the AssetPak class and it has been explicitly deleted to prevent copying of objects.
 * @param other The object to be copied.
 */
AssetPak(const AssetPak&) = delete;
		/**
 * @brief Move constructor for AssetPak class.
 *
 * This function is marked as deleted to prevent copying of AssetPak objects, which would not be efficient or safe.
 * It should only be used when moving an existing object into a new one.
 * 
 * @param[in] other The temporary object being moved from.
 */
AssetPak(AssetPak&&) = delete;

	//private:

		//size_t m_OffsetTableSize = 0;
		//std::vector<std::tuple<uint64_t, uint32_t, size_t>> m_OffsetTable;
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

		template<typename T>
		/**
 * @brief Registers an asset of type T into the system.
 * 
 * This function registers an asset of a specific type (T) into the system. If the type is AudioSource, it will log an error message saying that registering audio sources is currently unsupported. For AGEFont and Texture2D types, it will call the RegisterFont method on the registry object with the given asset as parameter.
 * 
 * @param Asset The asset to be registered.
 */
void RegisterAsset(Ref<T> Asset)
		{
			if (std::is_same<T, AudioSource>::value)
			{
				CoreLogger::Error("Registering Audio Sources is currently unsupported!");
				return;
			}
			if (std::is_same<T, AGEFont>::value)
			{
				m_Registry->RegisterFont(Asset);
				return;
			}
			if (std::is_same<T, Texture2D>::value)
			{
				CoreLogger::Error("Registering Textures is currently unsupported!");
				return;
			}


		}
	private:

		static AssetManager* s_Instance;
		Ref<AssetRegistry> m_Registry;
		std::filesystem::path m_GameContentPath;
		std::pair<AssetPak*, size_t> m_PakPair;
	};
}
