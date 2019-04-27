#include <algorithm>
#include <rili/test/CallHandler.h>
#include <rili/test/Config.h>
#include <rili/test/EventHandler.h>
#include <rili/test/InternalException.h>
#include <rili/test/Runner.h>
#include <rili/test/TestStorage.h>
#include <string>

namespace rili {
namespace test {
namespace runner {
Filter2 defaultFilter = [](std::string const&, std::string const& name) {
	if (name.substr(0, 9) == "DISABLED_") {
		return FilteringResult::Disable;
	} else {
		return FilteringResult::Run;
	}
};

Ordering defaultOrdering = [](rili::test::TestStorage::iterator begin, rili::test::TestStorage::iterator end) {
	std::sort(begin, end, [](std::reference_wrapper<const TestCreatorBase> const& a,
							 std::reference_wrapper<const TestCreatorBase> const& b) { return a.get() < b.get(); });
};

#ifdef RILI_TEST_WITH_EXCEPTIONS
namespace {
std::string convert(const std::exception_ptr& e) {
	try {
		std::rethrow_exception(e);
	} catch (std::exception& e) {
		return std::string("(std::exception): ") + e.what();
	} catch (...) {
		return "unknown exception";
	}
}
}  // namespace
#endif

bool runSingleTest(rili::test::TestCreatorBase const& creator) {
	auto& handler = EventHandler::getInstance();
	handler.startTest(creator.fixtureName(), creator.scenarioName(), creator.typeName());
#ifdef RILI_TEST_WITH_EXCEPTIONS
	try {
		auto test = creator.createTest();
		if (!handler.currentTestFailed()) {
			try {
				test->before();
				if (!handler.currentTestFailed()) {
					try {
						test->run();
					} catch (detail::UnexpectedCall const&) {
					} catch (detail::FailedAssertion const&) {
					} catch (...) {
						handler.runFailed(convert(std::current_exception()));
					}
					try {
						test->after();
					} catch (detail::UnexpectedCall const&) {
					} catch (detail::FailedAssertion const&) {
					} catch (...) {
						handler.afterFailed(convert(std::current_exception()));
					}
				}
			} catch (detail::UnexpectedCall const&) {
			} catch (detail::FailedAssertion const&) {
			} catch (...) {
				handler.beforeFailed(convert(std::current_exception()));
			}
		}
	} catch (detail::UnexpectedCall const&) {
	} catch (detail::FailedAssertion const&) {
	} catch (...) {
		handler.createFailed(convert(std::current_exception()));
	}
#else
	auto test = creator.createTest();
	if (!handler.currentTestFailed()) {
		test->before();
		if (!handler.currentTestFailed()) {
			test->run();
			test->after();
		}
	}
#endif
	CallHandler::getInstance().tearDown();
	return handler.endTest();
}

bool run(Filter2 const& filter, Ordering const& ordering) {
	return run([&filter](std::string const& fixtureName, std::string const& scenarioName,
						 std::string const&) { return filter(fixtureName, scenarioName); },
			   ordering);
}

bool run(Ordering const& ordering) { return run(defaultFilter, ordering); }

bool run(Filter3 const& filter, Ordering const& ordering) {
	bool regressionResult = true;
	auto& storage = rili::test::TestStorage::getInstance();

	ordering(storage.begin(), storage.end());

	EventHandler::getInstance().startTests();
	for (auto const& creator : storage) {
		switch (filter(creator.get().fixtureName(), creator.get().scenarioName(), creator.get().typeName())) {
			case FilteringResult::Run: {
				regressionResult = runSingleTest(creator.get()) ? regressionResult : false;
				break;
			}
			case FilteringResult::Disable: {
				EventHandler::getInstance().testDisabled(creator.get().fixtureName(), creator.get().scenarioName());
				break;
			}
			case FilteringResult::Skip: {
				EventHandler::getInstance().testSkipped(creator.get().fixtureName(), creator.get().scenarioName());
				break;
			}
		}
	}

	EventHandler::getInstance().endTests();
	return regressionResult;
}

}  // namespace runner
}  // namespace test
}  // namespace rili
