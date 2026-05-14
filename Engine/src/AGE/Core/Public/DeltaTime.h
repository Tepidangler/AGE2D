#pragma once

namespace AGE
{
	class TimeStep
	{
	public:
		/**
 * @brief Constructs a TimeStep object with the given time value. If no argument is provided, it defaults to 0.
 * @param[in] time The time value for this TimeStep. Defaults to 0 if not specified.
 */
/**
 * @brief Constructs a TimeStep object with the given time value. If no argument is provided, it defaults to 0.
 * @param[in] time The time value for this TimeStep. Defaults to 0 if not specified.
 */
TimeStep(float time = 0.f)
			:m_Time(time)
		{
		}

		/**
 * @brief This function returns the time value in seconds.
 * @return A float representing the time in seconds.
 */
/**
 * @brief This function returns the time value in seconds.
 * @return A float representing the time in seconds.
 */
float GetSeconds() const { return m_Time; }
		/**
 * @brief This function returns the time value in milliseconds.
 * @return The time value multiplied by 1000 to convert it into milliseconds.
 */
/**
 * @brief This function returns the time value in milliseconds.
 * @return The time value multiplied by 1000 to convert it into milliseconds.
 */
float GetMilliseconds() const { return m_Time * 1000.f; }

		/**
 * @brief Converts the object into a floating-point number representing time.
 *
 * This function returns the value of 'm_Time' which is a private member variable of this class. It provides an implicit conversion to float, allowing it to be used in arithmetic expressions where a float is expected. 
 *
 * @return A floating-point number representing the time stored in 'm_Time'.
 */
/**
 * @brief Converts the object to a floating-point number representing time.
 *
 * This function returns the value of the 'm_Time' member variable, which represents time in some unit. The exact meaning and interpretation of this value is not specified here. 
 *
 * @return A float representing the current time value.
 */
operator float() const { return m_Time; }

	private:
		float m_Time;
	};
}