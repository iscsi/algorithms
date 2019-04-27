#include <rili/test/Config.h>
#include <rili/test/EventHandler.h>
#include <rili/test/Expect.h>
#include <string>

namespace rili {
namespace test {
namespace expect {

void handleFailure(const std::string& operation, const std::string& file, const std::string& line, const std::string& l,
				   const std::string& r, const std::string& lname, const std::string& rname,
				   const std::string& message) noexcept {
	EventHandler::getInstance().expectFailed(operation, file, line, l, r, lname, rname, message);
}

void handleFailure(const std::string& operation, const std::string& file, const std::string& line, const std::string& v,
				   const std::string& vname, const std::string& message) noexcept {
	EventHandler::getInstance().expectFailed(operation, file, line, v, vname, message);
}

#ifdef RILI_TEST_WITH_EXCEPTIONS
void handleThrowFailure(std::string const& operation, std::string const& file, std::string const& line,
						std::string const& expectedType, std::string const& resultType,
						std::string const& message) noexcept {
	EventHandler::getInstance().expectThrowFailed(operation, file, line, expectedType, resultType, message);
}

bool anyThrow(const char* file, const int64_t& line, std::function<void()> invoke,
			  const std::string& message) noexcept {
	const std::string operation("EXPECT_ANY_THROW");
	try {
		invoke();
		handleThrowFailure(operation, std::string(file), std::to_string(line), "ANY", "NONE", message);
		return false;
	} catch (...) {
		return true;
	}
}
#endif

void addFailure(const char* file, const int64_t& line, const std::string& message) {
	EventHandler::getInstance().expectCustomFailed(std::string(file), std::to_string(line),
												   "ADD_FAILURE(\"" + message + "\")");
}
}  // namespace expect
}  // namespace test
}  // namespace rili
