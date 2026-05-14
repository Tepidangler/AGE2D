#include "AGEpch.hpp"
#include "Assets/Public/AssetManager.h"
#include "Core/Public/App.h"
#include "Audio/AGESound/Public/Sound.h"

namespace AGE
{
	AssetManager* AssetManager::s_Instance = nullptr;

	/**
 * @brief Constructor for the AssetManager class. Initializes the game content path and creates an instance of the AssetRegistry.
 * @param GameContentPath The path to the game's content directory.
 */
/**
 * @brief Constructor for AssetManager class.
 *
 * This constructor initializes the AssetManager with a given game content path and creates an instance of AssetRegistry. It also checks if there is already an instance of AssetManager, in which case it asserts that no other instance should exist. 
 *
 * @param GameContentPath The path to the game's content directory.
 */
AssetManager::AssetManager(const std::filesystem::path& GameContentPath)
		:m_GameContentPath(GameContentPath)
	{
		m_Registry = CreateRef<AssetRegistry>(&App::Get().GetDeviceManager().GetAudioManager());
		CoreLogger::Assert(!s_Instance, "Asset Manager Already Exists");
		s_Instance = this;
	}
	/**
 * @brief Constructor for the AssetManager class.
 * 
 * This constructor initializes an instance of the AssetManager class with a pointer to a pak file and its size. It also checks if an instance of AssetManager already exists, logging an error message if it does. The instance is then set as the current one.
 * @param AddrToPakFile A void pointer to the start of the pak file memory block.
 * @param SizeOfPakFile The size of the pak file in bytes.
 */
/**
 * @brief Constructor for AssetManager class. Initializes the asset manager with a pointer to an AssetPak object and its size.
 * @param AddrToPakFile Pointer to an AssetPak object.
 * @param SizeOfPakFile Size of the AssetPak object in bytes.
 * @return None
 */
AssetManager::AssetManager(void* AddrToPakFile, size_t SizeOfPakFile)
	{
		m_PakPair.first = (AssetPak*)AddrToPakFile;
		m_PakPair.second = SizeOfPakFile;
		CoreLogger::Assert(!s_Instance, "Asset Manager Already Exists");
		s_Instance = this;
	}
	/**
 * @brief Loads a PAK file into the AssetManager.
 * 
 * This function takes in an address and size of a PAK file, stores them as members of the class,
 * and returns true if the pointer to the PAK file is not null.
 * 
 * @param AddrToPakFile A void pointer to the start of the PAK file data.
 * @param SizeOfPakFile The size of the PAK file in bytes.
 * 
 * @return True if the PAK file was successfully loaded, false otherwise.
 */
/**
 * @brief Loads a PAK file into the AssetManager.
 *
 * This function takes in an address and size of a PAK file, stores them as a pair in m_PakPair, 
 * and returns true if the pointer to the PAK file is not null.
 *
 * @param AddrToPakFile A void pointer to the start of the PAK file data.
 * @param SizeOfPakFile The size of the PAK file in bytes.
 *
 * @return True if the PAK file was successfully loaded, false otherwise.
 */
bool AssetManager::LoadPakFile(void* AddrToPakFile, size_t SizeOfPakFile)
	{
		m_PakPair.first = reinterpret_cast<AssetPak*>(AddrToPakFile);
		m_PakPair.second = SizeOfPakFile;
		return m_PakPair.first != nullptr;
	}
	/**
 * @brief Loads a texture from the specified file path.
 * 
 * This function takes in a constant reference to a filesystem path, which represents the location of the texture file on disk. It returns an instance of Ref<Texture2D>, which is essentially a smart pointer that manages the lifetime of Texture2D objects. The actual loading and management of textures is handled by the AssetManager's registry object.
 * 
 * @param FilePath A constant reference to the filesystem path of the texture file on disk.
 * @return An instance of Ref<Texture2D>, which represents a smart pointer managing the lifetime of Texture2D objects.
 */
/**
 * @brief Loads a texture from the specified file path.
 * 
 * This function takes in a constant reference to a filesystem path, which represents the location of the texture file on disk. It returns a `Ref<Texture2D>` object, which is essentially a smart pointer that manages the lifetime of a Texture2D instance. The actual loading and management of textures is handled by an internal registry in the AssetManager class.
 * 
 * @param FilePath A constant reference to a filesystem path representing the location of the texture file on disk.
 * @return Ref<Texture2D> A smart pointer that manages the lifetime of a Texture2D instance.
 */
Ref<Texture2D> AssetManager::LoadTexture(const std::filesystem::path& FilePath)
	{
		return m_Registry->LoadTexture(FilePath);
	}
	/**
 * @brief Loads a texture from binary data.
 * 
 * This function loads a Texture2D object from raw binary data. The binary data is expected to be in the format that was used when saving the texture, i.e., it should contain all necessary information for re-creating the texture.
 * 
 * @param Addr A pointer to the start of the binary data.
 * @param Size The size of the binary data in bytes.
 * 
 * @return A reference to a Texture2D object, or nullptr if the loading failed.
 */
/**
 * @brief Loads a texture from binary data.
 * 
 * This function loads a texture from the provided binary data. The binary data is expected to be in a format that can be understood by the Texture2D class, such as PNG or JPEG. If the loading fails for any reason, it returns nullptr.
 * 
 * @param Addr A pointer to the start of the binary data.
 * @param Size The size of the binary data in bytes.
 * 
 * @return A reference to a Texture2D object representing the loaded texture. If loading fails, this will be a null reference.
 */
Ref<Texture2D> AssetManager::LoadTexture(void* Addr, size_t Size)
	{
		AGE::CoreLogger::Warn("Binary loading of Assets is currently not implemented!, returning nullptr!");
		return Ref<Texture2D>(nullptr);
	}
	/**
 * @brief Retrieves a texture from the asset manager.
 * 
 * This function takes in an UUID (Universally Unique Identifier) of a texture, and returns a reference to that texture. If the texture does not exist, it will return an empty reference.
 * 
 * @param ID The UUID of the texture to retrieve.
 * @return A reference to the requested texture if it exists, otherwise an empty reference.
 */
/**
 * @brief Retrieves a reference to a Texture2D object with the given UUID.
 * 
 * This function retrieves and returns a reference to a Texture2D object from the asset manager's registry using the provided UUID.
 * The returned reference can be used for further operations on the texture, such as rendering or manipulation.
 * 
 * @param ID The UUID of the Texture2D object to retrieve.
 * @return A reference to the requested Texture2D object. If no matching Texture2D is found in the registry, an empty Ref<Texture2D> will be returned.
 */
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
	/**
 * @brief Retrieves a texture from the asset manager.
 * 
 * This function retrieves a texture with the specified name from the registry and returns it as a reference. If no such texture exists, an exception is thrown.
 * 
 * @param Name The name of the texture to retrieve.
 * @return A reference to the retrieved texture.
 * @throws std::runtime_error if there's no texture with the given name in the registry.
 */
/** 
 * @brief Retrieves a texture from the asset manager.
 * @param Name The name of the texture to retrieve.
 * @return A reference to the Texture2D object if it exists, otherwise an empty Ref<Texture2D>.
 */
Ref<Texture2D> AssetManager::GetTexture(const std::string& Name)
	{
		return m_Registry->GetTexture(Name);
	}
	/**
 *  @brief Checks if a texture is loaded.
 *  
 *  This function checks whether the given file path corresponds to an already loaded texture in the AssetManager's registry.
 *  
 *  @param Filepath The path of the texture to check for.
 *  @return True if the texture is loaded, false otherwise.
 */
/** 
 * @brief Checks if a texture is loaded.
 * 
 * This function checks whether the given file path corresponds to an already loaded texture in the AssetManager.
 * 
 * @param Filepath The path of the texture to check for.
 * @return True if the texture is loaded, false otherwise.
 */
bool AssetManager::IsTextureLoaded(const std::filesystem::path& Filepath)
	{
		return m_Registry->IsTextureLoaded(Filepath);
	}
	/**
 * @brief Loads a shader from the specified file path.
 * 
 * This function takes in a constant string reference (const std::string&) as an argument, which represents the file path of the shader to be loaded. It then calls the `LoadShader` method on the member variable m_Registry with this file path as its parameter.
 *
 * @param FilePath The file path of the shader to load.
 */
/**
 * @brief Loads a shader from the specified file path.
 * 
 * This function takes in a constant string reference, which represents the file path of the shader to be loaded. It then uses this file path to load the shader using the `LoadShader` method on the `m_Registry` object.
 * 
 * @param FilePath The file path of the shader to be loaded.
 */
void AssetManager::LoadShader(const std::string& FilePath)
	{
		m_Registry->LoadShader(FilePath);
	}
	/**
 * @brief Loads a shader from two file paths.
 * 
 * This function loads a shader using the provided file paths and registers it in the AssetManager's registry.
 * The first parameter is the path to the vertex shader file, while the second one is for the fragment (or pixel) shader.
 *
 * @param FilePath1 Path to the vertex shader file.
 * @param FilePath2 Path to the fragment shader file.
 */
/**
 * @brief Loads a shader from two file paths.
 * 
 * This function loads a shader using the provided file paths and registers it in the AssetManager's registry.
 * The first parameter is the path to the vertex shader, while the second one is for the fragment (or pixel) shader.
 * @param FilePath1 Path to the vertex shader file.
 * @param FilePath2 Path to the fragment shader file.
 */
void AssetManager::LoadShader(const std::string& FilePath1, const std::string& FilePath2)
	{
		m_Registry->LoadShader(FilePath1, FilePath2);
	}
	/**
 * @brief Loads a shader into the asset manager.
 * 
 * This function takes in an integer Name and a string reference Source. It then calls the LoadShader method on the m_Registry object with these parameters.
 * The purpose of this function is to load a shader into the AssetManager for later use.
 * 
 * @param Name A unique identifier for the shader.
 * @param Source The source code of the shader.
 */
/**
 * @brief Loads a shader into the asset manager.
 * 
 * This function takes an integer and a string as parameters. The integer is used to identify the shader in some way (e.g., its name or ID), while the string contains the source code of the shader. It then calls the `LoadShader` method on the registry object, passing these two values along.
 * 
 * @param Name A unique identifier for the shader to be loaded.
 * @param Source The source code of the shader.
 */
void AssetManager::LoadShader(const int Name, const std::string& Source)
	{
		m_Registry->LoadShader(Name, Source);
	}
	/**
 * @brief Get a shader from the registry by name.
 * 
 * This function retrieves a shader object from the asset manager's registry using the provided name.
 * The returned reference can be used to access and manipulate the shader.
 * 
 * @param Name The name of the shader to retrieve.
 * @return A reference to the requested shader, or an empty reference if no such shader exists in the registry.
 */
/** 
 * @brief Get a shader from the registry by name.
 * @param Name The name of the shader to retrieve.
 * @return A reference to the requested shader, or an empty Ref if no such shader exists.
 */
Ref<Shader> AssetManager::GetShader(const std::string& Name)
	{
		return m_Registry->GetShader(Name);
	}
	/**
 *  @brief Checks if a shader with the given name exists.
 *  
 *  This function checks whether there is an existing shader in the AssetManager's registry that matches the provided name.
 *  
 *  @param Name The name of the shader to check for.
 *  @return True if a shader with the given name exists, false otherwise.
 */
/**
 *  @brief Checks if a shader with the given name exists.
 *  
 *  This function checks whether there is a registered shader in the AssetManager's registry that has the same name as provided.
 *  
 *  @param Name The name of the shader to check for.
 *  @return True if a shader with the given name exists, false otherwise.
 */
bool AssetManager::DoesShaderExist(const std::string& Name)
	{
		return m_Registry->DoesShaderExist(Name);
	}
	/**
 * @brief Loads a scene from the given file path.
 * 
 * This function loads a scene from the specified file path and returns it as a reference to a Scene object. If the scene cannot be loaded, an exception is thrown.
 * 
 * @param Filepath The path of the scene file to load.
 * @return A reference to the loaded Scene object.
 * @throws std::runtime_error if the scene could not be loaded.
 */
/**
 * @brief Loads a scene from the given file path.
 * 
 * This function loads a scene from the specified file path and returns it as a reference to an AssetManager's Scene object.
 * The file path is used to identify the location of the scene data.
 * 
 * @param Filepath The path to the scene file.
 * @return A reference to the loaded scene.
 */
Ref<Scene> AssetManager::LoadScene(const std::filesystem::path& Filepath)
	{
		return m_Registry->LoadScene(Filepath);
	}
	/**
 * @brief This function retrieves the names of all scenes in the AssetManager.
 * 
 * @param OutArray A reference to a std::vector<std::string> where the scene names will be stored.
 * 
 * @return void
 */
/**
 * @brief This function retrieves the names of all scenes in the AssetManager.
 * 
 * @param OutArray A reference to a std::vector<std::string> where the scene names will be stored.
 * 
 * @return void
 */
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
		for (size_t i = 0; i < OutArray.size(); ++i)
		{
			OutArray[i] = Scenes[i]->GetName();
		}

	}
	/**
 * @brief Loads an Aseprite file from the specified path.
 * 
 * This function loads a texture from the provided file path using the Asset Registry's LoadTexture method. The loaded texture is then returned as a Ref<Texture2D> object.
 * 
 * @param Filepath The path to the Aseprite file to load.
 * @return A Ref<Texture2D> object representing the loaded texture, or an empty Ref if the file could not be loaded.
 */
/**
 * @brief Loads an Aseprite file from the specified path.
 * 
 * This function loads a texture from the given file path using the Asset Registry's LoadTexture method. The loaded texture is then returned as a Ref<Texture2D> object.
 * 
 * @param Filepath The path to the Aseprite file to load.
 * @return A Ref<Texture2D> object representing the loaded texture, or an empty Ref if the file could not be loaded.
 */
Ref<Texture2D> AssetManager::LoadAsepriteFile(const std::filesystem::path& Filepath)
	{
		return m_Registry->LoadTexture(Filepath);
	}
	/**
 * @brief Retrieves a texture from the registry using its unique identifier.
 * 
 * This function uses the AssetManager's Registry to get a Texture2D object with the specified UUID. The returned reference can be used for further operations on the texture.
 * 
 * @param ID A const reference to the UUID of the texture to retrieve.
 * @return Ref<Texture2D> A reference to the retrieved Texture2D object. If no such texture exists, an empty reference is returned.
 */
/**
 * @brief Retrieves a texture from the asset manager using its unique identifier.
 * 
 * This function retrieves a texture from the registry of the AssetManager instance by its unique identifier (UUID). The UUID is used to identify and retrieve the specific texture.
 * 
 * @param ID A constant reference to the UUID that represents the texture to be retrieved.
 * @return A Ref<Texture2D> object representing the requested texture. If no such texture exists, an empty Ref<Texture2D> object is returned.
 */
Ref<Texture2D> AssetManager::GetAsepriteTexture(const UUID& ID)
	{
		return m_Registry->GetTexture(ID);
	}
	/**
 * @brief Retrieves a texture from the asset registry using an Aseprite file name.
 * 
 * This function takes in a string representing the name of an Aseprite file, and returns a reference to a Texture2D object. The actual retrieval is done through the AssetManager's internal registry.
 * 
 * @param Name The name of the Aseprite file to retrieve the texture for.
 * @return Reference to the retrieved Texture2D object. If no such texture exists, an empty reference will be returned.
 */
/**
 * @brief Retrieves a texture from the asset registry using an Aseprite file name.
 * 
 * This function takes in an Aseprite file name and returns a reference to a Texture2D object. The actual retrieval of the texture is handled by the AssetManager's internal registry, which this function interacts with through `m_Registry`.
 *
 * @param Name The name of the Aseprite file for which to retrieve the texture.
 * 
 * @return A reference to a Texture2D object representing the desired texture. If no such texture exists in the registry, this function will return an empty Ref<Texture2D>.
 */
Ref<Texture2D> AssetManager::GetAsepriteTexture(const std::string& Name)
	{
		return m_Registry->GetTexture(Name);
	}
	/**
 *  @brief Checks if an Aseprite file is loaded.
 *  
 *  This function checks whether a given Aseprite file has been loaded into the AssetManager's registry.
 *  
 *  @param Filepath The path of the Aseprite file to check for.
 *  @return True if the Aseprite file is loaded, false otherwise.
 */
/** 
 * @brief Checks if an Aseprite file is loaded.
 * 
 * This function checks whether a given Aseprite file has been loaded into the AssetManager's registry.
 * 
 * @param Filepath The path of the Aseprite file to check for.
 * @return True if the Aseprite file is loaded, false otherwise.
 */
bool AssetManager::IsAsepriteFileLoaded(const std::filesystem::path& Filepath)
	{
		return m_Registry->IsTextureLoaded(Filepath);
	}
	/**
 * @brief Loads a font from the specified file path.
 * 
 * This function loads a font from the given file path and returns a reference to it. If the font is already loaded, this function will return a reference to that existing instance instead of loading the font again.
 * 
 * @param Filepath The path to the font file.
 * @return A reference to the loaded font.
 */
/**
 * @brief Loads a font from the specified file path.
 * 
 * This function loads a font from the given file path and returns a reference to it. If the font is already loaded, this will return a reference to that instance instead of loading again.
 * 
 * @param Filepath The path to the font file.
 * @return A reference to the loaded font.
 */
Ref<AGEFont> AssetManager::LoadFont(const std::filesystem::path& Filepath)
	{		
		return m_Registry->LoadFont(Filepath);
	}
	/**
 * @brief Retrieves a font from the asset manager.
 * 
 * This function retrieves a font with the specified unique identifier (UUID). The UUID is used to identify and retrieve the font from the registry.
 * If the font does not exist in the registry, an exception will be thrown.
 * 
 * @param ID The unique identifier of the font to retrieve.
 * @return A reference to the requested font.
 * @throws std::runtime_error if the font with the specified UUID is not found in the registry.
 */
/**
 * @brief Retrieves a font from the asset manager.
 * 
 * This function retrieves a font with the specified unique identifier (UUID). It returns a reference to the font if it exists, or an empty reference otherwise.
 * 
 * @param ID The UUID of the font to retrieve.
 * @return A reference to the font if found, or an empty reference.
 */
Ref<AGEFont> AssetManager::GetFont(const UUID& ID)
	{
		return m_Registry->GetFont(ID);
	}
	/**
 * @brief Get a font from the asset manager.
 * 
 * This function retrieves a font with a specified name from the asset manager's registry. If the font does not exist, it will return an empty reference.
 * 
 * @param Name The name of the font to retrieve.
 * @return A reference to the requested font if found; otherwise, an empty reference.
 */
/**
 * @brief Retrieves a font from the asset manager.
 * 
 * This function is used to get a font with a specific name from the asset manager. The font can then be used for rendering text in the game.
 * 
 * @param Name The name of the font to retrieve.
 * @return A reference to the requested font. If no such font exists, an empty reference will be returned.
 */
Ref<AGEFont> AssetManager::GetFont(const std::string& Name)
	{
		return m_Registry->GetFont(Name);
	}
	/**
 * @brief Checks if a font is loaded.
 * 
 * This function checks whether the specified font file has been loaded into memory.
 * It uses an internal registry to check this information.
 * 
 * @param Filepath The path of the font file to be checked.
 * @return True if the font is loaded, false otherwise.
 */
/**
 * @brief Checks if a font is loaded.
 * 
 * This function checks whether the specified font file is currently loaded in memory.
 * It does this by querying the AssetRegistry object associated with the AssetManager instance.
 * 
 * @param Filepath The path to the font file to check for.
 * @return True if the font is loaded, false otherwise.
 */
bool AssetManager::IsFontLoaded(const std::filesystem::path& Filepath)
	{
		return m_Registry->IsFontLoaded(Filepath);
	}
	/**
 * @brief Loads a soundbank from the specified file path.
 * 
 * This function takes in a const reference to a std::filesystem::path object, which represents the location of the soundbank file on disk. The function then uses this path to load the soundbank into the AssetManager's registry.
 *
 * @param Filepath A constant reference to a std::filesystem::path object representing the location of the soundbank file on disk.
 * 
 * @return void No return value is provided by this function.
 */
/**
 * @brief Loads a soundbank from the specified file path.
 * 
 * This function takes in a const reference to a std::filesystem::path object, which represents the location of the soundbank file on disk. The function then uses this path to load the soundbank into memory using the AssetRegistry's LoadSoundbank method.
 * 
 * @param Filepath A const reference to a std::filesystem::path object representing the location of the soundbank file on disk.
 * @return void No return value.
 */
void AssetManager::LoadSoundbank(const std::filesystem::path& Filepath)
	{
		m_Registry->LoadSoundbank(Filepath);
	}
	/**
 * @brief Checks if a soundbank is loaded.
 * 
 * This function checks whether the specified soundbank file has been loaded into memory.
 * It does this by calling `AssetManager::IsSoundbankLoaded` on the internal registry object, which presumably handles all asset loading and management.
 * 
 * @param Filepath The path to the soundbank file to check for.
 * @return True if the soundbank is loaded, false otherwise.
 */
/**
 * @brief Checks if a soundbank is loaded.
 * 
 * This function checks whether the specified soundbank file has been loaded into memory.
 * It does this by calling `AssetManager::IsSoundbankLoaded` on the internal registry object.
 * 
 * @param Filepath The path to the soundbank file to check for.
 * @return True if the soundbank is loaded, false otherwise.
 */
bool AssetManager::IsSoundbankLoaded(const std::filesystem::path& Filepath)
	{
		return m_Registry->IsSoundbankLoaded(Filepath);
	}
	/**
 * @brief Checks if a scene is loaded.
 * 
 * This function checks whether the given file path corresponds to an already loaded scene in the AssetManager's registry.
 * 
 * @param Filepath The path of the scene to check for.
 * @return True if the scene is loaded, false otherwise.
 */
/** 
 * @brief Checks if a scene is loaded.
 * 
 * This function checks whether the specified file path corresponds to an already loaded scene in the AssetManager's registry.
 * 
 * @param Filepath The path of the scene to be checked.
 * @return True if the scene is loaded, false otherwise.
 */
bool AssetManager::IsSceneLoaded(const std::filesystem::path& Filepath)
	{
		return m_Registry->IsSceneLoaded(Filepath);
	}
	/**
 * @brief Retrieves a scene from the registry using its unique identifier.
 * 
 * This function takes in a constant reference to a UUID, which is used as an identifier for the scene. It then returns a reference to the scene with that specific ID. If no such scene exists, it will return an empty reference.
 * 
 * @param ID The unique identifier of the scene to be retrieved.
 * @return A reference to the scene if found, otherwise an empty reference.
 */
/**
 * @brief Retrieves a scene from the registry using its unique identifier.
 * 
 * This function takes in a constant reference to a UUID (Universally Unique Identifier), which is used as an index to retrieve the corresponding scene from the asset manager's registry. The function returns a `Ref<Scene>`, which represents a smart pointer to a Scene object. If no such scene exists with the given ID, it will return an empty reference.
 * 
 * @param ID A constant reference to the UUID of the scene to be retrieved.
 * @return The requested scene if found, otherwise an empty reference.
 */
Ref<Scene> AssetManager::GetScene(const UUID& ID)
	{
		return m_Registry->GetScene(ID);
	}
	/**
 * @brief Retrieves a scene with the given name.
 * 
 * This function retrieves and returns a reference to a Scene object from the registry using the provided name string.
 * If no such scene exists, it will return an empty Ref<Scene>.
 * 
 * @param Name The name of the scene to retrieve.
 * @return A reference to the requested scene if found; otherwise, an empty Ref<Scene>.
 */
/**
 * @brief Retrieves a scene by its name.
 * 
 * This function retrieves and returns the scene with the given name from the registry. If no such scene exists, it will return an empty reference.
 * 
 * @param Name The name of the scene to retrieve.
 * @return A reference to the requested scene if found; otherwise, an empty reference.
 */
Ref<Scene> AssetManager::GetScene(const std::string& Name)
	{
		return m_Registry->GetScene(Name);
	}
	/**
 * @brief Loads a sound from the specified file path.
 * 
 * This function loads an audio source from the given file path and returns a reference to it. If the sound is already loaded, this function will return a reference to the existing sound.
 * 
 * @param Filepath The path of the sound file to load.
 * @return A reference to the loaded or existing sound.
 */
/**
 * @brief Loads a sound from the given file path.
 * 
 * This function loads an audio source from the specified file path and returns a reference to it. If the sound is already loaded, this will return a reference to that existing sound.
 * 
 * @param Filepath The path of the sound file to load.
 * @return A reference to the loaded audio source.
 */
Ref<AudioSource> AssetManager::LoadSound(const std::filesystem::path& Filepath)
	{
		return m_Registry->LoadSound(Filepath);
	}
	/**
 * @brief Retrieves an audio source with a specific UUID.
 * 
 * This function retrieves and returns the audio source associated with the given UUID from the asset manager's registry.
 * If no such sound exists, it will return an empty reference.
 * 
 * @param ID The UUID of the audio source to retrieve.
 * @return A reference to the retrieved audio source or an empty reference if no such sound exists.
 */
/**
 * @brief Retrieves an audio source with the given unique identifier.
 * 
 * This function retrieves and returns a reference to an AudioSource object from the registry using its unique identifier (UUID). If no such sound exists, it will return an empty Ref<AudioSource>.
 * 
 * @param ID The UUID of the audio source to retrieve.
 * @return A reference to the requested audio source if found; otherwise, an empty Ref<AudioSource>.
 */
Ref<AudioSource> AssetManager::GetSound(const UUID& ID)
	{
		return m_Registry->GetSound(ID);
	}
	/**
 * @brief Retrieves an audio source with the given name.
 * 
 * This function retrieves and returns a reference to an AudioSource object from the registry using the provided name. If no such sound exists, it will return an empty reference.
 * 
 * @param Name The name of the sound to retrieve.
 * @return A reference to the audio source with the given name, or an empty reference if no such sound exists.
 */
/**
 * @brief Retrieves an audio source from the registry by name.
 * 
 * This function retrieves a reference to an AudioSource object stored in the AssetManager's Registry with the given Name.
 * The returned Reference can be used to access and manipulate the sound data associated with this name.
 * 
 * @param[in] Name - A string representing the unique identifier of the audio source.
 * @return Ref<AudioSource> - A reference to an AudioSource object in the AssetManager's Registry.
 */
Ref<AudioSource> AssetManager::GetSound(const std::string& Name)
	{
		return m_Registry->GetSound(Name);
	}
	/**
 * @brief Checks if a sound is loaded.
 * 
 * This function checks whether the specified sound file is currently loaded in memory.
 * It does this by using an AssetRegistry object to check its internal state.
 * 
 * @param Filepath The path of the sound file to be checked.
 * @return True if the sound is loaded, false otherwise.
 */
/** 
 * @brief Checks if a sound is loaded.
 * 
 * This function checks whether the specified sound file is currently loaded in memory.
 * It uses an internal registry to keep track of all loaded sounds, and returns true if the given filepath corresponds to a known sound that has been loaded.
 * If the sound is not loaded or there was an error during the check, it will return false.
 * 
 * @param Filepath The path to the sound file to be checked.
 * @return True if the sound is loaded, false otherwise.
 */
bool AssetManager::IsSoundLoaded(const std::filesystem::path& Filepath)
	{
		return m_Registry->IsSoundLoaded(Filepath);
	}

}