//
// Created by gdmgp on 12/3/2025.
//

#ifndef AGE2D_WIDGET_H
#define AGE2D_WIDGET_H
#include "Core/Public/Core.h"
#include "Serializers/Public/DataReader.h"
#include "Serializers/Public/DataWriter.h"
namespace AGE
{
	class ScriptableWidget;

	struct Widget
	{
		static void Serialize(DataWriter* Serializer, const Widget& Data)
		{

		}

		static void Deserialize(DataReader* Serializer, Widget& Data)
		{

		}

		ScriptableWidget* Instance = nullptr;
		ScriptableWidget* (*InstantiateScript)();
		void (*DestroyScript)(Widget*);

		template<typename T>
		void Bind()
		{
			InstantiateScript = []() {return static_cast<ScriptableWidget*>(new T()); };
			DestroyScript = [](Widget* WC) {delete WC->Instance; WC->Instance = nullptr; };
		}

	};
} // AGE

#endif //AGE2D_WIDGET_H