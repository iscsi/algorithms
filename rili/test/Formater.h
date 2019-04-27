#pragma once
/** @file */

#include <ostream>
#include <string>

namespace rili {
namespace test {

/**
 * @brief The Formater class is interface which can be used to indicate about exents,
 * which occure during tests exacution.
 *
 * Using Formater as base class you can implement your own tests results output format - you can use as reference
 * rili::test::BasicFormater.
 */
class Formater {
public:
	/**
	 * @brief constructor needs stream which will be used to flust formated test results
	 * @param logStream - used to flush results
	 */
	explicit Formater(std::ostream& logStream);
	virtual ~Formater() = default;

public:
	/**
	 * @brief is called when detected that test is disabled
	 * @param fixture test fixture name
	 * @param scenario test scenario name
	 */
	virtual void testDisabled(std::string const& fixture, std::string const& scenario) noexcept = 0;
	/**
	 * @brief is called when detected that test is skipped
	 * @param fixture test fixture name
	 * @param scenario test scenario name
	 */
	virtual void testSkipped(std::string const& fixture, std::string const& scenario) noexcept = 0;
	/**
	 * @brief is called when detected exception during rili::test::TestBaseFixture::after()
	 * @param reason - reason of failure
	 */
	virtual void afterFailed(const std::string& reason) noexcept = 0;
	/**
	 * @brief is called when detected excaption during rili::test::TestBaseFixture::before()
	 * @param reason - reason of failure
	 */
	virtual void beforeFailed(const std::string& reason) noexcept = 0;
	/**
	 * @brief is called when detected exception during rili::test::TestBaseFixture construction
	 * @param reason - reason of failure
	 */
	virtual void createFailed(const std::string& reason) noexcept = 0;
	/**
	 * @brief is called when single test ended
	 */
	virtual void endTest() noexcept = 0;
	/**
	 * @brief is called when all tests ended, so no more tests will be run
	 */
	virtual void endTests() noexcept = 0;
	/**
	 * @brief is called when detected excption during rili::test::TestBaseFixture::run()
	 * @param reason - reason of failure
	 */
	virtual void runFailed(const std::string& reason) noexcept = 0;
	/**
	 * @brief is called when single test exacution is started
	 * @param fixture - test fixture name
	 * @param scenario - test scenario name
	 * @param type - test scenario type name
	 */
	virtual void startTest(std::string const& fixture, std::string const& scenario,
						   std::string const& type) noexcept = 0;
	/**
	 * @brief startTests called as first event, when staring tests execution
	 */
	virtual void startTests() noexcept = 0;

public:
	/**
	 * @brief is called on any expectation failure
	 * @param file contain expectation file
	 * @param line contain expectation line
	 * @param content contain expectation reason or description
	 */
	virtual void expectFailed(std::string const& file, std::string const& line,
							  const std::string& content) noexcept = 0;

	/**
	 * @brief is used when is detected unexpected call on mocked object
	 * @param file contain file path where mock was created
	 * @param line contain line number where mock was created
	 * @param objectId pointer to object (it `this`)
	 * @param signature stringified signature of mocked function
	 * @param arguments arguments with which mocked method was called (if argument is converitable to string)
	 */
	virtual void unexpectedCall(std::string const& file, std::string const& line, void const* objectId,
								const std::string& signature, const std::string& arguments) noexcept = 0;

protected:
	/**
	 * @brief can be used by Formater derived implementations to flush test results
	 * @return stream
	 */
	std::ostream& stream() noexcept;

private:
	Formater(Formater const& other) = delete;
	Formater& operator=(Formater const&) = delete;

private:
	std::ostream& m_stream;
};

}  // namespace test
}  // namespace rili
