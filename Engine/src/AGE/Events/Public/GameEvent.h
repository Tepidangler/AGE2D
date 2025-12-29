#pragma once
#include "Core/Public/Core.h"
#include "Event.h"

#include "Scene/Public/Scene.h"

namespace AGE
{

	class InputEvent : public Event
	{
		inline uint8_t GetGamepadButton() { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryGame)

	protected:
		InputEvent();
		InputEvent(int Axis, float Position)
			:m_Axis(Axis), m_Position(Position) {}
		InputEvent(int Button)
			: m_Button(Button) {}

	protected:
		int m_Axis;
		float m_Position;
		int m_Button;
	};

	class AxisEvent : public InputEvent
	{
	public:
		AxisEvent(int Axis, float Position)
			: InputEvent(Axis, Position) {}

		inline int GetAxis() { return m_Axis; }
		inline float GetPosition() { return m_Position; }
		EVENT_CLASS_TYPE(AxisMoved)
	};

	class GamepadButtonPressedEvent : public InputEvent
	{
	public:
		GamepadButtonPressedEvent(int Button)
			:InputEvent(Button) {}

		inline uint8_t GetButton() { return m_Button; }
		EVENT_CLASS_TYPE(GamepadButtonPressed)
	};

	class GamepadButtonReleasedEvent : public InputEvent
	{
	public:
		GamepadButtonReleasedEvent(int Button)
			:InputEvent(Button) {}

		inline int GetButton() { return m_Button; }
		EVENT_CLASS_TYPE(GamepadButtonReleased)
	};

	class SceneEvent : public Event
	{
		EVENT_CLASS_CATEGORY(EventCategoryGame)
		protected:
		SceneEvent(Ref<Scene> Scene)
			:m_Scene(Scene) {}

	protected:
		Ref<Scene> m_Scene;
	};

	class SceneChangedEvent : public SceneEvent
	{
		public:
		SceneChangedEvent(Ref<Scene> Scene)
			:SceneEvent(Scene){}

		inline Ref<Scene> GetScene() {return m_Scene;}
		EVENT_CLASS_TYPE(SceneChanged)
	};
}
