#include <rili/test/BasicFormater.h>
#include <string>
#include <rili/test/ConsoleColor.h>

namespace rili {
namespace test {

BasicFormater::BasicFormater(std::ostream& stream)
	: Formater(stream),
	  m_previousFixtureName(),
	  m_currentTestName(),
	  m_failed(false),
	  m_numberOfSucceedTests(0),
	  m_numberOfFailedTests(0),
	  m_numberOfDisabledTests(0),
	  m_numberOfSkippedTests(0),
	  m_testStart(Clock::now()),
	  m_regressionStart(Clock::now()) {}

void BasicFormater::testSkipped(const std::string& fixture, const std::string& scenario) noexcept {
	m_numberOfSkippedTests++;
	/*if (m_previousFixtureName != fixture && !m_previousFixtureName.empty()) {
		stream() << "[----------]" << std::endl;
	}
	stream() << "[   SKIP   ] " << fixture << "." << scenario << std::endl;*/
	m_previousFixtureName = fixture;
}

void BasicFormater::testDisabled(const std::string& fixture, const std::string& scenario) noexcept {
	m_numberOfDisabledTests++;
	if (m_previousFixtureName != fixture && !m_previousFixtureName.empty()) {
		stream() << "[----------]" << std::endl;
	}
	stream() << "[ DISABLE  ] " << fixture << "." << scenario << std::endl;
	m_previousFixtureName = fixture;
}

void BasicFormater::createFailed(std::string const& reason) noexcept {
	stream() << "  Failure at 'construction': " << reason << std::endl;
	m_failed = true;
}

void BasicFormater::beforeFailed(std::string const& reason) noexcept {
	stream() << "  Failure at 'before': " << reason << std::endl;
	m_failed = true;
}

void BasicFormater::runFailed(std::string const& reason) noexcept {
	stream() << "  Failure at 'run': " << reason << std::endl;
	m_failed = true;
}

void BasicFormater::afterFailed(std::string const& reason) noexcept {
	stream() << "  Failure at 'after': " << reason << std::endl;
	m_failed = true;
}

void BasicFormater::startTest(const std::string& fixture, const std::string& scenario,
							  const std::string& type) noexcept {
	m_currentTestName = fixture + "." + scenario;
	if (type != "") {
		m_currentTestName += "<" + type + ">";
	}
	if (m_previousFixtureName != fixture && !m_previousFixtureName.empty()) {
		stream() << "[----------]" << std::endl;
	}
	m_failed = false;
	m_testStart = Clock::now();
	m_previousFixtureName = fixture;
	stream() << "[ RUN      ] " << m_currentTestName << std::endl;
}

void BasicFormater::endTest() noexcept {
	if (m_failed) {
		stream() << "[     " << red << "FAIL" << reset << " ] " << m_currentTestName << " ["
				 << std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - m_testStart).count() << "ms]"
				 << std::endl;
		m_numberOfFailedTests++;
	} else {
		stream() << "[       " << green << "OK" << reset << " ] " << m_currentTestName << " ["
				 << std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - m_testStart).count() << "ms]"
				 << std::endl;
		m_numberOfSucceedTests++;
	}
	m_currentTestName = std::string();
	m_failed = false;
}

void BasicFormater::startTests() noexcept {
	m_failed = false;
	m_numberOfFailedTests = 0;
	m_numberOfSucceedTests = 0;
	m_numberOfDisabledTests = 0;
	m_numberOfSkippedTests = 0;
	m_regressionStart = Clock::now();
	stream() << "[==========] Tests started" << std::endl;
}

void BasicFormater::endTests() noexcept {
	auto totalTests = m_numberOfFailedTests + m_numberOfSucceedTests + m_numberOfDisabledTests + m_numberOfSkippedTests;
	stream() << "[==========]" << std::endl;
	if (m_numberOfSucceedTests > 0) {
		stream() << "[  " << green << "PASSED" << reset << "  ] " << m_numberOfSucceedTests << "/" << totalTests << std::endl;
	}

	if (m_numberOfSkippedTests > 0) {
		stream() << "[ SKIPPED  ] " << m_numberOfSkippedTests << "/" << totalTests << std::endl;
	}

	if (m_numberOfDisabledTests > 0) {
		stream() << "[ DISABLED ] " << m_numberOfDisabledTests << "/" << totalTests << std::endl;
	}

	if (m_numberOfFailedTests > 0) {
		stream() << "[  " << red << "FAILED" << reset << "  ] " << m_numberOfFailedTests << "/" << totalTests << std::endl;
	}

	m_numberOfFailedTests = 0;
	m_numberOfSucceedTests = 0;
	m_numberOfDisabledTests = 0;
	m_numberOfSkippedTests = 0;
	m_previousFixtureName.clear();
	stream() << "[==========] Tests finished in "
			 << std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - m_regressionStart).count() << "ms"
			 << std::endl;
}

void BasicFormater::expectFailed(const std::string& file, const std::string& line,
								 const std::string& content) noexcept {
	stream() << "  Failure at " << file << ":" << line << ":" << std::endl << "	" << content << std::endl;
	m_failed = true;
}

void BasicFormater::unexpectedCall(std::string const& file, std::string const& line, void const* objectId,
								   const std::string& signature, const std::string& arguments) noexcept {
	stream() << "Unexpected call :" << signature << "{" << objectId << "}" << std::endl
			 << "  * on mock defined in: " << file << ":" << line << std::endl
			 << "  * with args: " << arguments << std::endl;
	m_failed = true;
}

}  // namespace test
}  // namespace rili
