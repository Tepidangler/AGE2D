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
	
/**
 * @brief This class represents the ImGui layer in a system. It is responsible for rendering and handling user interface events.
 * 
 * The ImGuiLayer class provides methods to attach, detach, render GUI elements using ImGui, block or unblock events, start and end the GUI session respectively.
 */
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

		/**
 * @brief This function is used to set the state of event blocking in a system.
 * @param block A boolean value indicating whether events should be blocked or not.
 * @return None
 */
/**
 * @brief This function is used to set the state of event blocking in a system.
 * @param block A boolean value indicating whether events should be blocked or not.
 * @return None
 */
inline void BlockEvents(bool block) { m_BlockEvents = block; }

		virtual void End();

	private:
		void SetDarkThemeColors();

		bool OnWindowResized(WindowResizeEvent& E);

		bool m_BlockEvents = true;

		LayerStack m_LayerStack;

		GraphicsContext* m_Context;

		RendererAPI::API m_CurrentGraphicsAPI;
	};


}