#include <rili/test/CallHandler.h>
#include <rili/test/EventHandler.h>
#include <sstream>
#include <string>
#include <utility>

namespace rili {
namespace test {

CallHandler &CallHandler::getInstance() {
	static CallHandler instance;
	return instance;
}

void CallHandler::registerCall(const void *objectInstance, const std::string &methodSignature, CallbackHolderPtr holder,
							   const std::string &file, const std::string &line, const std::string &comment) {
	m_expectations.emplace_back(objectInstance, methodSignature, std::move(holder), file, line, comment);
}

CallHandler::CallbackHolderPtr CallHandler::getCallbackHolder(const void *objectInstance,
															  const std::string &methodSignature) {
	CallHandler::CallbackHolderPtr holder(nullptr);
	if (!m_expectations.empty()) {
		auto &firstExpectation = m_expectations.front();
		if (firstExpectation.objectInstance == objectInstance && firstExpectation.methodSignature == methodSignature) {
			holder = std::move(firstExpectation.holder);
			m_expectations.pop_front();
		}
	}
	return holder;
}

void CallHandler::tearDown() {
	auto &eventHandler = EventHandler::getInstance();
	for (auto const &expectation : m_expectations) {
		eventHandler.expectCustomFailed(expectation.file, expectation.line, createComment(expectation));
	}
	m_expectations.clear();
}

CallHandler::CallHandler() : m_expectations() {}

std::string CallHandler::createComment(const CallHandler::Expectation &expectation) const {
	std::stringstream stream;
	stream << "Dangling call expectation: " << expectation.methodSignature << "{" << expectation.objectInstance << "}";
	if (!expectation.comment.empty()) {
		stream << ": " << expectation.comment;
	}
	return stream.str();
}

CallHandler::Expectation::Expectation(const void *objectInstance, const std::string &methodSignature,
									  CallHandler::CallbackHolderPtr holder, std::string file, std::string line,
									  std::string comment)
	: objectInstance(objectInstance),
	  methodSignature(methodSignature),
	  holder(std::move(holder)),
	  file(file),
	  line(line),
	  comment(comment) {}

}  // namespace test
}  // namespace rili
