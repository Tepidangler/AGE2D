#pragma once

#include "Core/Public/Core.h"
#include <string>
#include <glm/glm.hpp>
#include "Math/Public/MathStructures.h"
#include "Math/Public/UtilityFunctions.h"


namespace AGE
{
	class Shader
	{
	public:
		virtual ~Shader() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		
		virtual void SetFloat(const char* Name, float Values) const = 0;
		virtual void SetFloat2(const char* Name, const Vector2& Values) const = 0;
		virtual void SetFloat3(const char* Name, const Vector3& Values) const = 0;
		virtual void SetFloat4(const char* Name, const Vector4 Value) const = 0;
		virtual void SetMat4(const char* Name, const Matrix4D Matrix) const = 0;
		virtual void SetMat3(const char* Name, const Matrix3D& Matrix) const = 0;
		virtual void SetInt(const char* Name, const int Texture = 0, const int* TexturePtr = nullptr, const int Count = 2) const = 0;

		inline virtual uint32_t GetRendererID() const = 0;
		virtual const std::string& GetShaderName() const = 0;

		static Ref<Shader> Create(const std::string& VertexSrcPath, const std::string& FragmentSrcPath);
		static Ref<Shader> Create(const std::string& FilePath);
		static Ref<Shader> Create(const std::string& Name, const std::string& VertexSrc, const std::string& FragmentSrc);

	

	};

	class ShaderLibrary
	{
	public:

		void Add(const std::string& Name, const Ref<Shader>& Shader);
		void Add(Ref<Shader>& Shader);

		Ref<Shader> Load(const std::string& FilePath);
		Ref<Shader> Load(const std::string& FilePath1, const std::string& FilePath2);
		Ref<Shader> Load(const int Name, const std::string& Source);
		Ref<Shader> Get(const std::string& Name);

		bool Exists(const std::string& Name);

		std::unordered_map<std::string, Ref<Shader>> GetLibrary() { return m_Shaders; }

	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}