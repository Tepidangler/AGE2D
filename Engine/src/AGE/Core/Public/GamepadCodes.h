#pragma once

typedef unsigned char uint8_t;

namespace AGE
{
	using GamePadCode = uint8_t;

	namespace GamePad
	{
		enum Buttons: GamePadCode
		{
			//Centered = 0,
			//Up = 1,
			//Right = 2,
			//Down = 3,
			//Left = 8,
			//RightUp = Right | Up,
			//RightDown = Right | Down,
			//LeftUp = Left | Up,
			//LeftDown = Left | Down

			GamePadButtonA				=0,
			GamePadButtonB              =1,
			GamePadButtonX              =2,
			GamePadButtonY              =3,
			GamePadButtonLB				=4,
			GamePadButtonRB				=5,
			GamePadButtonBack           =6,
			GamePadButtonStart          =7,
			GamePadButtonGUIDE          =8,
			GamePadButtonLeftThumb	    =9,
			GamePadButtonRightThumb     =10,
			GamePadButtonDpadUp         =11,
			GamePadButtonDpadRight      =12,
			GamePadButtonDpadDown       =13,
			GamePadButtonDpadLeft       =14,
			GamePadButtonLast           =GamePadButtonDpadLeft,
										
			GamePadButtonCross			=GamePadButtonA,
			GamePadButtonCircle			=GamePadButtonB,
			GamePadButtonSquare			=GamePadButtonX,
			GamePadButtonTriangle		=GamePadButtonY

		};

		enum XInputMasks : uint16_t
		{
			XInputDpadUp = 0x0001,
			XInputDpadDown = 0x0002,
			XInputDpadLeft = 0x0004,
			XInputDpadRight = 0x0008,
			XInputStart = 0x0010,
			XInputBack = 0x0020,
			XInputLeftThumb = 0x0040,
			XInputRightThumb = 0x0080,
			XInputLeftShoulder = 0x0100,
			XInputRightShoulder = 0x0200,
			XInputButtonA = 0x1000,
			XInputButtonB = 0x2000,
			XInputButtonX = 0x4000,
			XInputButtonY = 0x8000

		};
	}
}