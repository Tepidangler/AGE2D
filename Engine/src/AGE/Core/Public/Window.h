#pragma once

#include "AGEpch.hpp"

#include "Core.h"
#include "Events/Public/Event.h"
#include "Render/Public/GraphicsContext.h"

namespace AGE
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;
		const char* String;

		WindowProps(const std::string& T = "Alcoy Game Engine Editor", unsigned int W = 1280, unsigned int H = 720, const char* S = "")
			: Title(T), Width(W), Height(H), String(S)
		{

		}
	};

	//Represents a desktop system based Window

	class AGE_API Window
	{
	public:
		
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		//Attributes
		virtual void SetEventCallback(const EventCallbackFn& Callback) = 0;

		virtual void SetVSync(bool Enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual Vector2 GetMousePos() = 0;
		virtual void* GetNativeWindow() const = 0;
		inline virtual HWND GetWin32Window() = 0;

		virtual GraphicsContext* GetGraphicsContext() = 0;

		virtual void SwitchRenderer() = 0;
		virtual void RebuildWindow() = 0;

		virtual void SetWindowIcon(const std::filesystem::path& Path) =0;

		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};
}