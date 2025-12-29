#include "AGEpch.hpp"
#include "Render/Public/Shader.h"
#include "Render/Public/Renderer.h"
#include "Platform/OpenGL/Public/OpenGLShader.h"

#include <glad/glad.h>

namespace AGE
{

	Ref<Shader> Shader::Create(const std::string& VertexSrcPath, const std::string& FragmentSrcPath)
	{
		switch (Renderer::GetAPI())
		{
			case 0:
			{
				AGE_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
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
				AGE_CORE_ASSERT(false, "Unknown Renderer API!");
				return nullptr;
				break;
			}
		}
		AGE_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& FilePath)
	{
		switch (Renderer::GetAPI())
		{
		case 0:
		{
			AGE_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
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
			AGE_CORE_ASSERT(false, "Unknown Renderer API!");
			return nullptr;
			break;
		}
		}
		AGE_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& Name, const std::string& VertexSrc, const std::string& FragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case 0:
		{
			AGE_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
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
			AGE_CORE_ASSERT(false, "Unknown Renderer API!");
			return nullptr;
			break;
		}
		}
		AGE_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& Name, const Ref<Shader>& Shader)
	{
		if (Exists(Name))
		{
			CoreLogger::Warn("Shader Already Exists! \n\tName: {0}", Name.c_str());
			return;
		}
		m_Shaders[Name] = Shader;
	}
	void ShaderLibrary::Add(Ref<Shader>& Shader)
	{
		std::string Name = Shader->GetShaderName();
		Add(Name, Shader);

	}

	//const int Name refers to the type of shader it is, if it is vertex then Name should be 1, if anything other than vertex then name should be anything other than 1
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

	Ref<Shader> ShaderLibrary::Load(const std::string& FilePath)
	{
		auto Shader = Shader::Create(FilePath);
		Add(Shader);
		return Shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& FilePath1, const std::string& FilePath2)
	{
		auto Shader = Shader::Create(FilePath1, FilePath2);
		Add(Shader);
		return Shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& Name)
	{
		AGE_CORE_ASSERT(Exists(Name), "Shader Not Found!");
		return m_Shaders[Name];
	}

	bool ShaderLibrary::Exists(const std::string& Name)
	{
		return m_Shaders.find(Name) != m_Shaders.end();
	}

}
