#pragma once

typedef unsigned short uint16_t;

namespace AGE
{
	using JoyStickID = uint16_t;
	using JoyStickCode = uint16_t;

	namespace JoyStick
	{
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
			GamePadAxisLast         = GamePadAxisRightTrigger
		};
	}
}