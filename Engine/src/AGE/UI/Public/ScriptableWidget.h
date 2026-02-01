//
// Created by gdmgp on 12/30/2025.
//

#ifndef AGE2D_SCRIPTABLEWIDGET_H
#define AGE2D_SCRIPTABLEWIDGET_H
#pragma once
#include "Core/Public/Core.h"
#include "Scene/Public/Entity.h"
#include "Core/Public/DeltaTime.h"
#include "UI/Public/UiComponent.h"


namespace AGE
{

	enum EWidgetStack : uint8_t
	{
		Menu,
		Modal,
		Splash,
		Game,
		INVALID
	};

	class ScriptableWidget : public std::enable_shared_from_this<ScriptableWidget>
	{
	public:
		virtual ~ScriptableWidget() {}

		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}

		template<typename T, typename ... Args>
		T& AddComponent(Args&& ... args)
		{
			return m_Entity.AddComponent<T>();
		}

		virtual void OnEvent(Event& E) {};
		virtual std::string GetName() { return m_Name; }
		virtual UUID GetID() { return m_Entity.GetUUID(); }
		virtual bool IsVisible() {return bIsVisible;}
		virtual void SetVisibility(bool Visibility) { bIsVisible = Visibility; }

	protected:
		virtual void OnInit() {}
		virtual void OnConstruct() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate(TimeStep DeltaTime) {}
		virtual void Reset() {}
		virtual Entity& GetEntityHandle() { return m_Entity; }
		std::string m_Name = "";
		bool bIsVisible = true;
		ScreenResolution m_Resolution;
		std::vector<Ref<UIComponent>> m_UIComponents;
		EWidgetStack m_Stack = EWidgetStack::INVALID;

	private:
		Entity m_Entity;
		friend class Scene;
		friend class WidgetStack;

	};
}



#endif //AGE2D_SCRIPTABLEWIDGET_H