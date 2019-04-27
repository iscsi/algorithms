#pragma once
#include <cstdint>
#include <memory>
#include <rili/test/MakeUnique.h>
#include <rili/test/Config.h>
#include <rili/test/Formater.h>
#include <string>

namespace rili {
namespace test {
/// @cond INTERNAL
class EventHandler final {
public:
	static EventHandler& getInstance();
	~EventHandler() = default;

public:
	bool endTest();
	void afterFailed(const std::string& reason);
	void beforeFailed(const std::string& reason);
	void createFailed(const std::string& reason);
	void endTests();
	void runFailed(const std::string& reason);
	void startTest(std::string const& fixture, std::string const& scenario, std::string const& type);
	void testDisabled(std::string const& fixture, std::string const& scenario);
	void testSkipped(std::string const& fixture, std::string const& scenario);
	void startTests();

public:
	void expectCustomFailed(std::string const& file, std::string const& line, std::string const& content);
	void unexpectedCall(std::string const& file, std::string const& line, void const* objectId,
						std::string const& signature, std::string const& arguments);
	void expectFailed(std::string const& operation, std::string const& file, std::string const& line,
					  std::string const& l, std::string const& r, std::string const& lname, std::string const& rname,
					  std::string const& message);
	void expectFailed(std::string const& operation, std::string const& file, std::string const& line,
					  std::string const& v, std::string const& vname, std::string const& message);
#ifdef RILI_TEST_WITH_EXCEPTIONS
	void expectThrowFailed(std::string const& operation, std::string const& file, std::string const& line,
						   std::string const& expectedType, std::string const& resultType, std::string const& message);
#endif

public:
	template <typename T>
	void changeFormater(std::ostream& stream) {
		m_formater.swap(rili::make_unique<T>(stream));
	}

public:
	bool currentTestFailed() const;

private:
	EventHandler();
	EventHandler(EventHandler const& other) = delete;
	EventHandler& operator=(EventHandler const&) = delete;

private:
	std::string content(std::string const& operation, std::string const& l, std::string const& r,
						std::string const& lname, std::string const& rname, std::string const& message);
	std::string content(std::string const& operation, std::string const& v, std::string const& vname,
						std::string const& message);
	std::string contentOfThrow(std::string const& operation, std::string const& expectedType,
							   std::string const& resultType, std::string const& message);
	void failCurrentTest();

private:
	std::unique_ptr<Formater> m_formater;
	bool m_currentTestFailed;
};
/// @endcond INTERNAL
}  // namespace test
}  // namespace rili
