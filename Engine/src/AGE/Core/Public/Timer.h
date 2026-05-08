#pragma once
#include <chrono>

namespace AGE
{
	class Timer
	{
	public:

		/**
 * @brief Constructor for the Timer class. It initializes a new instance of the Timer and resets it.
 */
Timer()
		{
			Reset();
		}

		/**
 * @brief This function resets the start time to the current time.
 * 
 * The function uses `std::chrono` library to get the current time and store it in m_Start variable.
 * It is typically used at the beginning of a performance measurement session, setting the starting point for timing measurements.
 * 
 * @return void
 */
void Reset()
		{
			m_Start = std::chrono::high_resolution_clock::now();
		}

		/**
 * @brief This function returns the elapsed time in milliseconds since the start time 'm_Start'.
 * 
 * The function uses std::chrono to measure the duration between the current time and the start time.
 * It then converts this duration from nanoseconds to milliseconds by dividing by 1,000,000 (since there are 1,000,000 nanoseconds in a millisecond).
 * The result is returned as a float.
 * 
 * @return A float representing the elapsed time in milliseconds.
 */
float Elapsed()
		{
			//return std::chrono::duration_cast<std::chrono::nanoseconds>(
			//	       std::chrono::high_resolution_clock::now() - m_Start).count() * .001f * .001f * .001f;

			return std::chrono::duration<float, std::nano>(std::chrono::high_resolution_clock::now() - m_Start).count() * .001f * .001f * .001f;
		}

		/**
 * @brief This function returns the elapsed time in milliseconds since the last reset.
 * @return A float representing the elapsed time in milliseconds. If no timer has been set, it will return 0.0f.
 */
float ElapsedMillis()
		{
			return Elapsed() * 1000.f;
		}

	private:

		std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
	};
}