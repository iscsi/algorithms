#pragma once
/** @file */

#include <cstdint>
#include <functional>
#include <rili/test/Config.h>
#include <rili/test/ConvertToString.h>
#include <string>
#include <type_traits>

/// @cond INTERNAL
#define RILI_ASSERT_VA_ARGS_MACRO_EXPAND(x) x

#define RILI_ASSERT_EQ_HELPER(FILE, LINE, LEFT, RIGHT, MESSAGE, ...) \
	::rili::test::assert::eq(FILE, LINE, LEFT, RIGHT, #LEFT, #RIGHT, std::string(MESSAGE))

#define RILI_ASSERT_NE_HELPER(FILE, LINE, LEFT, RIGHT, MESSAGE, ...) \
	::rili::test::assert::ne(FILE, LINE, LEFT, RIGHT, #LEFT, #RIGHT, std::string(MESSAGE))

#define RILI_ASSERT_LT_HELPER(FILE, LINE, LEFT, RIGHT, MESSAGE, ...) \
	::rili::test::assert::lt(FILE, LINE, LEFT, RIGHT, #LEFT, #RIGHT, std::string(MESSAGE))

#define RILI_ASSERT_LE_HELPER(FILE, LINE, LEFT, RIGHT, MESSAGE, ...) \
	::rili::test::assert::le(FILE, LINE, LEFT, RIGHT, #LEFT, #RIGHT, std::string(MESSAGE))

#define RILI_ASSERT_GT_HELPER(FILE, LINE, LEFT, RIGHT, MESSAGE, ...) \
	::rili::test::assert::gt(FILE, LINE, LEFT, RIGHT, #LEFT, #RIGHT, std::string(MESSAGE))

#define RILI_ASSERT_GE_HELPER(FILE, LINE, LEFT, RIGHT, MESSAGE, ...) \
	::rili::test::assert::ge(FILE, LINE, LEFT, RIGHT, #LEFT, #RIGHT, std::string(MESSAGE))

#define RILI_ASSERT_TRUE_HELPER(FILE, LINE, VALUE, MESSAGE, ...) \
	::rili::test::assert::True(FILE, LINE, VALUE, #VALUE, std::string(MESSAGE))

#define RILI_ASSERT_FALSE_HELPER(FILE, LINE, VALUE, MESSAGE, ...) \
	::rili::test::assert::False(FILE, LINE, VALUE, #VALUE, std::string(MESSAGE))

#ifdef RILI_TEST_WITH_EXCEPTIONS
#define RILI_ASSERT_ANY_THROW_HELPER(FILE, LINE, INVOKE, MESSAGE, ...) \
	::rili::test::assert::anyThrow(FILE, LINE, INVOKE, std::string(MESSAGE))

#define RILI_ASSERT_THROW_HELPER(FILE, LINE, TYPE, INVOKE, MESSAGE, ...) \
	::rili::test::assert::Throw<TYPE>(FILE, LINE, INVOKE, #TYPE, std::string(MESSAGE))
#endif
/// @endcond INTERNAL

/**
 * @brief ASSERT_EQ(LEFT, RIGHT, MESSAGE) indicate about failure if LEFT and RIGHT are not equal(using: `!(LEFT ==
 * RIGHT)`) and immediately end test
 *
 * To failure information is included:
 * * file location
 * * line number
 * * LEFT and RIGHT stringified expression,
 * * LEFT and RIGHT value if convertiable to string (by std::ostringstream interface)
 * * optional message
 *
 * @note message parameter is optional - if not provided empty will be used
 */
#define ASSERT_EQ(LEFT, ...)		  \
	RILI_ASSERT_VA_ARGS_MACRO_EXPAND( \
		RILI_ASSERT_EQ_HELPER(__FILE__, __LINE__, LEFT, __VA_ARGS__, std::string(), std::string()))

/**
 * @brief ASSERT_NE(LEFT, RIGHT, MESSAGE) indicate about failure if LEFT and RIGHT are equal(using: `!(LEFT != RIGHT)`)
 * and immediately end test
 *
 * To failure information is included:
 * * file location
 * * line number
 * * LEFT and RIGHT stringified expression,
 * * LEFT and RIGHT value if convertiable to string (by std::ostringstream interface)
 * * optional message
 *
 * @note message parameter is optional - if not provided empty will be used
 */
#define ASSERT_NE(LEFT, ...)		  \
	RILI_ASSERT_VA_ARGS_MACRO_EXPAND( \
		RILI_ASSERT_NE_HELPER(__FILE__, __LINE__, LEFT, __VA_ARGS__, std::string(), std::string()))

/**
 * @brief ASSERT_LT(LEFT, RIGHT, MESSAGE) indicate about failure if LEFT is not less than RIGHT(using: `!(LEFT <
 * RIGHT)`) and immediately end test
 *
 * To failure information is included:
 * * file location
 * * line number
 * * LEFT and RIGHT stringified expression,
 * * LEFT and RIGHT value if convertiable to string (by std::ostringstream interface)
 * * optional message
 *
 * @note message parameter is optional - if not provided empty will be used
 */
#define ASSERT_LT(LEFT, ...)		  \
	RILI_ASSERT_VA_ARGS_MACRO_EXPAND( \
		RILI_ASSERT_LT_HELPER(__FILE__, __LINE__, LEFT, __VA_ARGS__, std::string(), std::string()))

/**
 * @brief ASSERT_LE(LEFT, RIGHT, MESSAGE) indicate about failure if LEFT is not less or equal RIGHT(using: `!(LEFT <=
 * RIGHT)`) and immediately end test
 *
 * To failure information is included:
 * * file location
 * * line number
 * * LEFT and RIGHT stringified expression,
 * * LEFT and RIGHT value if convertiable to string (by std::ostringstream interface)
 * * optional message
 *
 * @note message parameter is optional - if not provided empty will be used
 */
#define ASSERT_LE(LEFT, ...)		  \
	RILI_ASSERT_VA_ARGS_MACRO_EXPAND( \
		RILI_ASSERT_LE_HELPER(__FILE__, __LINE__, LEFT, __VA_ARGS__, std::string(), std::string()))

/**
 * @brief ASSERT_GT(LEFT, RIGHT, MESSAGE) indicate about failure if LEFT is not greater than RIGHT(using: `!(LEFT >
 * RIGHT)`) and immediately end test
 *
 * To failure information is included:
 * * file location
 * * line number
 * * LEFT and RIGHT stringified expression,
 * * LEFT and RIGHT value if convertiable to string (by std::ostringstream interface)
 * * optional message
 *
 * @note message parameter is optional - if not provided empty will be used
 */
#define ASSERT_GT(LEFT, ...)		  \
	RILI_ASSERT_VA_ARGS_MACRO_EXPAND( \
		RILI_ASSERT_GT_HELPER(__FILE__, __LINE__, LEFT, __VA_ARGS__, std::string(), std::string()))

/**
 * @brief ASSERT_GE(LEFT, RIGHT, MESSAGE) indicate about failure if LEFT is not greater or equal RIGHT(using: `!(LEFT >=
 * RIGHT)`) and immediately end test
 *
 * To failure information is included:
 * * file location
 * * line number
 * * LEFT and RIGHT stringified expression,
 * * LEFT and RIGHT value if convertiable to string (by std::ostringstream interface)
 * * optional message
 *
 * @note message parameter is optional - if not provided empty will be used
 */
#define ASSERT_GE(LEFT, ...)		  \
	RILI_ASSERT_VA_ARGS_MACRO_EXPAND( \
		RILI_ASSERT_GE_HELPER(__FILE__, __LINE__, LEFT, __VA_ARGS__, std::string(), std::string()))

/**
 * @brief ASSERT_TRUE(EXPR, MESSAGE) indicate about failure if EXPR is true(using: `!(EXPR == true)`) and immediately
 * end test
 *
 * To failure information is included:
 * * file location
 * * line number
 * * EXPR stringified expression,
 * * EXPR value
 * * optional message
 *
 * @note message parameter is optional - if not provided empty will be used
 */
#define ASSERT_TRUE(...)			  \
	RILI_ASSERT_VA_ARGS_MACRO_EXPAND( \
		RILI_ASSERT_TRUE_HELPER(__FILE__, __LINE__, __VA_ARGS__, std::string(), std::string()))

/**
 * @brief ASSERT_FALSE(EXPR, MESSAGE) indicate about failure if EXPR is true(using: `!(EXPR == false)`) and immediately
 * end test
 *
 * To failure information is included:
 * * file location
 * * line number
 * * EXPR stringified expression,
 * * EXPR value
 * * optional message
 *
 * @note message parameter is optional - if not provided empty will be used
 */
#define ASSERT_FALSE(...)			 \
	RILI_ASSERT_VA_ARGS_MACRO_EXPAND( \
		RILI_ASSERT_FALSE_HELPER(__FILE__, __LINE__, __VA_ARGS__, std::string(), std::string()))

/**
 * @brief ASSERT_ANY_THROW(INVOKE, MESSAGE) indicate about if any exception will be not thrown from INVOKE and
 * immediately end test
 *
 * To failure information is included:
 * * file location
 * * line number
 * * INVOKE stringified expression,
 * * optional message
 *
 * @note message parameter is optional - if not provided empty will be used
 */
#define ASSERT_ANY_THROW(...)		 \
	RILI_ASSERT_VA_ARGS_MACRO_EXPAND( \
		RILI_ASSERT_ANY_THROW_HELPER(__FILE__, __LINE__, __VA_ARGS__, std::string(), std::string()))

/**
 * @brief ASSERT_THROW(TYPE, INVOKE, MESSAGE) indicate about if any exception will be not thrown from INVOKE or thrown
 * exception type is not equal to ASSERTed type. In case of failure immediately end test
 *
 * To failure information is included:
 * * file location
 * * line number
 * * TYPE and INVOKE stringified expression,
 * * optional message
 *
 * @note message parameter is optional - if not provided empty will be used
 */
#define ASSERT_THROW(TYPE, ...)	   \
	RILI_ASSERT_VA_ARGS_MACRO_EXPAND( \
		RILI_ASSERT_THROW_HELPER(__FILE__, __LINE__, TYPE, __VA_ARGS__, std::string(), std::string()))

/// @cond INTERNAL
namespace rili {
namespace test {
namespace assert {

[[noreturn]] void handleFailure(std::string const& operation, std::string const& file, std::string const& line,
								std::string const& l, std::string const& r, std::string const& lname,
								std::string const& rname, std::string const& message);

[[noreturn]] void handleFailure(std::string const& operation, std::string const& file, std::string const& line,
								std::string const& v, std::string const& vname, std::string const& message);

[[noreturn]] void handleThrowFailure(std::string const& operation, std::string const& file, std::string const& line,
									 std::string const& assertedType, std::string const& resultType,
									 std::string const& message);

template <typename LEFT, typename RIGHT>
bool eq(const char* file, int64_t const& line, LEFT const& l, RIGHT const& r, const char* lname, const char* rname,
		std::string const& message) {
	const std::string operation("ASSERT_EQ");
	return l == r ? true : (handleFailure(operation, std::string(file), std::to_string(line), toString(l), toString(r),
										  std::string(lname), std::string(rname), message),
							false);
}

template <typename LEFT, typename RIGHT>
bool ne(const char* file, int64_t const& line, LEFT const& l, RIGHT const& r, const char* lname, const char* rname,
		std::string const& message) {
	const std::string operation("ASSERT_NE");
	return l != r ? true : (handleFailure(operation, std::string(file), std::to_string(line), toString(l), toString(r),
										  std::string(lname), std::string(rname), message),
							false);
}

template <typename LEFT, typename RIGHT>
bool lt(const char* file, int64_t const& line, LEFT const& l, RIGHT const& r, const char* lname, const char* rname,
		std::string const& message) {
	const std::string operation("ASSERT_LT");
	return l < r ? true : (handleFailure(operation, std::string(file), std::to_string(line), toString(l), toString(r),
										 std::string(lname), std::string(rname), message),
						   false);
}

template <typename LEFT, typename RIGHT>
bool le(const char* file, int64_t const& line, LEFT const& l, RIGHT const& r, const char* lname, const char* rname,
		std::string const& message) {
	const std::string operation("ASSERT_LE");
	return l <= r ? true : (handleFailure(operation, std::string(file), std::to_string(line), toString(l), toString(r),
										  std::string(lname), std::string(rname), message),
							false);
}

template <typename LEFT, typename RIGHT>
bool gt(const char* file, int64_t const& line, LEFT const& l, RIGHT const& r, const char* lname, const char* rname,
		std::string const& message) {
	const std::string operation("ASSERT_GT");
	return l > r ? true : (handleFailure(operation, std::string(file), std::to_string(line), toString(l), toString(r),
										 std::string(lname), std::string(rname), message),
						   false);
}

template <typename LEFT, typename RIGHT>
bool ge(const char* file, int64_t const& line, LEFT const& l, RIGHT const& r, const char* lname, const char* rname,
		std::string const& message) {
	const std::string operation("ASSERT_GE");
	return l >= r ? true : (handleFailure(operation, std::string(file), std::to_string(line), toString(l), toString(r),
										  std::string(lname), std::string(rname), message),
							false);
}

template <typename VALUE>
bool True(const char* file, int64_t const& line, VALUE const& v, const char* vname, std::string const& message) {
	const std::string operation("ASSERT_TRUE");
	return static_cast<bool>(v) == true ? true : (handleFailure(operation, std::string(file), std::to_string(line),
																"false", std::string(vname), message),
												  false);
}

template <typename VALUE>
bool False(const char* file, int64_t const& line, VALUE const& v, const char* vname, std::string const& message) {
	const std::string operation("ASSERT_FALSE");
	return static_cast<bool>(v) == false ? true : (handleFailure(operation, std::string(file), std::to_string(line),
																 "true", std::string(vname), message),
												   false);
}

#ifdef RILI_TEST_WITH_EXCEPTIONS
bool anyThrow(const char* file, int64_t const& line, std::function<void()> invoke, std::string const& message);

template <typename T>
bool Throw(const char* file, int64_t const& line, std::function<void()> invoke, const char* ASSERTedThrownType,
		   std::string const& message) {
	const std::string operation("ASSERT_THROW");
	const std::string assertedType(ASSERTedThrownType);
	try {
		invoke();
	} catch (T&) {
		return true;
	} catch (...) {
		handleThrowFailure(operation, std::string(file), std::to_string(line), assertedType, "OTHER", message);
	}
	handleThrowFailure(operation, std::string(file), std::to_string(line), assertedType, "NONE", message);
}
#endif
}  // namespace assert
}  // namespace test
}  // namespace rili

/// @endcond INTERNAL
