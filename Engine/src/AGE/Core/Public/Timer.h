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
/**
 * @brief Constructor for the Timer class. Initializes a new instance of the timer and resets it to 0.
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
/**
 * @brief This function resets the start time to the current time.
 * 
 * The function uses `std::chrono` library to get the current time and assigns it to m_Start variable.
 * It is typically used in timing operations where you want to measure how much time has passed since a certain point.
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
/**
 * @brief This function returns the elapsed time in milliseconds since the start time 'm_Start'.
 * 
 * The function uses a high resolution clock to measure the elapsed time and then converts it into milliseconds.
 * It does this by first converting the duration into nanoseconds, then dividing by 1 million (to convert from nanoseconds to microseconds) and finally again by 1000 (to convert from microseconds to milliseconds).
 * The result is a float representing the elapsed time in milliseconds.
 * 
 * @return A float representing the elapsed time in milliseconds since 'm_Start'.
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
/**
 * @brief This function returns the elapsed time in milliseconds.
 *
 * The function multiplies the result of `Elapsed()` by 1000 to convert seconds into milliseconds.
 * It assumes that `Elapsed()` is a function returning the elapsed time in seconds.
 *
 * @return A float representing the elapsed time in milliseconds.
 */
float ElapsedMillis()
		{
			return Elapsed() * 1000.f;
		}

	private:

		std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
	};
}