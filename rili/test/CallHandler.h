#pragma once
#include <list>
#include <memory>
#include <rili/test/CallbackHolder.h>
#include <string>
/// @cond INTERNAL
namespace rili {
namespace test {
class CallHandler {
public:
	typedef std::unique_ptr<UniversalCallbackHolder> CallbackHolderPtr;
	static CallHandler& getInstance();
	void registerCall(void const* objectInstance, std::string const& methodSignature, CallbackHolderPtr holder,
					  std::string const& file, std::string const& line, std::string const& comment);
	CallbackHolderPtr getCallbackHolder(void const* objectInstance, std::string const& methodSignature);
	void tearDown();

private:
	CallHandler();
	struct Expectation {
		Expectation(void const* objectInstance, std::string const& methodSignature, CallbackHolderPtr holder,
					std::string file, std::string line, std::string comment);
		void const* objectInstance;
		std::string methodSignature;
		CallbackHolderPtr holder;
		std::string file;
		std::string line;
		std::string comment;
	};
	std::string createComment(Expectation const&) const;

	typedef std::list<Expectation> Expectations;
	Expectations m_expectations;
};
}  // namespace test
}  // namespace rili
/// @endcond INTERNAL
