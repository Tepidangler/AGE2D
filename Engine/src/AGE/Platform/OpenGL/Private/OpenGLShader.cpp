#include "AGEpch.hpp"
#include "Platform/OpenGL/Public/OpenGLShader.h"
#include "glm/gtc/type_ptr.hpp"
#include <glad/glad.h>
#include "Debug/Public/Instrumentor.h"
//#include <GLFW/glfw3.h>

namespace AGE
{
	/**
 * @brief Converts a string to its corresponding OpenGL shader type.
 * 
 * This function takes in a string and converts it into the equivalent GLenum value representing an OpenGL Shader Type. The input can be "Vertex", "vertex", "Fragment", "fragment", "pixel" or "Pixel". For "Geometry", "geometry", "Geo" or "geo". If no match is found, it returns GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR.
 * 
 * @param Type The string to convert into an OpenGL Shader type.
 * @return The corresponding GLenum value for the input string.
 */
/**
 * @brief Converts a string to its corresponding OpenGL shader type.
 * 
 * This function takes in a string and returns the equivalent OpenGL shader type. It supports four types of shaders: vertex, fragment (or pixel), geometry, and others. If the input string does not match any of these, it returns GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR.
 * 
 * @param Type The string to convert. Can be "Vertex", "vertex", "Fragment", "fragment", "pixel", "Pixel", "Geometry", "geometry", "Geo", or "geo".
 * @return GLenum The corresponding OpenGL shader type, or GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR if the input string does not match any of these.
 */
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

	/**
 * Constructor for OpenGLShader class. It takes a file path as input and reads the shader source code from it. The source code is then preprocessed and compiled into separate shaders. 
 * @param FilePath A string representing the file path of the shader source code. This should be in the format "Assets/Shaders/Something.vsfs".
 */
/**
 * @brief Constructs an OpenGLShader object from a file path.
 * 
 * This constructor reads and preprocesses the shader source code, compiles each type of shader, links them together, and extracts the name of the shader from the file path.
 * @param FilePath The path to the shader source code file.
 */
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

	/**
 * @brief Constructor for OpenGLShader class.
 * Initializes an instance by reading shader sources from files specified by their paths, compiling them into a program that can be used in OpenGL rendering, and assigning a name derived from the input paths.
 * 
 * @param VertexSrcPath The path to the vertex shader source file.
 * @param FragmentSrcPath The path to the fragment shader source file.
 */
/**
 * @brief Constructor for OpenGLShader class.
 * 
 * This constructor takes in two strings representing the file paths of vertex and fragment shaders respectively. It reads these files into an unordered map with keys GL_VERTEX_SHADER and GL_FRAGMENT_SHADER, then compiles them using the Compile function. The name of the shader is extracted from the input file path and stored in m_ShaderName.
 * 
 * @param VertexSrcPath File path to vertex shader source code.
 * @param FragmentSrcPath File path to fragment shader source code.
 */
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
	/**
 * @brief Constructs an OpenGLShader object with the given name, vertex source code and fragment source code.
 * 
 * This function initializes an instance of OpenGLShader with a specified name and shader sources for both vertex and fragment stages. The sources are passed as strings to the Compile method which handles the actual compilation process.
 * 
 * @param Name The name of the shader program.
 * @param VertexSrc A string containing the source code for the vertex shader stage.
 * @param FragmentSrc A string containing the source code for the fragment shader stage.
 */
/**
 * @brief Constructs an OpenGLShader object with the given name, vertex source code and fragment source code.
 * 
 * This function initializes an instance of OpenGLShader by setting its shader name to the provided name, and compiling both a vertex and a fragment shader from the provided source codes.
 * The sources are expected to be strings containing GLSL (OpenGL Shading Language) code.
 * 
 * @param Name The name of the shader program.
 * @param VertexSrc A string containing the GLSL code for the vertex shader.
 * @param FragmentSrc A string containing the GLSL code for the fragment shader.
 */
OpenGLShader::OpenGLShader(const std::string& Name, const std::string& VertexSrc, const std::string& FragmentSrc)
		:m_ShaderName(Name)
	{
		AGE_PROFILE_FUNCTION();
		std::unordered_map<GLenum, std::string> Sources;
		Sources[GL_VERTEX_SHADER] = VertexSrc;
		Sources[GL_FRAGMENT_SHADER] = FragmentSrc;
		Compile(Sources);
	}

	/**
 * @brief Destructor for the OpenGLShader class.
 * 
 * This function deletes a shader program from the GPU using glDeleteProgram(). The ID of the shader program to delete is stored in m_RendererID.
 */
/**
 * @brief Destructor for the OpenGLShader class.
 * 
 * This function deletes a shader program from the GPU using glDeleteProgram(). The ID of the shader program to delete is stored in m_RendererID.
 */
OpenGLShader::~OpenGLShader()
	{
		AGE_PROFILE_FUNCTION();
		glDeleteProgram(m_RendererID);
	}
	/** 
 * @brief This function binds the OpenGL shader program.
 * 
 * It uses the `glUseProgram` function to bind the shader program with the given renderer ID. The function does not return any value, so it is a void function.
 */
/** 
 * @brief This function binds the OpenGL shader program.
 * 
 * It uses the glUseProgram function to bind this shader program, setting it as the current active program in the OpenGL context.
 * The m_RendererID member variable is used as an argument for this function call.
 */
void OpenGLShader::Bind() const
	{
		AGE_PROFILE_FUNCTION();
		glUseProgram(m_RendererID);
		//CoreLogger::Info("{0}", glGetError());

	}
	/**
 * @brief This function unbinds the current shader program from use, setting the context to that of the default OpenGL state.
 * 
 * @return void
 */
/**
 * @brief This function unbinds the current shader program from use by binding to 0 (the null program).
 * @return void
 */
void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}
	/**
 * @brief This function sets a single floating-point value with the given name.
 * 
 * @param Name The name of the float variable to set.
 * @param Values The new value for the float variable.
 * 
 * @return None
 */
/** 
 * @brief This function sets a single floating-point value with the given name.
 * @param Name The name of the float variable to set.
 * @param Values The new value for the float variable.
 * @return void
 */
void OpenGLShader::SetFloat(const char* Name, float Values) const
	{
		AGE_PROFILE_FUNCTION();
		UploadFloat(Name, Values);
	}
	/** 
 * @brief This function sets a float vector of two elements with the given name.
 * 
 * @param Name The name of the uniform variable to set.
 * @param Values A Vector2 object containing the values to be set for the uniform variable.
 * 
 * @return void
 */
/**
 * @brief This function sets a float vector of two elements with the given name.
 * 
 * @param Name The name of the uniform variable to set.
 * @param Values A Vector2 object containing the values to be set for the uniform variable.
 * 
 * @return void
 */
void OpenGLShader::SetFloat2(const char* Name, const Vector2& Values) const
	{
		AGE_PROFILE_FUNCTION();
		UploadFloat2(Name, Values);
	}
	/**
 * @brief This function sets a float vector in the OpenGLShader.
 * 
 * @param Name The name of the uniform variable to set.
 * @param Values The Vector3 value to be uploaded.
 * 
 * @return void
 */
/** 
 * @brief This function sets a float vector of length 3.
 * 
 * @param Name The name of the uniform variable to set.
 * @param Values The Vector3 object containing the new values for the uniform variable.
 * 
 * @return void
 */
void OpenGLShader::SetFloat3(const char* Name, const Vector3& Values) const
	{
		AGE_PROFILE_FUNCTION();
		UploadFloat3(Name, Values);
	}
	/**
 * @brief This function sets a float vector of size 4 by name.
 * 
 * @param Name The name of the uniform variable to set.
 * @param Value The Vector4 value to be set.
 * 
 * @return void
 */
/** 
 * @brief This function sets a float vector of size 4 in the OpenGLShader object.
 * 
 * @param Name The name of the uniform variable to set.
 * @param Value The Vector4 value to be set for the uniform variable.
 * 
 * @return void
 */
void OpenGLShader::SetFloat4(const char* Name, const Vector4 Value) const
	{
		AGE_PROFILE_FUNCTION();
		UploadFloat4(Name, Value);
	}
	/** 
 * @brief This function sets a 3x3 matrix with the given name.
 * 
 * @param Name The name of the uniform variable to set in the shader program.
 * @param Matrix The 3x3 matrix to be uploaded.
 * 
 * @return void
 */
/** 
 * @brief This function sets a 3x3 matrix with the given name and value.
 * 
 * @param Name The name of the uniform variable to set in the shader program.
 * @param Matrix The 3x3 matrix to be uploaded.
 * 
 * @return void
 */
void OpenGLShader::SetMat3(const char* Name, const Matrix3D& Matrix) const
	{
		AGE_PROFILE_FUNCTION();
		UploadMat3(Name, Matrix);
	}
	/**
 * @brief Set a 4x4 matrix uniform in the shader.
 *
 * This function sets a 4x4 matrix uniform with the given name and value in the OpenGLShader object. The matrix is uploaded to the GPU for use by the shaders.
 *
 * @param Name The name of the uniform variable to set.
 * @param Matrix The 4x4 matrix to upload.
 *
 * @return void
 */
/** 
 * @brief This function sets a matrix of type Matrix4D with the given name.
 * @param Name The name of the uniform variable to set in the shader program.
 * @param Matrix The Matrix4D object that will be uploaded to the GPU.
 * @return void
 */
void OpenGLShader::SetMat4(const char* Name, const Matrix4D Matrix) const
	{
		AGE_PROFILE_FUNCTION();
		UploadMat4(Name, Matrix);
	}
	/**
 * @brief This function sets an integer uniform in the OpenGLShader.
 * 
 * @param Name The name of the uniform to set.
 * @param Texture The texture unit number to bind to the uniform.
 * @param TexturePtr Pointer to array of texture units to bind to the uniform.
 * @param Count Number of elements in the TexturePtr array.
 * 
 * @return void
 */
/**
 * @brief This function sets an integer uniform in the OpenGL shader.
 * 
 * @param Name The name of the uniform variable to set.
 * @param Texture The texture unit number to bind.
 * @param TexturePtr Pointer to the array of texture units to bind.
 * @param Count Number of elements in the TexturePtr array.
 */
void OpenGLShader::SetInt(const char* Name, const int Texture, const int* TexturePtr, const int Count) const
	{
		AGE_PROFILE_FUNCTION();
		UploadInt(Name, Texture, TexturePtr, Count);
	}
	/**
 * @brief Uploads a single floating-point value to the GPU.
 * 
 * This function uploads a single float value to the GPU using OpenGL's glUniform1f function. It does this by first obtaining the location of the uniform variable in the shader program with glGetUniformLocation, and then passing that location along with the float value to be uploaded to the GPU.
 * 
 * @param Name The name of the uniform variable in the shader program.
 * @param Values The single floating-point value to upload to the GPU.
 * 
 * @return void
 */
/**
 * @brief Uploads a single floating-point value to the GPU.
 * 
 * This function uploads a single float value to the GPU using OpenGL's glUniform1f function. The location of the uniform variable is determined by calling glGetUniformLocation with the shader program and the name of the uniform variable as arguments.
 *
 * @param Name A string representing the name of the uniform variable in the shader program.
 * @param Values The float value to be uploaded to the GPU.
 */
void OpenGLShader::UploadFloat(const char* Name, float Values) const
	{
		glUniform1f(glGetUniformLocation(m_RendererID, Name), Values);
	}
	/**
 * @brief Uploads a 2D float vector to the GPU.
 * 
 * This function uploads a 2D float vector to the GPU using OpenGL's glUniform2f and glGetUniformLocation functions. The uniform location is determined by the provided name, which should correspond to an existing uniform in the shader program.
 *
 * @param Name A string representing the name of the uniform variable in the shader program.
 * @param Values A Vector2 object containing the 2D float values to be uploaded.
 */
/**
 * @brief Uploads a 2-component float vector to the GPU.
 *
 * This function uploads a two component floating point vector to the GPU at the location specified by Name. The values of the vector are passed as separate arguments, Values[0] and Values[1].
 *
 * @param Name The name of the uniform variable in the shader program.
 * @param Values A 2-component float vector containing the new value for the uniform variable.
 */
void OpenGLShader::UploadFloat2(const char* Name, const Vector2& Values) const
	{
		glUniform2f(glGetUniformLocation(m_RendererID, Name), Values[0], Values[1]);
	}
	/**
 * @brief Uploads a 3-component float vector to the GPU.
 * 
 * This function uploads a three component floating point vector to the GPU, which can be used for various shader operations such as light positioning or material properties. The uniform location is obtained using the provided name and uploaded to the GPU using `glUniform3f`.
 *
 * @param Name A string representing the name of the uniform variable in the shader program.
 * @param Values A 3-component floating point vector containing the values to be uploaded.
 */
/**
 * @brief Uploads a 3-component floating point vector to the GPU.
 *
 * This function uploads a three component floating point vector to the GPU, which can be used for various shader operations such as light positioning or material properties.
 *
 * @param Name The name of the uniform variable in the shader program.
 * @param Values A 3-component floating point vector containing the values to upload.
 */
void OpenGLShader::UploadFloat3(const char* Name, const Vector3& Values) const
	{
		glUniform3f(glGetUniformLocation(m_RendererID, Name), Values[0], Values[1], Values[2]);
	}
	/**
 * @brief Uploads a 4-component vector to the GPU.
 * 
 * This function uploads a 4-component vector (represented by a Vector4 object) to the GPU, using OpenGL's glUniform4f function. The location of the uniform variable on the GPU is determined by the provided name string.
 *
 * @param Name A pointer to a null-terminated string representing the name of the uniform variable in the shader program.
 * @param Values A constant reference to a Vector4 object containing the 4 components of the vector to be uploaded.
 */
/**
 * @brief Uploads a 4-component vector to the GPU as a uniform variable.
 *
 * This function uploads a 4-component vector (x, y, z, w) to the GPU as a uniform variable with the specified name. The location of this uniform is obtained using `glGetUniformLocation`.
 *
 * @param Name A string representing the name of the uniform variable on the GPU.
 * @param Values A 4-component vector containing the values to be uploaded.
 */
void OpenGLShader::UploadFloat4(const char* Name, const Vector4& Values) const
	{
		glUniform4f(glGetUniformLocation(m_RendererID, Name), Values[0], Values[1], Values[2], Values[3]);
		
	}
	/**
 * @brief Uploads a 3x3 matrix to the GPU shader program.
 *
 * This function uploads a 3x3 matrix to the GPU shader program using OpenGL's glUniformMatrix3fv function. The location of the uniform variable in the shader is determined by calling glGetUniformLocation with the name of the uniform and the ID of the shader program.
 *
 * @param Name A string representing the name of the uniform variable in the shader program.
 * @param Matrix A 3x3 matrix to be uploaded to the GPU.
 */
/**
 * @brief Uploads a 3x3 matrix to the GPU shader program.
 *
 * This function uploads a 3x3 matrix to the GPU shader program using OpenGL's glUniformMatrix3fv function. The location of the uniform variable in the shader program is obtained by calling glGetUniformLocation with the name of the uniform and the ID of the shader program.
 *
 * @param Name A string representing the name of the uniform variable in the shader program.
 * @param Matrix A 3x3 matrix to be uploaded to the GPU.
 */
void OpenGLShader::UploadMat3(const char* Name, const Matrix3D& Matrix) const
	{
		glUniformMatrix3fv(glGetUniformLocation(m_RendererID, Name), 1, GL_FALSE, glm::value_ptr(Matrix.ToGLM()));
		
	}
	/**
 * @brief Uploads a Matrix4D to the OpenGL shader.
 *
 * This function uploads a Matrix4D to an OpenGL shader by first getting the location of the uniform variable in the shader using glGetUniformLocation, then passing the matrix data to this location with glUniformMatrix4fv. 
 *
 * @param Name The name of the uniform variable in the shader.
 * @param Matrix The Matrix4D to be uploaded.
 */
/**
 * @brief Uploads a Matrix4D to the OpenGL shader.
 *
 * This function uploads a Matrix4D to an OpenGL shader by first getting the uniform location of the variable in the shader, 
 * and then using glUniformMatrix4fv to set the value of that variable. The matrix is uploaded as a raw float array.
 *
 * @param Name The name of the Matrix4D variable in the shader.
 * @param Matrix The Matrix4D to be uploaded.
 */
void OpenGLShader::UploadMat4(const char* Name, const Matrix4D& Matrix) const
	{
		//Figure out why this is taking 15mss
		int location = 0;
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

	/**
 * @brief Uploads an integer uniform to the OpenGL shader.
 * 
 * This function uploads a single integer or an array of integers as a uniform variable in the OpenGL shader program. It first checks if the `TexturePtr` parameter is not null, and if so, it uses `glUniform1iv()` to set the uniform value using the pointer to the data. If `TexturePtr` is null, it simply sets the single integer uniform with `glUniform1i()`.
 * 
 * @param Name The name of the uniform variable in the shader program.
 * @param Texture A single integer value to be uploaded as a uniform.
 * @param TexturePtr Pointer to an array of integers to be uploaded as uniforms. If this is null, `Texture` will be used instead.
 * @param Count The number of elements in the `TexturePtr` array if it's not null. This parameter is ignored if `TexturePtr` is null.
 */
/**
 * @brief Uploads an integer uniform to the OpenGL shader.
 * 
 * This function uploads a single integer or an array of integers to the specified uniform variable in the OpenGL shader.
 * The location of the uniform is determined by its name, which must be valid and existent within the shader program.
 * If TexturePtr is not null, it will use glUniform1iv to upload Count number of integer values from TexturePtr array. 
 * Otherwise, it will simply upload a single integer value using glUniform1i.
 * @param Name The name of the uniform variable in the shader program.
 * @param Texture A single integer value to be uploaded.
 * @param TexturePtr Pointer to an array of integers to be uploaded. If this is null, only a single integer will be uploaded.
 * @param Count Number of elements in the TexturePtr array if it's not null. This parameter has no effect if TexturePtr is null.
 */
void OpenGLShader::UploadInt(const char* Name, const int Texture, const int* TexturePtr, const int Count) const
	{
		if (TexturePtr)
		{
			glUniform1iv(glGetUniformLocation(m_RendererID, Name), Count, TexturePtr);

		}
		glUniform1i(glGetUniformLocation(m_RendererID, Name),Texture);
	}

	/**
 * @brief Reads a file from the disk and returns its content as a string.
 *
 * This function opens a file at the given path, reads its contents into a string, 
 * and then closes the file. If the file cannot be opened for any reason (e.g., it does not exist), 
 * an error message is logged to the console.
 *
 * @param FilePath The path of the file to read.
 * @return A string containing the contents of the file, or "Unknown" if the file could not be opened.
 */
/**
 * @brief Reads a file from the disk and returns its content as a string.
 * 
 * This function opens a file at the given path, reads its entire contents into a string, and then closes the file. If the file cannot be opened for any reason (e.g., it does not exist), an error message is logged to the console.
 * @param FilePath The path of the file to read from.
 * @return A string containing the content of the file. If the file could not be opened, this will be an empty string.
 */
std::string OpenGLShader::ReadFile(const std::string FilePath)
	{
		AGE_PROFILE_FUNCTION();
		std::string Result;
		std::ifstream In(FilePath, std::ios::in | std::ios::binary);
		if (In)
		{
			In.seekg(0, std::ios::end);
			Result.resize((size_t)In.tellg());
			In.seekg(0, std::ios::beg);
			In.read(&Result[0], (std::streamsize)Result.size());
			In.close();
		}
		else
		{
			CoreLogger::Error("Could Not Open File '{0}'", FilePath);
		}
		return Result;
		

	}

	/**
 * Preprocesses an OpenGL shader source code, separating it into different sections based on type (vertex, fragment, etc.).
 * The function takes in a string of source code and returns an unordered map where each key is a GLenum representing the shader type 
 * and each value is the corresponding shader source code. It uses a specific token (#type) to identify different sections within the source code.
 */
/**
 * @brief Preprocesses OpenGL shader source code to separate different types of shaders based on specific token.
 * 
 * @param Source Original source code of the shader program.
 * @return Unordered map where keys are GLenum representing shader types and values are strings containing corresponding shader sources.
 */
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

	/**
 * Compiles a collection of OpenGL shaders into a single program.
 * The function takes in a map where each key-value pair represents the type and source code of a shader.
 * If any compilation errors occur, they are logged and the function returns without further action.
 * @param ShaderSources A dictionary mapping GLenum (representing shader type) to string (source code). Maximum 4 shaders supported.
 */

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
				

				std::vector<GLchar> infoLog((size_t)maxLength);
				glGetShaderInfoLog(Shader, maxLength, &maxLength, &infoLog[0]);


				glDeleteShader(Shader);


				CoreLogger::Error("Shader Error: {0}", infoLog.data());
				CoreLogger::Assert(false, "Shader Compilation Failure!");

				break;
			}
			glAttachShader(program, Shader);
			GLShaderIDs[(size_t)GlShaderIDIndex++] = Shader;
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
				std::vector<GLchar> infoLog((size_t)maxLength);
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