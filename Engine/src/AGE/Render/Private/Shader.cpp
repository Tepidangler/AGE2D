#include "AGEpch.hpp"
#include "Render/Public/Shader.h"
#include "Render/Public/Renderer.h"
#include "Platform/OpenGL/Public/OpenGLShader.h"

#include <glad/glad.h>

namespace AGE
{

	/**
 * @brief Creates a new shader object based on the current renderer's API.
 * 
 * The function checks the current renderer's API and creates an appropriate shader object accordingly. If no supported API is detected, it asserts false and returns nullptr.
 * 
 * @param VertexSrcPath A string representing the path to the vertex shader source code file.
 * @param FragmentSrcPath A string representing the path to the fragment shader source code file.
 * 
 * @return A reference to a Shader object, which can be either an OpenGLShader or another type of shader depending on the current renderer's API. If no supported API is detected, it returns nullptr.
 */
Ref<Shader> Shader::Create(const std::string& VertexSrcPath, const std::string& FragmentSrcPath)
	{
		switch (Renderer::GetAPI())
		{
			case 0:
			{
				CoreLogger::Assert(false, "RendererAPI::API::None is currently not supported!");
				return nullptr;
				break;
			}
			case 1:
			{
				return CreateScope<OpenGLShader>(VertexSrcPath, FragmentSrcPath);
				break;
			}
			default:
			{
				CoreLogger::Assert(false, "Unknown Renderer API!");
				return nullptr;
				break;
			}
		}
		CoreLogger::Assert(false, "Unknown Renderer API!");
		return nullptr;
	}

	/**
 * @brief Creates a shader object based on the current renderer API.
 * 
 * @param FilePath The path to the shader file.
 * 
 * @return A smart pointer (Ref<Shader>) pointing to the newly created Shader object, or nullptr if an unsupported RendererAPI enum value was passed.
 */
Ref<Shader> Shader::Create(const std::string& FilePath)
	{
		switch (Renderer::GetAPI())
		{
		case 0:
		{
			CoreLogger::Assert(false, "RendererAPI::API::None is currently not supported!");
			return nullptr;
			break;
		}
		case 1:
		{
			return CreateScope<OpenGLShader>(FilePath);
			break;
		}
		default:
		{
			CoreLogger::Assert(false, "Unknown Renderer API!");
			return nullptr;
			break;
		}
		}
		CoreLogger::Assert(false, "Unknown Renderer API!");
		return nullptr;
	}

	/**
 * @brief Creates a new shader object.
 * 
 * This function creates and returns a reference to a Shader object based on the current RendererAPI in use. It supports OpenGL as of now, but more APIs can be added easily by extending this switch-case structure.
 * 
 * @param Name The name of the shader program.
 * @param VertexSrc A string containing the source code for the vertex shader.
 * @param FragmentSrc A string containing the source code for the fragment shader.
 * 
 * @return A reference to a Shader object, or nullptr if an unsupported RendererAPI is in use.
 */
Ref<Shader> Shader::Create(const std::string& Name, const std::string& VertexSrc, const std::string& FragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case 0:
		{
			CoreLogger::Assert(false, "RendererAPI::API::None is currently not supported!");
			return nullptr;
			break;
		}
		case 1:
		{
			return CreateScope<OpenGLShader>(Name, VertexSrc, FragmentSrc);
			break;
		}
		default:
		{
			CoreLogger::Assert(false, "Unknown Renderer API!");
			return nullptr;
			break;
		}
		}
		CoreLogger::Assert(false, "Unknown Renderer API!");
		return nullptr;
	}

	/**
 * @brief Adds a shader to the library with a given name and reference.
 * 
 * This function adds a new shader to the library if it does not already exist. If a shader with the same name exists, a warning is logged and the function returns without adding anything.
 * 
 * @param Name The name of the shader to add.
 * @param Shader A reference to the shader object to be added.
 */
void ShaderLibrary::Add(const std::string& Name, const Ref<Shader>& Shader)
	{
		if (Exists(Name))
		{
			CoreLogger::Warn("Shader Already Exists! \n\tName: {0}", Name.c_str());
			return;
		}
		m_Shaders[Name] = Shader;
	}
	/**
 * @brief Adds a shader to the library.
 *
 * This function takes a reference to a shader object and adds it to the library. The name of the shader is obtained by calling the GetShaderName() method on the Shader object. 
 *
 * @param[in] Shader A reference to the shader object that needs to be added.
 */
void ShaderLibrary::Add(Ref<Shader>& Shader)
	{
		std::string Name = Shader->GetShaderName();
		Add(Name, Shader);

	}

	//const int Name refers to the type of shader it is, if it is vertex then Name should be 1, if anything other than vertex then name should be anything other than 1
	/**
 * @brief Loads a shader into the library. The type of shader is determined by the Name parameter, where 1 represents "Vertex" and any other value represents "Pixel".
 * @param Name An integer representing the type of shader to be loaded.
 * @param Source A string containing the source code for the shader.
 * @return Returns a reference to the newly loaded Shader object.
 */
Ref<Shader> ShaderLibrary::Load(const int Name, const std::string& Source)
	{
		auto Shader = Shader::Create(Source);
		if (Name == 1)
		{
			Add("Vertex", Shader);
		}
		else
		{
			Add("Pixel", Shader);
		}
	
		return Shader;
	}

	/**
 * @brief Loads a shader from the given file path and adds it to the library.
 * @param FilePath The path of the shader file.
 * @return A reference to the loaded shader.
 */
Ref<Shader> ShaderLibrary::Load(const std::string& FilePath)
	{
		auto Shader = Shader::Create(FilePath);
		Add(Shader);
		return Shader;
	}

	/**
 * @brief Loads a shader from two file paths and adds it to the library.
 * 
 * The function creates a new shader object using `Shader::Create` with the provided file paths, then adds this shader to the library using `Add` method. Finally, it returns the created shader.
 * 
 * @param FilePath1 The path of the first shader file.
 * @param FilePath2 The path of the second shader file.
 * 
 * @return A reference to the loaded shader object.
 */
Ref<Shader> ShaderLibrary::Load(const std::string& FilePath1, const std::string& FilePath2)
	{
		auto Shader = Shader::Create(FilePath1, FilePath2);
		Add(Shader);
		return Shader;
	}

	/**
 * @brief Retrieves a shader from the library by name.
 * @param Name The name of the shader to retrieve.
 * @return A reference to the requested shader, or an empty Ref if no such shader exists in the library.
 */
Ref<Shader> ShaderLibrary::Get(const std::string& Name)
	{
		CoreLogger::Assert(Exists(Name), "Shader Not Found!");
		return m_Shaders[Name];
	}

	/**
 * @brief Checks if a shader with the given name exists in the library.
 *
 * This function checks whether there is an entry for a shader with the specified name in the ShaderLibrary's internal map of shaders. 
 * It returns true if such an entry exists, and false otherwise.
 *
 * @param Name The name of the shader to check for.
 * @return True if a shader with the given name exists, false otherwise.
 */
bool ShaderLibrary::Exists(const std::string& Name)
	{
		return m_Shaders.find(Name) != m_Shaders.end();
	}

}
