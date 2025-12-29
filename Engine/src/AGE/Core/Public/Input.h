#pragma once
#include "Core.h"
#include "Keycodes.h"
#include "MouseButtonCodes.h"

namespace AGE
{
	 class AGE_API Input
	 {
		public:
			static bool IsKeyPressed(int Keycode);

			static bool IsMouseButtonPressed(int Button); 

			static bool IsGamepadButtonPressed(uint16_t ID, uint8_t Button);

			static float GetMouseX();

			static float GetMouseY();

			static std::pair<float,float> GetMouseXY();

			static bool IsJoyStickConnected(uint16_t ID);

			static float GetJoyStickLeftX(uint16_t ID);
			static float GetJoyStickLeftY(uint16_t ID);

			static std::pair<float,float> GetJoyStickLeftXY(uint16_t ID);

			static float GetJoyStickRightX(uint16_t ID);
			static float GetJoyStickRightY(uint16_t ID);
			static std::pair<float, float> GetJoyStickRightXY(uint16_t ID);

			static float GetJoyStickLeftTrigger(uint16_t ID);
			static float GetJoyStickRightTrigger(uint16_t ID);


	 private:
		 static bool IsJoyStickPresent(uint16_t ID);
	
	 };
}