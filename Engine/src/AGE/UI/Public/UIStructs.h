//
// Created by gdmgp on 12/29/2025.
//

#ifndef AGE2D_UISTRUCTS_H
#define AGE2D_UISTRUCTS_H

#include <string>
#include "Core/Public/Core.h"
#include "Math/Public/Vector3.h"
#include "Math/Public/Vector4.h"
#include "Texture/Public/Texture.h"

namespace AGE
{
	template<typename ... Callable>
	struct UIVisitor : Callable...
	{
		using Callable::operator()...;
	};

	struct UIComponentType
	{
		enum Value : uint16_t
		{
			TextComponent,TextBoxComponent,
			HorizontalBoxComponent,VerticalBoxComponent,
			ButtonComponent,
			ImageComponent
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
				case HorizontalBoxComponent: {
					return "HorizontalBoxComponent";
					break;
				}
				case VerticalBoxComponent: {
					return "VerticalBoxComponent";
					break;
				}
				case ButtonComponent: {
					return "ButtonComponent";
					break;
				}
				case ImageComponent: {
					return "ImageComponent";
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
				case HorizontalBoxComponent: {
					return "HorizontalBoxComponent";
					break;
				}
				case VerticalBoxComponent: {
					return "VerticalBoxComponent";
					break;
				}
				case ButtonComponent: {
					return "ButtonComponent";
					break;
				}
				case ImageComponent: {
					return "ImageComponent";
					break;
				}
			}
		}

		static void Serialize(DataWriter* Serializer, const UIComponentType& Instance)
		{
			Serializer->WriteString(Instance.Name);
			Serializer->WriteRaw<uint16_t>(Instance.value);
		}

		static void Deserialize(DataReader* Serializer, UIComponentType& Instance)
		{
			Serializer->ReadString(Instance.Name);
			Serializer->ReadRaw<Value>(Instance.value);
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
		bool Focused = false;
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
}
#endif //AGE2D_UISTRUCTS_H