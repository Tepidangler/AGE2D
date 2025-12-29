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
#include <imgui_internal.h>

#include "rttr/registration_friend.h"


namespace AGE
{

	struct UIComponentType
	{
		enum Value : uint16_t
		{
			TextComponent,TextBoxComponent
		};

		UIComponentType() = default;
		constexpr UIComponentType(Value Val)
			: value(Val)
		{
			Name = ToString(value);

		}

		constexpr operator Value() const {return value;}

		explicit operator bool() const = delete;

		constexpr bool operator==(UIComponentType a) const
		{
			return value == a.value;
		}

		constexpr bool operator!=(UIComponentType a) const
		{
			return value != a.value;
		}

		operator std::string()  const
		{
			return Name;
		}
		std::string operator()(Value Val)  const
		{
			return ToString(Val);
		}

		Value ToValue()
		{
			return value;
		}
		Value ToValue() const
		{
			return value;
		}

		std::string& ToString()
		{
			return Name;
		}

		std::string ToString() const
		{
			return Name;
		}

		std::string ToString(Value Val)
		{
			switch(Val)
			{
				case TextComponent:
				{
					return "TextComponent";
					break;
				}
				case TextBoxComponent:
				{
					return "TextBoxComponent";
					break;
				}
			}
		}

		std::string ToString(Value Val) const
		{
			switch(Val)
			{
				case TextComponent:
				{
					return "TextComponent";
					break;
				}
				case TextBoxComponent:
				{
					return "TextBoxComponent";
					break;
				}
			}
		}

	private:
		Value value;
		std::string Name = "";
	};

	struct UIProperties
	{
		UIProperties() = default;
		Vector3 Position = {0.f};
		Vector3 Rotation = {0.f};
		Vector3 Scale = {1.f};
		bool Visible = true;
	};

	struct BoxProperties
	{
		BoxProperties() = default;
		Vector3 Position = {0.f};
		Vector3 Rotation = {0.f};
		Vector3 Scale = {1.f};
		Vector4 TintColor = {1.f};
		Ref<Texture> Texture = nullptr;
	};


	class UIComponent
	{
	public:
		UIComponent(const std::string& Name);
		virtual ~UIComponent() = default;

		virtual void OnUpdate(TimeStep DeltaTime) {};
		std::string& GetName() {return m_Name;};
		UIProperties& GetProperties() {return m_CompProperties;};
		UIComponentType::Value GetType() {return m_Type;}
		UIProperties m_CompProperties;
		std::string m_Name = "";

		static Ref<UIComponent> Create(const std::string& Name, UIComponentType Type);
		static void DrawVec3Control(const std::string& Label, Vector3& Values, float ResetValue = 0.f, float ColumnWidth = 100.f);

		virtual void DrawFontSelectionComboBox() = 0;
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


} // AGE

#endif //AGE2D_UICOMPONENT_H