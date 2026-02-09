#include "AGEpch.hpp"
#include "Platform/OpenGL/Public/OpenGLShader.h"
#include "glm/gtc/type_ptr.hpp"
#include <glad/glad.h>
#include "Debug/Public/Instrumentor.h"
//#include <GLFW/glfw3.h>

namespace AGE
{
	static GLenum ShaderTypeFromString(const std::string& Type)
	{
		if (Type == "Vertex" || Type == "vertex")
		{
			return GL_VERTEX_SHADER;
		}

		if (Type == "Fragment" || Type == "fragment" || Type == "pixel" || Type == "Pixel")
		{
			return GL_FRAGMENT_SHADER;
		}

		if (Type == "Geometry" || Type == "geometry" || Type == "Geo" || Type == "geo")
		{
			return GL_GEOMETRY_SHADER;
		}

		return GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR;
	}

	OpenGLShader::OpenGLShader(const std::string& FilePath)
	{
		AGE_PROFILE_FUNCTION();
		std::string ShaderSource  = ReadFile(FilePath);
		std::unordered_map<GLenum, std::string> Pp = PreProcess(ShaderSource);
		Compile(Pp);
		
		// Assets/Shaders/Something.vsfs

		auto LastSlash = FilePath.find_last_of("/\\");
		LastSlash = LastSlash == std::string::npos ? 0 : LastSlash + 1;
		auto LastDot = FilePath.rfind('.');
		auto Count = LastDot == std::string::npos ? FilePath.size() - LastSlash : LastDot - LastSlash;
		m_ShaderName = FilePath.substr(LastSlash, Count);
	}

	OpenGLShader::OpenGLShader(const std::string& VertexSrcPath, const std::string& FragmentSrcPath)
	{
		AGE_PROFILE_FUNCTION();
		std::unordered_map<GLenum, std::string> Sources;
		Sources[GL_VERTEX_SHADER] = ReadFile(VertexSrcPath);
		Sources[GL_FRAGMENT_SHADER] = ReadFile(FragmentSrcPath);
		Compile(Sources);

		// Assets/Shaders/(Vertex/Fragment)/Something.(vs/fs)
		auto LastSlash = VertexSrcPath.find_last_of("/\\");
		LastSlash = LastSlash == std::string::npos ? 0 : LastSlash + 1;
		auto LastDot = VertexSrcPath.rfind('.');
		auto Count = LastDot == std::string::npos ? VertexSrcPath.size() - LastSlash : LastDot - LastSlash;
		m_ShaderName = VertexSrcPath.substr(LastSlash, Count);
	
	}
	OpenGLShader::OpenGLShader(const std::string& Name, const std::string& VertexSrc, const std::string& FragmentSrc)
		:m_ShaderName(Name)
	{
		AGE_PROFILE_FUNCTION();
		std::unordered_map<GLenum, std::string> Sources;
		Sources[GL_VERTEX_SHADER] = VertexSrc;
		Sources[GL_FRAGMENT_SHADER] = FragmentSrc;
		Compile(Sources);
	}

	OpenGLShader::~OpenGLShader()
	{
		AGE_PROFILE_FUNCTION();
		glDeleteProgram(m_RendererID);
	}
	void OpenGLShader::Bind() const
	{
		AGE_PROFILE_FUNCTION();
		glUseProgram(m_RendererID);
		//CoreLogger::Info("{0}", glGetError());

	}
	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}
	void OpenGLShader::SetFloat(const char* Name, float Values) const
	{
		AGE_PROFILE_FUNCTION();
		UploadFloat(Name, Values);
	}
	void OpenGLShader::SetFloat2(const char* Name, const Vector2& Values) const
	{
		AGE_PROFILE_FUNCTION();
		UploadFloat2(Name, Values);
	}
	void OpenGLShader::SetFloat3(const char* Name, const Vector3& Values) const
	{
		AGE_PROFILE_FUNCTION();
		UploadFloat3(Name, Values);
	}
	void OpenGLShader::SetFloat4(const char* Name, const Vector4 Value) const
	{
		AGE_PROFILE_FUNCTION();
		UploadFloat4(Name, Value);
	}
	void OpenGLShader::SetMat3(const char* Name, const Matrix3D& Matrix) const
	{
		AGE_PROFILE_FUNCTION();
		UploadMat3(Name, Matrix);
	}
	void OpenGLShader::SetMat4(const char* Name, const Matrix4D Matrix) const
	{
		AGE_PROFILE_FUNCTION();
		UploadMat4(Name, Matrix);
	}
	void OpenGLShader::SetInt(const char* Name, const int Texture, const int* TexturePtr, const int Count) const
	{
		AGE_PROFILE_FUNCTION();
		UploadInt(Name, Texture, TexturePtr, Count);
	}
	void OpenGLShader::UploadFloat(const char* Name, float Values) const
	{
		glUniform1f(glGetUniformLocation(m_RendererID, Name), Values);
	}
	void OpenGLShader::UploadFloat2(const char* Name, const Vector2& Values) const
	{
		glUniform2f(glGetUniformLocation(m_RendererID, Name), Values[0], Values[1]);
	}
	void OpenGLShader::UploadFloat3(const char* Name, const Vector3& Values) const
	{
		glUniform3f(glGetUniformLocation(m_RendererID, Name), Values[0], Values[1], Values[2]);
	}
	void OpenGLShader::UploadFloat4(const char* Name, const Vector4& Values) const
	{
		glUniform4f(glGetUniformLocation(m_RendererID, Name), Values[0], Values[1], Values[2], Values[3]);
		
	}
	void OpenGLShader::UploadMat3(const char* Name, const Matrix3D& Matrix) const
	{
		glUniformMatrix3fv(glGetUniformLocation(m_RendererID, Name), 1, GL_FALSE, glm::value_ptr(Matrix.ToGLM()));
		
	}
	void OpenGLShader::UploadMat4(const char* Name, const Matrix4D& Matrix) const
	{
		//Figure out why this is taking 15mss
		uint32_t location = 0;
		{
			{
				AGE_PROFILE_SCOPE("glGetUniformLocation -> OpenGLShader::UploadMat4");
				location = glGetUniformLocation(m_RendererID, Name); // <---- why does this take 15ms???????????
			}


			{
				AGE_PROFILE_SCOPE("glUniformMatrix4fv -> OpenGLShader::UploadMat4");
				glUniformMatrix4fv(location, 1, GL_FALSE, &Matrix(0,0));
			}
			
		}
	}

	void OpenGLShader::UploadInt(const char* Name, const int Texture, const int* TexturePtr, const int Count) const
	{
		if (TexturePtr)
		{
			glUniform1iv(glGetUniformLocation(m_RendererID, Name), Count, TexturePtr);

		}
		glUniform1i(glGetUniformLocation(m_RendererID, Name),Texture);
	}

	std::string OpenGLShader::ReadFile(const std::string FilePath)
	{
		AGE_PROFILE_FUNCTION();
		std::string Result;
		std::ifstream In(FilePath, std::ios::in | std::ios::binary);
		if (In)
		{
			In.seekg(0, std::ios::end);
			Result.resize(In.tellg());
			In.seekg(0, std::ios::beg);
			In.read(&Result[0], Result.size());
			In.close();
		}
		else
		{
			CoreLogger::Error("Could Not Open File '{0}'", FilePath);
		}
		return Result;
		

	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& Source)
	{
		AGE_PROFILE_FUNCTION();
		std::unordered_map<GLenum, std::string> ShaderSources;

		const char* TypeToken = "#type";
		size_t TypeTokenLength = strlen(TypeToken);
		size_t Pos = Source.find(TypeToken, 0);
		while (Pos != std::string::npos)
		{
			size_t EOL = Source.find_first_of("\r\n", Pos);
			CoreLogger::Assert(EOL != std::string::npos, "Syntax Error");
			size_t begin = Pos + TypeTokenLength + 1;
			std::string Type = Source.substr(begin, EOL - begin);
			CoreLogger::Assert(ShaderTypeFromString(Type) , "Invalid Shader Type Specifier");

			size_t NextLinePos = Source.find_first_not_of("\r\n", EOL);
			Pos = Source.find(TypeToken, NextLinePos);
			ShaderSources[ShaderTypeFromString(Type)] = Source.substr(NextLinePos, Pos - (NextLinePos == std::string::npos ? Source.size() -1 : NextLinePos));
		}

		return ShaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& ShaderSources)
	{
		AGE_PROFILE_FUNCTION();
		GLuint program = glCreateProgram();
		CoreLogger::Assert(ShaderSources.size() <= 4, "Using Too Many Shaders! Only 4 Shaders Supported");
		std::array<GLenum,4> GLShaderIDs;

		int GlShaderIDIndex = 0;
		for (auto& KV : ShaderSources)
		{
			GLenum Type = KV.first;
			const std::string& Source = KV.second;
			GLuint Shader = glCreateShader(Type);
			const GLchar* sourceCStr = Source.c_str();
			glShaderSource(Shader, 1, &sourceCStr, 0);


			glCompileShader(Shader);

			GLint isCompiled = 0;
			glGetShaderiv(Shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &maxLength);
				

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(Shader, maxLength, &maxLength, &infoLog[0]);


				glDeleteShader(Shader);


				CoreLogger::Error("Shader Error: {0}", infoLog.data());
				CoreLogger::Assert(false, "Shader Compilation Failure!");

				break;
			}
			glAttachShader(program, Shader);
			GLShaderIDs[GlShaderIDIndex++] = Shader;
		}			

			// Vertex and fragment shaders are successfully compiled.
			// Now time to link them together into a program.
			// Get a program object.

			m_RendererID = program;

			// Link our program
			glLinkProgram(program);
			
			// Note the different functions here: glGetProgram* instead of glGetShader*.
			GLint isLinked = 0;
			glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);

			if (isLinked == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
				
				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
				
				// We don't need the program anymore.
				glDeleteProgram(program);
				
				for (auto ID : GLShaderIDs)
				{


					glDeleteShader(ID);

					CoreLogger::Error("Shader Link Error: {0}", infoLog.data());

					CoreLogger::Assert(false, "Shader Link Failure!");

				}
			}

			// Always detach shaders after a successful link.
			for (auto ID : GLShaderIDs)
			{

				glDetachShader(program, ID);

				CoreLogger::Trace("{0}", glGetError());
			}

			//m_RendererID = program;
		
		
	}

}