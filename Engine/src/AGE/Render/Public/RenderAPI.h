#pragma once
#include "Math/Public/MathStructures.h"
#include "Render/Public/VertexArray.h"

namespace AGE
{


	class RendererAPI
	{
	public: //enum

		enum API //: uint8_t
		{
			None = 0,
			OpenGL = 1,
		};
	public: //functions

		static Scope<RendererAPI> Create();
		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t Width, uint32_t Height) = 0;
		virtual void SetClearColor(const Vector4 Color) = 0;
		virtual void Clear() = 0;
	
		virtual void DrawIndexed(uint32_t IndexCount, uint32_t IndexStart, int VertexStart) = 0;
		virtual void DrawIndexed(const Ref<VertexArray>& VertexArray, uint32_t IndexCount) = 0;
		virtual void DrawLines(const Ref<VertexArray>& VertexArray, uint32_t VertexCount) = 0;
		virtual void DrawStrips(const Ref<VertexArray>& VertexArray, uint32_t IndexCount) = 0;
		virtual void SetLineWidth(float Width) = 0;

		virtual void Submit() = 0;

		virtual void Flush() = 0;

		virtual void Present() = 0;

		static inline API GetAPI() { return s_API; }

		static inline void SetAPI(RendererAPI::API Type) { s_API = Type; }

	private:
		static API s_API;


	};

	namespace Utils
	{
		static std::string ConvertAPIToString()
		{
			switch (RendererAPI::GetAPI())
			{
			case 0:
			{
				return std::string("Headless");
				break;
			}
			case 1:
			{
				return std::string("OpenGL");
				break;
			}
			case 2:
			{
				return std::string("DirectX 11");
				break;
			}
			case 3:
			{
				return std::string("DirectX 12");
				break;
			}
			case 4:
			{
				return std::string("Vulkan");
				break;
			}
			case 5:
			{
				return std::string("Playstation 5 Graphics API");
				break;
			}
			}

			return std::string("UNDEFINED");
		}
	}
}