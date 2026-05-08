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
 * This function is a virtual destructor that provides the base implementation for any derived classes of RendererAPI. It does not perform any specific actions and simply serves as a placeholder to ensure proper destruction of objects of derived classes when they are no longer in use.
 *
 * @return void
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
 * @brief Sets the Renderer API type.
 *
 * This function sets the Renderer API type to a specified value, which can be one of the enumerated types in the RendererAPI class.
 * The new API type is then stored in the static variable s_API for use by other parts of the program that need to interact with the renderer.
 *
 * @param Type - The desired API type to set. This should be one of the enumerated types defined in RendererAPI class.
 */
static inline void SetAPI(RendererAPI::API Type) { s_API = Type; }

	private:
		static API s_API;


	};

	namespace Utils
	{
		/**
 * @brief Converts the current RendererAPI to a string representation.
 *
 * This function uses a switch statement to convert the enum value of RendererAPI::GetAPI() into its corresponding string representation. 
 * If the API is not recognized, it returns "UNDEFINED".
 *
 * @return A std::string representing the current RendererAPI. Possible values are: "Headless", "OpenGL", or "UNDEFINED" if the API is unknown.
 */
static std::string ConvertAPIToString()
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