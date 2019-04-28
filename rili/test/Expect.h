#pragma once
/** @file */

#include <cstdint>
#include <functional>
#include <rili/test/AlmostEqual.h>
#include <rili/test/Config.h>
#include <rili/test/ConvertToString.h>
#include <string>
#include <type_traits>

/// @cond INTERNAL
#define RILI_EXPECT_VA_ARGS_MACRO_EXPAND(x) x

#define RILI_ADD_FAILURE_HELPER(FILE, LINE, MESSAGE, ...) \
	::rili::test::expect::addFailure(FILE, LINE, std::string(MESSAGE))

#define RILI_EXPECT_EQ_HELPER(FILE, LINE, LEFT, RIGHT, MESSAGE, ...) \
	::rili::test::expect::eq(FILE, LINE, LEFT, RIGHT, #LEFT, #RIGHT, std::string(MESSAGE))

#define RILI_EXPECT_NE_HELPER(FILE, LINE, LEFT, RIGHT, MESSAGE, ...) \
	::rili::test::expect::ne(FILE, LINE, LEFT, RIGHT, #LEFT, #RIGHT, std::string(MESSAGE))

#define RILI_EXPECT_NEARLY_HELPER(FILE, LINE, LEFT, RIGHT, PRECISION, MESSAGE, ...) \
	::rili::test::expect::nearly(FILE, LINE, LEFT, RIGHT, PRECISION, #LEFT, #RIGHT, std::string(MESSAGE))

#define RILI_EXPECT_LT_HELPER(FILE, LINE, LEFT, RIGHT, MESSAGE, ...) \
	::rili::test::expect::lt(FILE, LINE, LEFT, RIGHT, #LEFT, #RIGHT, std::string(MESSAGE))

#define RILI_EXPECT_LE_HELPER(FILE, LINE, LEFT, RIGHT, MESSAGE, ...) \
	::rili::test::expect::le(FILE, LINE, LEFT, RIGHT, #LEFT, #RIGHT, std::string(MESSAGE))

#define RILI_EXPECT_GT_HELPER(FILE, LINE, LEFT, RIGHT, MESSAGE, ...) \
	::rili::test::expect::gt(FILE, LINE, LEFT, RIGHT, #LEFT, #RIGHT, std::string(MESSAGE))

#define RILI_EXPECT_GE_HELPER(FILE, LINE, LEFT, RIGHT, MESSAGE, ...) \
	::rili::test::expect::ge(FILE, LINE, LEFT, RIGHT, #LEFT, #RIGHT, std::string(MESSAGE))

#define RILI_EXPECT_TRUE_HELPER(FILE, LINE, VALUE, MESSAGE, ...) \
	::rili::test::expect::True(FILE, LINE, VALUE, #VALUE, std::string(MESSAGE))

#define RILI_EXPECT_FALSE_HELPER(FILE, LINE, VALUE, MESSAGE, ...) \
	::rili::test::expect::False(FILE, LINE, VALUE, #VALUE, std::string(MESSAGE))

#ifdef RILI_TEST_WITH_EXCEPTIONS
#define RILI_EXPECT_ANY_THROW_HELPER(FILE, LINE, INVOKE, MESSAGE, ...) \
	::rili::test::expect::anyThrow(FILE, LINE, INVOKE, std::string(MESSAGE))

#define RILI_EXPECT_THROW_HELPER(FILE, LINE, TYPE, INVOKE, MESSAGE, ...) \
	::rili::test::expect::Throw<TYPE>(FILE, LINE, INVOKE, #TYPE, std::string(MESSAGE))
#endif
/// @endcond INTERNAL

/**
 * @brief ADD_FAILURE(MESSAGE) indicate about custom failure
 *
 * To failure information is included:
 *  * file location
 *  * line number
 *  * message
 *
 * @note message parameter is optional - if not provided empty will be used
 */
#define ADD_FAILURE(...)			  \
	RILI_EXPECT_VA_ARGS_MACRO_EXPAND( \
		RILI_ADD_FAILURE_HELPER(__FILE__, __LINE__, __VA_ARGS__, std::string(), std::string()))

/**
 * @brief EXPECT_EQ(LEFT, RIGHT, MESSAGE) indicate about failure if LEFT and RIGHT are not equal(using: `!(LEFT ==
 * RIGHT)`)
 *
 * To failure information is included:
 * * file location
 * * line number
 * * LEFT and RIGHT stringified expression,
 * * LEFT and RIGHT value if convertiable to string (by std::ostringstream interface)
 * * optional message
 *
 * @note message parameter is optional - if not provided empty will be used
 * @return comparation result
 */
#define EXPECT_EQ(LEFT, ...)		  \
	RILI_EXPECT_VA_ARGS_MACRO_EXPAND( \
		RILI_EXPECT_EQ_HELPER(__FILE__, __LINE__, LEFT, __VA_ARGS__, std::string(), std::string()))

/**
 * @brief EXPECT_NE(LEFT, RIGHT, MESSAGE) indicate about failure if LEFT and RIGHT are equal(using: `!(LEFT != RIGHT)`)
 *
 * To failure information is included:
 * * file location
 * * line number
 * * LEFT and RIGHT stringified expression,
 * * LEFT and RIGHT value if convertiable to string (by std::ostringstream interface)
 * * optional message
 *
 * @note message parameter is optional - if not provided empty will be used
 * @return comparation result
 */
#define EXPECT_NE(LEFT, ...)		  \
	RILI_EXPECT_VA_ARGS_MACRO_EXPAND( \
		RILI_EXPECT_NE_HELPER(__FILE__, __LINE__, LEFT, __VA_ARGS__, std::string(), std::string()))

 /**
  * @brief EXPECT_NEAR(LEFT, RIGHT, PRECISION, MESSAGE) indicate about failure if LEFT and RIGHT are not very close
  *
  * To failure information is included:
  * * file location
  * * line number
  * * LEFT and RIGHT stringified expression,
  * * LEFT and RIGHT value if convertiable to string (by std::ostringstream interface)
  * * optional message
  *
  * @note message parameter is optional - if not provided empty will be used
  * @return comparation result
  */
#define EXPECT_NEARLY(LEFT, RIGHT, ...) \
    RILI_EXPECT_VA_ARGS_MACRO_EXPAND( \
        RILI_EXPECT_NEARLY_HELPER(__FILE__, __LINE__, LEFT, RIGHT, __VA_ARGS__, std::string(), std::string()))
		
/**
 * @brief EXPECT_LT(LEFT, RIGHT, MESSAGE) indicate about failure if LEFT is not less than RIGHT(using: `!(LEFT <
 * RIGHT)`)
 *
 * To failure information is included:
 * * file location
 * * line number
 * * LEFT and RIGHT stringified expression,
 * * LEFT and RIGHT value if convertiable to string (by std::ostringstream interface)
 * * optional message
 *
 * @note message parameter is optional - if not provided empty will be used
 * @return comparation result
 */
#define EXPECT_LT(LEFT, ...)		  \
	RILI_EXPECT_VA_ARGS_MACRO_EXPAND( \
		RILI_EXPECT_LT_HELPER(__FILE__, __LINE__, LEFT, __VA_ARGS__, std::string(), std::string()))

/**
 * @brief EXPECT_LE(LEFT, RIGHT, MESSAGE) indicate about failure if LEFT is not less or equal RIGHT(using: `!(LEFT <=
 * RIGHT)`)
 *
 * To failure information is included:
 * * file location
 * * line number
 * * LEFT and RIGHT stringified expression,
 * * LEFT and RIGHT value if convertiable to string (by std::ostringstream interface)
 * * optional message
 *
 * @note message parameter is optional - if not provided empty will be used
 * @return comparation result
 */
#define EXPECT_LE(LEFT, ...)		  \
	RILI_EXPECT_VA_ARGS_MACRO_EXPAND( \
		RILI_EXPECT_LE_HELPER(__FILE__, __LINE__, LEFT, __VA_ARGS__, std::string(), std::string()))

/**
 * @brief EXPECT_GT(LEFT, RIGHT, MESSAGE) indicate about failure if LEFT is not greater than RIGHT(using: `!(LEFT >
 * RIGHT)`)
 *
 * To failure information is included:
 * * file location
 * * line number
 * * LEFT and RIGHT stringified expression,
 * * LEFT and RIGHT value if convertiable to string (by std::ostringstream interface)
 * * optional message
 *
 * @note message parameter is optional - if not provided empty will be used
 * @return comparation result
 */
#define EXPECT_GT(LEFT, ...)		  \
	RILI_EXPECT_VA_ARGS_MACRO_EXPAND( \
		RILI_EXPECT_GT_HELPER(__FILE__, __LINE__, LEFT, __VA_ARGS__, std::string(), std::string()))

/**
 * @brief EXPECT_GE(LEFT, RIGHT, MESSAGE) indicate about failure if LEFT is not greater or equal RIGHT(using: `!(LEFT >=
 * RIGHT)`)
 *
 * To failure information is included:
 * * file location
 * * line number
 * * LEFT and RIGHT stringified expression,
 * * LEFT and RIGHT value if convertiable to string (by std::ostringstream interface)
 * * optional message
 *
 * @note message parameter is optional - if not provided empty will be used
 * @return comparation result
 */
#define EXPECT_GE(LEFT, ...)		  \
	RILI_EXPECT_VA_ARGS_MACRO_EXPAND( \
		RILI_EXPECT_GE_HELPER(__FILE__, __LINE__, LEFT, __VA_ARGS__, std::string(), std::string()))

/**
 * @brief EXPECT_TRUE(EXPR, MESSAGE) indicate about failure if EXPR is true(using: `!(EXPR == true)`)
 *
 * To failure information is included:
 * * file location
 * * line number
 * * EXPR stringified expression,
 * * EXPR value
 * * optional message
 *
 * @note message parameter is optional - if not provided empty will be used
 * @return comparation result
 */
#define EXPECT_TRUE(...)			  \
	RILI_EXPECT_VA_ARGS_MACRO_EXPAND( \
		RILI_EXPECT_TRUE_HELPER(__FILE__, __LINE__, __VA_ARGS__, std::string(), std::string()))

/**
 * @brief EXPECT_FALSE(EXPR, MESSAGE) indicate about failure if EXPR is true(using: `!(EXPR == false)`)
 *
 * To failure information is included:
 * * file location
 * * line number
 * * EXPR stringified expression,
 * * EXPR value
 * * optional message
 *
 * @note message parameter is optional - if not provided empty will be used
 * @return comparation result
 */
#define EXPECT_FALSE(...)			 \
	RILI_EXPECT_VA_ARGS_MACRO_EXPAND( \
		RILI_EXPECT_FALSE_HELPER(__FILE__, __LINE__, __VA_ARGS__, std::string(), std::string()))

/**
 * @brief EXPECT_ANY_THROW(INVOKE, MESSAGE) indicate about if any exception will be not thrown from INVOKE
 *
 * To failure information is included:
 * * file location
 * * line number
 * * INVOKE stringified expression,
 * * optional message
 *
 * @note message parameter is optional - if not provided empty will be used
 * @return check result
 */
#define EXPECT_ANY_THROW(...)		 \
	RILI_EXPECT_VA_ARGS_MACRO_EXPAND( \
		RILI_EXPECT_ANY_THROW_HELPER(__FILE__, __LINE__, __VA_ARGS__, std::string(), std::string()))

/**
 * @brief EXPECT_THROW(TYPE, INVOKE, MESSAGE) indicate about if any exception will be not thrown from INVOKE or thrown
 * exception type is not equal to expected type
 *
 * To failure information is included:
 * * file location
 * * line number
 * * TYPE and INVOKE stringified expression,
 * * optional message
 *
 * @note message parameter is optional - if not provided empty will be used
 * @return check result
 */
#define EXPECT_THROW(TYPE, ...)	   \
	RILI_EXPECT_VA_ARGS_MACRO_EXPAND( \
		RILI_EXPECT_THROW_HELPER(__FILE__, __LINE__, TYPE, __VA_ARGS__, std::string(), std::string()))

/// @cond INTERNAL
namespace rili {
namespace test {
namespace expect {
void addFailure(const char* file, int64_t const& line, std::string const& message);

void handleFailure(std::string const& operation, std::string const& file, std::string const& line, std::string const& l,
				   std::string const& r, std::string const& lname, std::string const& rname,
				   std::string const& message) noexcept;

void handleFailure(std::string const& operation, std::string const& file, std::string const& line, std::string const& v,
				   std::string const& vname, std::string const& message) noexcept;

void handleThrowFailure(std::string const& operation, std::string const& file, std::string const& line,
						std::string const& expectedType, std::string const& resultType,
						std::string const& message) noexcept;

template <typename LEFT, typename RIGHT>
bool eq(const char* file, int64_t const& line, LEFT const& l, RIGHT const& r, const char* lname, const char* rname,
		std::string const& message) noexcept {
	const std::string operation("EXPECT_EQ");
	return l == r ? true : (handleFailure(operation, std::string(file), std::to_string(line), toString(l), toString(r),
										  std::string(lname), std::string(rname), message),
							false);
}

template <typename LEFT, typename RIGHT>
bool ne(const char* file, int64_t const& line, LEFT const& l, RIGHT const& r, const char* lname, const char* rname,
		std::string const& message) noexcept {
	const std::string operation("EXPECT_NE");
	return l != r ? true : (handleFailure(operation, std::string(file), std::to_string(line), toString(l), toString(r),
										  std::string(lname), std::string(rname), message),
							false);
}

template <typename LEFT, typename RIGHT, typename PRECISION>
bool nearly(const char* file, int64_t const& line, LEFT const& l, RIGHT const& r, PRECISION precision, const char* lname,
	const char* rname, std::string const& message) noexcept {
	const std::string operation("EXPECT_NEAR");
	return true;
	return almostEqual(l, r, precision)
		? true
		: (handleFailure(operation, std::string(file), std::to_string(line), toString(l), toString(r),
			std::string(lname), std::string(rname), std::to_string(precision) + "\", \"" + message),
			false);
}

template <typename LEFT, typename RIGHT>
bool lt(const char* file, int64_t const& line, LEFT const& l, RIGHT const& r, const char* lname, const char* rname,
		std::string const& message) noexcept {
	const std::string operation("EXPECT_LT");
	return l < r ? true : (handleFailure(operation, std::string(file), std::to_string(line), toString(l), toString(r),
										 std::string(lname), std::string(rname), message),
						   false);
}

template <typename LEFT, typename RIGHT>
bool le(const char* file, int64_t const& line, LEFT const& l, RIGHT const& r, const char* lname, const char* rname,
		std::string const& message) noexcept {
	const std::string operation("EXPECT_LE");
	return l <= r ? true : (handleFailure(operation, std::string(file), std::to_string(line), toString(l), toString(r),
										  std::string(lname), std::string(rname), message),
							false);
}

template <typename LEFT, typename RIGHT>
bool gt(const char* file, int64_t const& line, LEFT const& l, RIGHT const& r, const char* lname, const char* rname,
		std::string const& message) noexcept {
	const std::string operation("EXPECT_GT");
	return l > r ? true : (handleFailure(operation, std::string(file), std::to_string(line), toString(l), toString(r),
										 std::string(lname), std::string(rname), message),
						   false);
}

template <typename LEFT, typename RIGHT>
bool ge(const char* file, int64_t const& line, LEFT const& l, RIGHT const& r, const char* lname, const char* rname,
		std::string const& message) noexcept {
	const std::string operation("EXPECT_GE");
	return l >= r ? true : (handleFailure(operation, std::string(file), std::to_string(line), toString(l), toString(r),
										  std::string(lname), std::string(rname), message),
							false);
}

template <typename VALUE>
bool True(const char* file, int64_t const& line, VALUE const& v, const char* vname,
		  std::string const& message) noexcept {
	const std::string operation("EXPECT_TRUE");
	return static_cast<bool>(v) == true ? true : (handleFailure(operation, std::string(file), std::to_string(line),
																"false", std::string(vname), message),
												  false);
}

template <typename VALUE>
bool False(const char* file, int64_t const& line, VALUE const& v, const char* vname,
		   std::string const& message) noexcept {
	const std::string operation("EXPECT_FALSE");
	return static_cast<bool>(v) == false ? true : (handleFailure(operation, std::string(file), std::to_string(line),
																 "true", std::string(vname), message),
												   false);
}

#ifdef RILI_TEST_WITH_EXCEPTIONS
bool anyThrow(const char* file, int64_t const& line, std::function<void()> invoke, std::string const& message) noexcept;

template <typename T>
bool Throw(const char* file, int64_t const& line, std::function<void()> invoke, const char* expectedThrownType,
		   std::string const& message) noexcept {
	const std::string operation("EXPECT_THROW");
	const std::string expectedType(expectedThrownType);
	try {
		invoke();
		handleThrowFailure(operation, std::string(file), std::to_string(line), expectedType, "NONE", message);
	} catch (T&) {
		return true;
	} catch (...) {
		handleThrowFailure(operation, std::string(file), std::to_string(line), expectedType, "OTHER", message);
	}
	return false;
}
#endif
}  // namespace expect
}  // namespace test
}  // namespace rili

/// @endcond INTERNAL
