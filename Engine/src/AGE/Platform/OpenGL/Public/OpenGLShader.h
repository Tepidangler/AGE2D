#pragma once
#include "Render/Public/Shader.h"
#include <glm/glm.hpp>

//REMOVE
typedef unsigned int GLenum;

namespace AGE
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& FilePath);
		OpenGLShader(const std::string& VertexSrcPath, const std::string& FragmentSrcPath);
		OpenGLShader(const std::string& Name, const std::string& VertexSrc, const std::string& FragmentSrc);

		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetFloat(const char* Name, float Values) const override;
		virtual void SetFloat2(const char* Name, const Vector2& Values) const override;
		virtual void SetFloat3(const char* Name, const Vector3& Values) const override;
		virtual void SetFloat4(const char* Name, const Vector4 Value) const override;
		virtual void SetMat3(const char* Name, const Matrix3D& Matrix) const override;
		virtual void SetMat4(const char* Name, const Matrix4D Matrix) const override;
		virtual void SetInt(const char* Name, const int Texture = 0, const int* TexturePtr = nullptr, const int Count = 2) const override;

		virtual const std::string& GetShaderName() const override { return m_ShaderName; }

		void UploadFloat(const char* Name, float Values) const;
		void UploadFloat2(const char* Name, const Vector2& Values) const;
		void UploadFloat3(const char* Name, const Vector3& Values) const;
		void UploadFloat4(const char* Name, const Vector4& Values) const;
		void UploadMat3(const char* Name, const Matrix3D& Matrix) const;
		void UploadMat4(const char* Name, const Matrix4D& Matrix) const;
		void UploadInt(const char* Name, const int Texture = 0, const int* TexturePtr = nullptr, const int Count = 2) const;

		std::string ReadFile(const std::string FilePath);

		std::unordered_map < GLenum, std::string> PreProcess(const std::string& Source);

		void Compile(const std::unordered_map<GLenum, std::string>& ShaderSources);

		inline virtual uint32_t GetRendererID() const override { return m_RendererID; }

		
	private:
		uint32_t m_RendererID;
		std::string m_ShaderName;
	};
}