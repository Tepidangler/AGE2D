#pragma once

#include "Core/Public/Layer.h"
#include "Core/Public/LayerStack.h"
#include "Events/Public/KeyEvent.h"
#include "Events/Public/MouseEvent.h"
#include "Events/Public/ApplicationEvent.h"
#include "Events/Public/RendererEvent.h"
#include "Render/Public/GraphicsContext.h"
#include "Render/Public/Renderer.h"



namespace AGE
{
	class AGE_API ImGuiLayer : public Layer
	{
	
	public:

		ImGuiLayer();

		~ImGuiLayer();

		virtual void OnAttach() override;
						  
		virtual void OnDetach() override;
		virtual void OnImGuiRender(TimeStep DeltaTime) override;


		virtual void Begin();

		virtual void OnEvent(Event& E) override;

		inline void BlockEvents(bool block) { m_BlockEvents = block; }

		virtual void End();

	private:
		void SetDarkThemeColors();

		bool OnWindowResized(WindowResizeEvent& E);
	private:
		float m_Time = 0.f;

		bool m_BlockEvents = true;

		bool m_RendererChanged = false;
		LayerStack m_LayerStack;

		GraphicsContext* m_Context;

		RendererAPI::API m_CurrentGraphicsAPI;
	};


}