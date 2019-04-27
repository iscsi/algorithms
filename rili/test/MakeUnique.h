#pragma once

#include <memory>

#if __cplusplus < 201402L
#include <cstddef>
#include <type_traits>
#include <utility>
#endif

namespace rili {
#if __cplusplus >= 201402L
using std::make_unique;
#else
namespace details {
template <class T>
struct _Unique_if {
	typedef std::unique_ptr<T> _Single_object;
};

template <class T>
struct _Unique_if<T[]> {
	typedef std::unique_ptr<T[]> _Unknown_bound;
};

template <class T, std::size_t N>
struct _Unique_if<T[N]> {
	typedef void _Known_bound;
};
}  // namespace details

template <class T, class... Args>
typename details::_Unique_if<T>::_Single_object make_unique(Args&&... args) {
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template <class T>
typename details::_Unique_if<T>::_Unknown_bound make_unique(std::size_t n) {
	typedef typename std::remove_extent<T>::type U;
	return std::unique_ptr<T>(new U[n]());
}

template <class T, class... Args>
typename details::_Unique_if<T>::_Known_bound make_unique(Args&&...) = delete;

#endif
}  // namespace rili
