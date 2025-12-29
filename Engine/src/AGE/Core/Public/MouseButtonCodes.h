#pragma once

//Stolen form glfw3.h

typedef unsigned short uint16_t;

namespace AGE
{
	using MouseCode = uint16_t;

	namespace Mouse
	{
		enum Buttons: MouseCode
		{
			D1 = 0,
			D2 = 1,
			D3 = 2,
			D4 = 3,
			D5 = 4,
			D6 = 5,
			D7 = 6,
			D8 = 7,
			Last = D8,
			Left = D1,
			Right = D2,
			Middle = D3
		};
	}
}