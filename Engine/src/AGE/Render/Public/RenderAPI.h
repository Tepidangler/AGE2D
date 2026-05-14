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
			Headless = 0,
			OpenGL = 1,
		};
	public: //functions

		/**
 * @brief Virtual destructor for RendererAPI class.
 *
 * This function is responsible for freeing any resources that the RendererAPI object may have acquired during its lifetime, such as memory or graphics resources. It does not return a value and has no parameters. 
 */
virtual ~RendererAPI() =default;
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

		/**
 * @brief This function returns the current API object used by the application.
 * @return The currently active API object, or "Unknown" if no API is set.
 */
static inline API GetAPI() { return s_API; }

		/**
 * @brief This function sets the API type for the RendererAPI class.
 * @param Type The API type to be set, which can be one of the values defined in the RendererAPI::API enum.
 * @return void
 */
static inline void SetAPI(RendererAPI::API Type) { s_API = Type; }

	private:
		static API s_API;


	};

	namespace Utils
	{
		/**
 * @brief Converts the current RendererAPI to a string.
 *
 * This function converts the enum value of RendererAPI into a human-readable string representation.
 * It uses a switch statement to check the integer equivalent of the RendererAPI and returns a corresponding string. 
 * If the RendererAPI is not recognized, it defaults to "UNDEFINED".
 *
 * @return A string representing the current RendererAPI. Possible values are: "Headless", "OpenGL", or "UNDEFINED" if the API is unknown.
 */
[[maybe_unused]]static std::string ConvertAPIToString()
		{
			switch ((int)RendererAPI::GetAPI())
			{
			case 0:
			{
				return {"Headless"};
				break;
			}
			case 1:
			{
				return {"OpenGL"};
				break;
			}
				default:
			{
				return {"UNDEFINED"};
			}
			}

			return {"UNDEFINED"};
		}
	}
}