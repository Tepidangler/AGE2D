#pragma once
#include "Core/Public/Log.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <thread>
#include <mutex>
#include <sstream>

namespace AGE {

	using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;

	struct ProfileResult
	{
		std::string Name;

		FloatingPointMicroseconds Start;
		std::chrono::microseconds ElapsedTime;
		std::thread::id ThreadID;
	};

	struct InstrumentationSession
	{
		std::string Name;
	};

	class Instrumentor
	{
	public:
		/**
 * @brief Deleted copy constructor for the Instrumentor class to prevent copying.
 *
 * This function is marked as deleted because we do not want any copies of an instance of this class.
 * It's a good practice to avoid unnecessary copying and duplication in our code, which can lead to performance issues or memory leaks. 
 * The copy constructor for the Instrumentor class has been set to private to prevent its use.
 */
/**
 * @brief Deleted copy constructor for the Instrumentor class.
 *
 * This function is marked as deleted to prevent copying of an instance of this class, which would not make sense in the context of our application.
 */
Instrumentor(const Instrumentor&) = delete;
		/**
 * @brief Instrumentor move constructor is deleted to prevent copying of the instrumentor object.
 * 
 * This function is marked as deleted in C++, which means that it cannot be used for creating a copy of an existing object.
 * It's useful when we want to ensure that objects are not copied unintentionally and can only be moved.
 *
 * @return The move constructor is implicitly declared as deleted by the compiler if any non-static data member 
 *         or base class has a user-declared destructor, copy assignment operator, or move assignment operator.
 */
/**
 * @brief Move constructor for the Instrumentor class. Deleted to prevent copying of objects.
 * @param other The object to be moved from.
 */
Instrumentor(Instrumentor&&) = delete;

		/**
 * @brief Starts a new instrumentation session.
 * 
 * This function starts a new session with the given name and writes the header to the output stream. If there is an existing session, it will be closed before starting the new one. The results of profiling meant for the original session will end up in the newly opened session instead.
 * @param[in] name The name of the new session.
 * @param[in] filepath The path to the output JSON file. Defaults to "results.json".
 * 
 * @return void
 */
/**
 * @brief Starts a new profiling session.
 *
 * This function starts a new profiling session with the given name and writes the header to the output stream. If there is already an active session, it will be closed before starting the new one. 
 * The results of any profiling data meant for the original session will instead go into the newly started session.
 *
 * @param[in] name     The name of the new session. This should ideally represent what the session is measuring or recording.
 * @param[in] filepath Optional parameter specifying where to write the profiling data. Defaults to "results.json".
 */
void BeginSession(const std::string& name, const std::string& filepath = "results.json")
		{
			std::lock_guard lock(m_Mutex);
			if (m_CurrentSession)
			{
				// If there is already a current session, then close it before beginning new one.
				// Subsequent profiling output meant for the original session will end up in the
				// newly opened session instead.  That's better than having badly formatted
				// profiling output.
				if (Log::GetCoreLogger()) // Edge case: BeginSession() might be before Log::Init()
				{
					CoreLogger::Error("Instrumentor::BeginSession('{0}') when session '{1}' already open.", name, m_CurrentSession->Name);
				}
				InternalEndSession();
			}
			m_OutputStream.open(filepath);

			if (m_OutputStream.is_open())
			{
				m_CurrentSession = new InstrumentationSession({ name });
				WriteHeader();
			}
			else
			{
				if (Log::GetCoreLogger()) // Edge case: BeginSession() might be before Log::Init()
				{
					CoreLogger::Error("Instrumentor could not open results file '{0}'.", filepath);
				}
			}
		}

		/**
 * @brief This function is used to end the session. It locks a mutex and then calls an internal function to actually end the session.
 * 
 * @return void
 */
/**
 * @brief This function is used to end the session. It ensures thread safety by using a std::lock_guard on m_Mutex. 
 *        The actual work of ending the session is done by calling InternalEndSession().
 * @return void
 */
void EndSession()
		{
			std::lock_guard lock(m_Mutex);
			InternalEndSession();
		}

		/**
 * @brief Writes a profile result to an output stream in JSON format.
 *
 * This function takes a ProfileResult object and writes it as a JSON string to the output stream. The JSON string includes details about the elapsed time, name of the operation, thread ID, and start timestamp. It also locks the mutex for thread safety. If the current session is active (m_CurrentSession == true), the function writes the JSON string to the output stream and flushes it.
 *
 * @param result The ProfileResult object to be written.
 */
/**
 * @brief Writes a profile result to the output stream in JSON format.
 *
 * This function takes a ProfileResult object and writes its data into an output 
 * stream in JSON format. The data includes the category, duration, name, phase (X for unknown), 
 * process ID (0 as it's not applicable here), thread ID, and timestamp. It also locks a mutex to ensure 
 * thread safety when writing to the output stream. If the current session is active, the function writes 
 * the JSON string into the output stream and flushes it.
 *
 * @param result The ProfileResult object containing data about the profile.
 */
void WriteProfile(const ProfileResult& result)
		{
			std::stringstream json;

			json << std::setprecision(3) << std::fixed;
			json << ",{";
			json << "\"cat\":\"function\",";
			json << "\"dur\":" << (result.ElapsedTime.count()) << ',';
			json << "\"name\":\"" << result.Name << "\",";
			json << "\"ph\":\"X\",";
			json << "\"pid\":0,";
			json << "\"tid\":" << result.ThreadID << ",";
			json << "\"ts\":" << result.Start.count();
			json << "}";

			std::lock_guard lock(m_Mutex);
			if (m_CurrentSession)
			{
				m_OutputStream << json.str();
				m_OutputStream.flush();
			}
		}

		/**
 * @brief Returns a reference to the singleton instance of the Instrumentor class.
 * 
 * This function creates and returns a reference to an instance of the Instrumentor class, which is a part of the profiling system used in this application. The instance is created using the 'static' keyword, ensuring that it is only initialized once and reused across multiple calls.
 * 
 * @return A reference to the singleton instance of the Instrumentor class.
 */
/**
 * @brief Returns a reference to the singleton instance of the Instrumentor class.
 * 
 * This function creates and returns a static instance of the Instrumentor class, ensuring that only one instance exists throughout the program's execution.
 * The instance is returned as a reference, allowing for easy access and manipulation of its properties or methods.
 * 
 * @return A reference to the singleton instance of the Instrumentor class.
 */
static Instrumentor& Get()
		{
			static Instrumentor instance;
			return instance;
		}
	private:
		/**
 * @brief Constructor for the Instrumentor class.
 */
/**
 * @brief Constructs an Instrumentor object with a null current session pointer.
 */
Instrumentor()
			: m_CurrentSession(nullptr)
		{
		}

		/**
 * @brief Destructor for the Instrumentor class.
 * 
 * This function ends the current session and writes any remaining profiling data to disk. It is called automatically when the Instrumentor object goes out of scope, ensuring that all profiling data is written before the program exits.
 * 
 * @return void
 */
/**
 * @brief Destructor for the Instrumentor class.
 * 
 * This function ends the current session and writes any remaining profiling data to disk. It is called automatically when the Instrumentor object goes out of scope, ensuring that all profiling data is written before the program exits.
 */
~Instrumentor()
		{
			EndSession();
		}

		/**
 * @brief This function writes a JSON header to the output stream.
 * The header includes an object "otherData" and an array "traceEvents". 
 * After calling this function, the output stream will be flushed immediately.
 *
 * @return void
 */
/**
 * @brief This function writes a JSON header to the output stream.
 * The header includes an object "otherData" and an array "traceEvents". 
 * After calling this function, the stream is ready for writing trace events.
 */
void WriteHeader()
		{
			m_OutputStream << "{\"otherData\": {},\"traceEvents\":[{}";
			m_OutputStream.flush();
		}

		/**
 * @brief Writes the footer of a JSON object to an output stream.
 *
 * This function writes the closing bracket and square brackets that form the end of a JSON object 
 * into the output stream. It is typically used after writing all other elements of the JSON object.
 *
 * @return void
 */
/**
 * @brief Writes the footer to the output stream.
 *
 * This function writes a closing bracket and flushes the output stream, which is typically used in JSON or similar formats where data is written out as a series of key-value pairs enclosed within curly braces {}. 
 *
 * @return void
 */
void WriteFooter()
		{
			m_OutputStream << "]}";
			m_OutputStream.flush();
		}

		// Note: you must already own lock on m_Mutex before
		// calling InternalEndSession()
		/**
 * @brief This function is used to end the current session and clean up resources.
 * It writes a footer, closes the output stream, deletes the current session object, and sets m_CurrentSession to nullptr.
 * 
 * @return void
 */
/**
 * @brief This function is used to end the current session and clean up resources.
 * It writes a footer, closes the output stream, deletes the current session object, and sets m_CurrentSession to nullptr.
 * 
 * @return void
 */
void InternalEndSession()
		{
			if (m_CurrentSession)
			{
				WriteFooter();
				m_OutputStream.close();
				delete m_CurrentSession;
				m_CurrentSession = nullptr;
			}
		}
	private:
		std::mutex m_Mutex;
		InstrumentationSession* m_CurrentSession;
		std::ofstream m_OutputStream;
	};

	class InstrumentationTimer
	{
	public:
		/**
 * @brief Constructs an InstrumentationTimer object with a given name.
 * 
 * The constructor initializes the timer with the provided name and sets m_Stopped to false. It also records the current time point using std::chrono::steady_clock::now() and stores it in m_StartTimepoint.
 * @param name A string representing the name of the instrumentation timer.
 */
/**
 * @brief Constructs an InstrumentationTimer object with a given name.
 * @param name The name to be associated with the timer.
 * 
 * This constructor initializes the timer with the provided name and sets m_Stopped to false, indicating that the timer is not stopped yet. It also records the current time point using std::chrono::steady_clock::now() and stores it in m_StartTimepoint.
 */
InstrumentationTimer(const char* name)
			: m_Name(name), m_Stopped(false)
		{
			m_StartTimepoint = std::chrono::steady_clock::now();
		}

		/**
 * @brief Destructor for the InstrumentationTimer class. Stops the timer if it has not been stopped already.
 */
/**
 * @brief Destructor for the InstrumentationTimer class. Stops the timer if it hasn't been stopped already.
 */
~InstrumentationTimer()
		{
			if (!m_Stopped)
				Stop();
		}

		/**
 * @brief Stops the timer and writes a profile to the instrumentor.
 * 
 * This function stops the timer by capturing the current time point using `std::chrono::steady_clock::now()`, calculates the elapsed time since the start timepoint was set in microseconds, then writes this information along with other details such as the name of the timer and the ID of the thread to the instrumentor.
 * 
 * @return void
 */
/**
 * @brief Stops the timer and writes a profile to the instrumentor.
 * 
 * This function measures the time elapsed since the start of the timer, writes this information to the Instrumentor, and then resets the timer. The profile includes the name of the timer, the start time, the elapsed time, and the ID of the thread that executed the code.
 * 
 * @return void
 */
void Stop()
		{
			auto endTimepoint = std::chrono::steady_clock::now();
			auto highResStart = FloatingPointMicroseconds{ m_StartTimepoint.time_since_epoch() };
			auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch();

			Instrumentor::Get().WriteProfile({ m_Name, highResStart, elapsedTime, std::this_thread::get_id() });

			m_Stopped = true;
		}
	private:
		const char* m_Name;
		std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
		bool m_Stopped;
	};

	namespace InstrumentorUtils {

		template <size_t N>
		struct ChangeResult
		{
			char Data[N];
		};

		template <size_t N, size_t K>
		"This function cleans up an input string by removing a specified substring."
constexpr 
auto CleanupOutputString(const char(&expr)[N], const char(&remove)[K])
		{
			ChangeResult<N> result = {};

			size_t srcIndex = 0;
			size_t dstIndex = 0;
			while (srcIndex < N)
			{
				size_t matchIndex = 0;
				while (matchIndex < K - 1 && srcIndex + matchIndex < N - 1 && expr[srcIndex + matchIndex] == remove[matchIndex])
					matchIndex++;
				if (matchIndex == K - 1)
					srcIndex += matchIndex;
				result.Data[dstIndex++] = expr[srcIndex] == '"' ? '\'' : expr[srcIndex];
				srcIndex++;
			}
			return result;
		}
	}
}

#define AGE_PROFILE 1
#if AGE_PROFILE
// Resolve which function signature macro will be used. Note that this only
// is resolved when the (pre)compiler starts, so the syntax highlighting
// could mark the wrong one in your editor!
#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
#define AGE_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
#define AGE_FUNC_SIG __PRETTY_FUNCTION__
#elif (defined(__FUNCSIG__) || (_MSC_VER))
#define AGE_FUNC_SIG __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
#define AGE_FUNC_SIG __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
#define AGE_FUNC_SIG __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
#define AGE_FUNC_SIG __func__
#elif defined(__cplusplus) && (__cplusplus >= 201103)
#define AGE_FUNC_SIG __func__
#else
#define AGE_FUNC_SIG "AGE_FUNC_SIG unknown!"
#endif

#define AGE_PROFILE_BEGIN_SESSION(name, filepath) ::AGE::Instrumentor::Get().BeginSession(name, filepath)
#define AGE_PROFILE_END_SESSION() ::AGE::Instrumentor::Get().EndSession()
#define AGE_PROFILE_SCOPE_LINE2(name, line) constexpr auto fixedName##line = ::AGE::InstrumentorUtils::CleanupOutputString(name, "__cdecl ");\
											   ::AGE::InstrumentationTimer timer##line(fixedName##line.Data)
#define AGE_PROFILE_SCOPE_LINE(name, line) AGE_PROFILE_SCOPE_LINE2(name, line)
#define AGE_PROFILE_SCOPE(name) AGE_PROFILE_SCOPE_LINE(name, __LINE__)
#define AGE_PROFILE_FUNCTION() AGE_PROFILE_SCOPE(AGE_FUNC_SIG)
#else
#define AGE_PROFILE_BEGIN_SESSION(name, filepath)
#define AGE_PROFILE_END_SESSION()
#define AGE_PROFILE_SCOPE(name)
#define AGE_PROFILE_FUNCTION()
#endif