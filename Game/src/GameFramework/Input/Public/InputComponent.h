#pragma once
#include "Core/Public/Core.h"
#include "Events/Public/GameEvent.h"
#include "Scene/Public/Components.h"
#include "Scene/Public/ScriptableEntity.h"
#include "Serializers/Public/DataReader.h"
#include "Serializers/Public/DataWriter.h"
#include "Math/Public/MathStructures.h"
#include "Actors/Public/Actor.h"
#include <functional>

namespace GameFramework
{
	enum class KeyStatus : uint8_t { Pressed = 0, Released = 1 };

	struct InputActionBinding
	{
	private:
		uint8_t bConsumeInput = 1;
		uint8_t bExecuteWhenPaused = 1;
		uint8_t bPaired = 1;
		std::string Name;
		int32_t Handle;

	public:
		KeyStatus Status;
		using ActionCallbackFn = std::function<void()>;

		ActionCallbackFn BindedFunction;

	public:
		InputActionBinding()
			:bPaired(false), Name(std::string()), Status(KeyStatus::Pressed), Handle(-1), bConsumeInput(true), bExecuteWhenPaused(false) {}

		InputActionBinding(const std::string& ActionName, const KeyStatus EventStatus)
			: bPaired(false), Name(ActionName), Status(EventStatus), Handle(-1), bConsumeInput(true), bExecuteWhenPaused(false) {}

		InputActionBinding(const InputActionBinding&) = default;
		//InputActionBinding(const AGE::Ref<InputActionBinding>&) = default;

		//TODO: Consider Move Constructor

		std::string GetActionName() const { return Name; }
		bool IsPaired() const { return bPaired; }
		int32_t GetHandle() const { return Handle; }

		void GenerateNewHandle()
		{
			static int32_t sHandle = 1;
			Handle = sHandle++;
		}

		bool operator==(const InputActionBinding& rhs)
		{
			return (IsValid() && GetHandle() == rhs.GetHandle());
		}

		bool IsValid() { return Handle != -1; }

		void Execute()
		{
			BindedFunction;
		}

		friend class InputComponent;
	};

	struct InputAxisBinding
	{
	public:
		uint8_t bConsumeInput = 1;
		uint8_t bExecuteWhenPaused = 1;

		std::string AxisName;

		float AxisValue;

		using AxisCallbackFn = std::function<void(float)>;

		AxisCallbackFn BindedFunction;

		InputAxisBinding()
			: AxisName(std::string()), AxisValue(0.f), bConsumeInput(true), bExecuteWhenPaused(false) {}
		InputAxisBinding(const std::string& Name)
			: AxisName(Name), AxisValue(0.f), bConsumeInput(true), bExecuteWhenPaused(false) {}

		template<typename T>
		void BindFunction(AxisCallbackFn Func)
		{
			BindedFunction = Func;
		}

		void Execute()
		{
			BindedFunction(AxisValue);
		}
	};

	class InputComponent : public AGE::ScriptableEntity
	{
	public:

		virtual void OnCreate() override;

		virtual void OnUpdate(AGE::TimeStep DeltaTime) override;

		virtual void OnEvent(AGE::Event& E) override;

		virtual std::string GetScriptableEntityType() override { return m_Name; }

		bool OnAxisMoved(AGE::AxisEvent& E);
		bool OnButtonPressed(AGE::GamepadButtonPressedEvent& E);
		bool OnButtonReleased(AGE::GamepadButtonReleasedEvent& E);

		static void Serialize(AGE::DataWriter* Serializer, const InputComponent& Data)
		{

		}

		static void Deserialize(AGE::DataReader* Serializer, InputComponent& Data)
		{

		}

		std::vector<AGE::Ref<InputActionBinding>> m_ActionBindings;
		std::vector<AGE::Ref<InputAxisBinding>> m_AxisBindings;
		bool bBlockInput = false;



		template<typename T>
		InputActionBinding& BindAction(const std::string& Action, KeyStatus Status, T* Instigator, InputActionBinding::ActionCallbackFn Func)
		{
			InputActionBinding Binding(Action, Status);

			return AddActionBinding(Binding);
		}

		template<typename T>
		AGE::Ref<InputAxisBinding>& BindAxis(const std::string& Axis, T* Instigator, InputAxisBinding::AxisCallbackFn Func)
		{
			InputAxisBinding Binding(Axis);
			m_AxisBindings.emplace_back(AGE::CreateRef<InputAxisBinding>(Binding));
			Binding.BindFunction<T>(Func);
			return m_AxisBindings.back();
		}

		InputActionBinding& AddActionBinding(InputActionBinding Binding)
		{
			m_ActionBindings.emplace_back(AGE::CreateRef<InputActionBinding>(Binding));
			InputActionBinding& BindRef = *m_ActionBindings.back().get();
			//BindRef.GenerateNewHandle();

			if (BindRef.Status == KeyStatus::Pressed || BindRef.Status == KeyStatus::Released)
			{
				const KeyStatus PairedEvent = Binding.Status == KeyStatus::Pressed ? KeyStatus::Released : KeyStatus::Pressed;

				for (int i = (int)(m_ActionBindings.size() - 2); i >= 0; i--)
				{
					InputActionBinding& Ref = *m_ActionBindings[i].get();
					if (Ref.GetActionName() == BindRef.GetActionName())
					{
						if (Ref.bPaired)
						{
							BindRef.bPaired = true;
							break;
						}
						else if (Ref.Status == PairedEvent)
						{
							Ref.bPaired = true;
							BindRef.bPaired = true;
						}
					}
				}
			}

			return BindRef;
		}

		void ShouldBlockInput(bool Block)
		{
			bBlockInput = Block;
		}

		bool IsBlockingInput() { return bBlockInput; }



	private:
		std::string m_Name = "Input Component";

		std::string FindCorrespondingAxisName(std::vector<std::pair<std::string, std::vector<uint8_t>>>& AxisBindings, uint8_t Key);
		std::string FindCorrespondingActionName(std::vector<std::pair<std::string, std::vector<uint8_t>>>& ActionBindings, uint8_t Key);


	};
}
