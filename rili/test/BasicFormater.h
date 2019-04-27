#pragma once
/** @file */

#include <chrono>
#include <cstdint>
#include <rili/test/Formater.h>
#include <string>

namespace rili {
namespace test {

/**
 * @brief Default formater, which log test results similarly like gtest
 */
class BasicFormater final : public rili::test::Formater {
public:
	/**
	 * @brief Constructs BasicFromater, gven in parameter stream will be used to flush tests results
	 * @param stream
	 */
	explicit BasicFormater(std::ostream& stream);
	virtual ~BasicFormater() = default;

public:
	void testSkipped(std::string const& fixture, std::string const& scenario) noexcept override;
	void testDisabled(std::string const& fixture, std::string const& scenario) noexcept override;
	void afterFailed(const std::string& reason) noexcept override;
	void beforeFailed(const std::string& reason) noexcept override;
	void createFailed(const std::string& reason) noexcept override;
	void endTest() noexcept override;
	void endTests() noexcept override;
	void runFailed(const std::string& reason) noexcept override;
	void startTest(std::string const& fixture, std::string const& scenario, std::string const& type) noexcept override;
	void startTests() noexcept override;

public:
	void expectFailed(std::string const& file, std::string const& line, const std::string& content) noexcept override;
	void unexpectedCall(std::string const& file, std::string const& line, void const* objectId,
						const std::string& signature, const std::string& arguments) noexcept override;

private:
	std::string m_previousFixtureName;
	std::string m_currentTestName;
	bool m_failed;

	uint_fast32_t m_numberOfSucceedTests;
	uint_fast32_t m_numberOfFailedTests;
	uint_fast32_t m_numberOfDisabledTests;
	uint_fast32_t m_numberOfSkippedTests;

	typedef std::chrono::high_resolution_clock Clock;
	Clock::time_point m_testStart;
	Clock::time_point m_regressionStart;
};

}  // namespace test
}  // namespace rili
