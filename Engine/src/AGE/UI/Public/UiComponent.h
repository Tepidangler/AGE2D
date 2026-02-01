//
// Created by gdmgp on 12/3/2025.
//

#ifndef AGE2D_UICOMPONENT_H
#define AGE2D_UICOMPONENT_H
#pragma once
#include "Core/Public/Core.h"
#include "Math/Public/Math.h"
#include "Core/Public/DeltaTime.h"
#include "Scene/Public/Components.h"
#include <rttr/registration>
#include <imgui.h>
#include "UI/Public/UIStructs.h"
#include <imgui_internal.h>
#include "rttr/registration_friend.h"


namespace AGE
{
#if 1

	class UIComponent
	{
	public:
		UIComponent(const std::string& Name);
		virtual ~UIComponent() = default;

		virtual void OnUpdate(TimeStep DeltaTime) {};

		virtual void OnEvent(Event& Event) = 0;

		virtual void CallSerialize(DataWriter* Serializer) = 0;
		virtual void CallDeserialize(DataReader* Serializer) = 0;
		std::string& GetName() {return m_Name;};
		UIProperties& GetProperties() {return m_CompProperties;};
		UIComponentType::Value GetType() {return m_Type;}
		UIProperties m_CompProperties;
		std::string m_Name = "";

		static Ref<UIComponent> Create(const std::string& Name, UIComponentType Type);
		static void DrawVec3Control(const std::string& Label, Vector3& Values, float ResetValue = 0.f, float ColumnWidth = 100.f);

		virtual void DrawFontSelectionComboBox(){}
		virtual void DrawContent() = 0;

		template<typename T>
		T* As();

		RTTR_ENABLE()
	protected:
		UIComponentType m_Type = UIComponentType::TextComponent;

		UIComponent() = default;


		friend class Widget;
		RTTR_REGISTRATION_FRIEND

	};


#endif // #if 0
} // AGE
#endif //AGE2D_UICOMPONENT_H