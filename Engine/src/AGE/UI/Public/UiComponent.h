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
#include "UI/Public/UIStructs.h"
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconversion"
#ifdef AG_PLATFORM_LINUX
#pragma clang diagnostic ignored "-Wnontrivial-memcall"
#pragma clang diagnostic ignored "-Wunused-function"
#endif
#ifdef AG_PLATFORM_WINDOWS
#pragma clang diagnostic ignored "-Wmicrosoft-unqualified-friend"
#endif
#include <imgui_internal.h>
#include <imgui.h>
#include <rttr/registration>
#include "rttr/registration_friend.h"
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wfloat-conversion"
#ifdef AG_PLATFORM_WINDOWS
#pragma GCC diagnostic ignored "-Wmicrosoft-unqualified-friend"
#endif
#include <imgui_internal.h>
#include <rttr/registration>
#include "rttr/registration_friend.h"
#pragma GCC diagnostic pop
#elif defined(_MSC_VER)
#pragma warning(push, 0)
#include <imgui_internal.h>
#include <rttr/registration>
#include "rttr/registration_friend.h"
#pragma warning(pop)
#else
#error "Compiler is not supported with AGE yet"
#endif


namespace AGE
{
#if 1

	class UIComponent
	{
	public:
		UIComponent(const std::string& Name);
		/**
 * @brief Virtual destructor for the UIComponent class.
 *
 * This function is responsible for releasing any resources that were acquired by the object during its lifetime. It does not return anything and has no parameters.
 */
virtual ~UIComponent() = default;

		virtual void OnUpdate(TimeStep DeltaTime) {};

		virtual void OnEvent(Event& Event) = 0;

		virtual void CallSerialize(DataWriter* Serializer) = 0;
		virtual void CallDeserialize(DataReader* Serializer) = 0;
		/**
 * @brief Gets the name of the object.
 *
 * This function returns a reference to the internal string that holds the name of the object. The caller can modify this string, and the changes will be reflected in the object's state. 
 *
 * @return A reference to the internal string holding the name.
 */
std::string& GetName() {return m_Name;};
		/**
 * @brief Returns a reference to the UI properties object.
 *
 * This function returns a reference to an object of type UIProperties, which holds all the properties related to the user interface. These properties can be used for customizing the appearance and behavior of different UI elements.
 *
 * @return A reference to the UIProperties object.
 */
UIProperties& GetProperties() {return m_CompProperties;};
		/**
 * @brief This function returns the type of the UI component.
 * @return The type of the UI component as an enumerated value.
 */
UIComponentType::Value GetType() {return m_Type;}
		UIProperties m_CompProperties;
		std::string m_Name = "";

		static Ref<UIComponent> Create(const std::string& Name, UIComponentType Type);
		static void DrawVec3Control(const std::string& Label, Vector3& Values, float ResetValue = 0.f, float ColumnWidth = 100.f);

		/**
 * @brief This function is responsible for drawing the font selection combo box on the screen.
 * 
 * @return None
 */
virtual void DrawFontSelectionComboBox(){}
		virtual void DrawContent() = 0;

		template<typename T>
		T* As();

		RTTR_ENABLE()
	protected:
		UIComponentType m_Type = UIComponentType::TextComponent;

		/**
 * @brief Default constructor for the UIComponent class.
 *
 * This function initializes a new instance of the UIComponent class with default values. It does not take any parameters and returns nothing. The behavior is undefined if this function is called on an already initialized object.
 */
UIComponent() = default;


		friend struct Widget;
		RTTR_REGISTRATION_FRIEND

	};


#endif // #if 0
} // AGE
#endif //AGE2D_UICOMPONENT_H