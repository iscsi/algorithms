#pragma once
#include <sstream>
#include <string>
#include <vector>

namespace rili {
namespace test {
/// @cond INTERNAL
template <typename T>
class isStreamable {
public:
	template <typename U>
	static auto test(const U* u) -> decltype(*static_cast<std::ostringstream*>(nullptr) << *u);
	static auto test(...) -> std::false_type;

	enum { value = !std::is_same<decltype(test(static_cast<T*>(nullptr))), std::false_type>::value };
};

template <typename T>
std::string toString(T const&, typename std::enable_if<!isStreamable<T>::value>::type* = nullptr) noexcept {
	return std::string();
}

template <typename T>
std::string toString(T const& t, typename std::enable_if<isStreamable<T>::value>::type* = nullptr) noexcept {
	std::ostringstream stream;
	stream << t;
	return stream.str();
}

template <typename T>
std::string toString(std::vector<T> const& v, typename std::enable_if<isStreamable<T>::value>::type* = nullptr) noexcept {
	std::string str("{");
	for (size_t i = 0; i < v.size(); i++)
	{
		if (i > 0)
			str += ", ";
		str += toString(v[i]);
	}
	str += "}";
	return str;
}
/// @endcond INTERNAL
}  // namespace test
}  // namespace rili
