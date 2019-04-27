#include <iostream>
#include <memory>
#include <rili/test/MakeUnique.h>
#include <rili/test/BasicFormater.h>
#include <rili/test/Config.h>
#include <rili/test/EventHandler.h>
#include <string>

namespace rili {
namespace test {

EventHandler& EventHandler::getInstance() {
	static EventHandler instance;
	return instance;
}

void EventHandler::startTests() { m_formater->startTests(); }

EventHandler::EventHandler() : m_formater(rili::make_unique<BasicFormater>(std::cout)), m_currentTestFailed(false) {}

std::string EventHandler::content(const std::string& operation, const std::string& l, const std::string& r,
								  const std::string& lname, const std::string& rname, const std::string& message) {
	std::string content;
	content += operation + "(";

	if (!l.empty()) {
		content += l;
		content += "{" + lname + "}";
	} else {
		content += lname;
	}

	content += ", ";

	if (!r.empty()) {
		content += r;
		content += "{" + rname + "}";
	} else {
		content += rname;
	}

	if (!message.empty()) {
		content += ", \"" + message + "\"";
	}
	content += ")";
	return content;
}

std::string EventHandler::content(const std::string& operation, const std::string& v, const std::string& vname,
								  const std::string& message) {
	std::string content;
	content += operation + "(";

	if (!v.empty()) {
		content += v;
		content += "{" + vname + "}";
	} else {
		content += vname;
	}

	if (!message.empty()) {
		content += ", \"" + message + "\"";
	}
	content += ")";
	return content;
}

std::string EventHandler::contentOfThrow(const std::string& operation, const std::string& expectedType,
										 const std::string& resultType, const std::string& message) {
	std::string content;
	content += operation + "(" + expectedType + ", " + resultType;
	if (!message.empty()) {
		content += ", \"" + message + "\"";
	}
	content += ")";
	return content;
}

void EventHandler::failCurrentTest() { m_currentTestFailed = true; }

void EventHandler::createFailed(const std::string& reason) {
	failCurrentTest();
	m_formater->createFailed(reason);
}
void EventHandler::beforeFailed(const std::string& reason) {
	failCurrentTest();
	m_formater->beforeFailed(reason);
}

void EventHandler::runFailed(const std::string& reason) {
	failCurrentTest();
	m_formater->runFailed(reason);
}

void EventHandler::afterFailed(const std::string& reason) {
	failCurrentTest();
	m_formater->afterFailed(reason);
}

void EventHandler::startTest(const std::string& fixture, const std::string& scenario, const std::string& type) {
	m_currentTestFailed = false;
	m_formater->startTest(fixture, scenario, type);
}

void EventHandler::testDisabled(const std::string& fixture, const std::string& scenario) {
	m_formater->testDisabled(fixture, scenario);
}

void EventHandler::testSkipped(const std::string& fixture, const std::string& scenario) {
	m_formater->testSkipped(fixture, scenario);
}

bool EventHandler::endTest() {
	m_formater->endTest();
	return !m_currentTestFailed;
}

void EventHandler::endTests() { m_formater->endTests(); }

void EventHandler::expectFailed(const std::string& operation, const std::string& file, const std::string& line,
								const std::string& l, const std::string& r, const std::string& lname,
								const std::string& rname, const std::string& message) {
	expectCustomFailed(file, line, content(operation, l, r, lname, rname, message));
}

void EventHandler::expectFailed(const std::string& operation, const std::string& file, const std::string& line,
								const std::string& v, const std::string& vname, const std::string& message) {
	expectCustomFailed(file, line, content(operation, v, vname, message));
}

#ifdef RILI_TEST_WITH_EXCEPTIONS
void EventHandler::expectThrowFailed(const std::string& operation, const std::string& file, const std::string& line,
									 const std::string& expectedType, const std::string& resultType,
									 const std::string& message) {
	expectCustomFailed(file, line, contentOfThrow(operation, expectedType, resultType, message));
}
#endif

bool EventHandler::currentTestFailed() const { return m_currentTestFailed; }

void EventHandler::expectCustomFailed(const std::string& file, const std::string& line, const std::string& content) {
	m_formater->expectFailed(file, line, content);
	failCurrentTest();
}

void EventHandler::unexpectedCall(const std::string& file, const std::string& line, const void* objectId,
								  const std::string& signature, const std::string& arguments) {
	m_formater->unexpectedCall(file, line, objectId, signature, arguments);
	failCurrentTest();
}
}  // namespace test
}  // namespace rili
