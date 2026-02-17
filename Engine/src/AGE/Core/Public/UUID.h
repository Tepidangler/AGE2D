#pragma once
#ifdef AG_PLATFORM_WINDOWS
#include <xhash>
#else
#include <functional>
#endif
#include <cinttypes>
namespace AGE
{
	class UUID
	{
	public:
		UUID();
		UUID(uint64_t uuid);
		UUID(const UUID&) = default;


		operator uint64_t() const { return m_UUID; }

	private:

		uint64_t m_UUID;
	};

}

namespace std
{
	template<>
	struct hash<AGE::UUID>
	{
		std::size_t operator()(const AGE::UUID& uuid) const noexcept
		{
			return hash<uint64_t>()((uint64_t)uuid);
		}
	};
}