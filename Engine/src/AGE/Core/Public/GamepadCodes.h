#pragma once

typedef unsigned short uint16_t;

namespace AGE
{
	using GamePadCode = uint16_t;
	using JoyStickID = uint16_t;
	using JoyStickCode = uint16_t;

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
			GamePadButtonTriangle		=GamePadButtonY,

			INVALID = UINT8_MAX

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

		enum : JoyStickID
		{
			JoyStick1    = 0,
			JoyStick2    = 1,
			JoyStick3    = 2,
			JoyStick4    = 3,
			JoyStick5    = 4,
			JoyStick6    = 5,
			JoyStick7    = 6,
			JoyStick8    = 7,
			JoyStick9    = 8,
			JoyStick10   = 9,
			JoyStick11   = 10,
			JoyStick12   = 11,
			JoyStick13   = 12,
			JoyStick14   = 13,
			JoyStick15   = 14,
			JoyStick16   = 15,
			JoyStickLast = JoyStick16
		};

		enum Axes: JoyStickCode
		{
			GamePadAxisLeftX        = 0,
			GamePadAxisLeftY        = 1,
			GamePadAxisRightX       = 2,
			GamePadAxisRightY       = 3,
			GamePadAxisLeftTrigger  = 4,
			GamePadAxisRightTrigger = 5,
			GamePadAxisLast         = GamePadAxisRightTrigger,
			INVALIDAXES					= UINT16_MAX
		};
	}

}