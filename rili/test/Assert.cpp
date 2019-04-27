#include <exception>
#include <rili/test/Assert.h>
#include <rili/test/Config.h>
#include <rili/test/EventHandler.h>
#include <rili/test/InternalException.h>
#include <string>

namespace rili {
namespace test {
namespace assert {

void handleFailure(const std::string& operation, const std::string& file, const std::string& line, const std::string& l,
				   const std::string& r, const std::string& lname, const std::string& rname,
				   const std::string& message) {
	EventHandler::getInstance().expectFailed(operation, file, line, l, r, lname, rname, message);
#ifdef RILI_TEST_WITH_EXCEPTIONS
	throw detail::FailedAssertion();
#else
	std::terminate();
#endif
}

void handleFailure(const std::string& operation, const std::string& file, const std::string& line, const std::string& v,
				   const std::string& vname, const std::string& message) {
	EventHandler::getInstance().expectFailed(operation, file, line, v, vname, message);
#ifdef RILI_TEST_WITH_EXCEPTIONS
	throw detail::FailedAssertion();
#else
	std::terminate();
#endif
}

#ifdef RILI_TEST_WITH_EXCEPTIONS
void handleThrowFailure(std::string const& operation, std::string const& file, std::string const& line,
						std::string const& expectedType, std::string const& resultType, std::string const& message) {
	EventHandler::getInstance().expectThrowFailed(operation, file, line, expectedType, resultType, message);
	throw detail::FailedAssertion();
}

bool anyThrow(const char* file, const int64_t& line, std::function<void()> invoke, const std::string& message) {
	const std::string operation("ASSERT_ANY_THROW");
	try {
		invoke();
	} catch (...) {
		return true;
	}
	handleThrowFailure(operation, std::string(file), std::to_string(line), "ANY", "NONE", message);
}
#endif
}  // namespace assert
}  // namespace test
}  // namespace rili
