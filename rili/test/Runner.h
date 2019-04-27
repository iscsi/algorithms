#pragma once
/** @file */

#include <functional>
#include <rili/test/BaseFixture.h>
#include <rili/test/TestStorage.h>
#include <string>

namespace rili {
namespace test {
namespace runner {

/**
 * @brief is enum which can be used to choose if test should run, be skipped or disabled
 */
enum class FilteringResult { Run, Skip, Disable };

/**
 * @brief is function used to filter tests by case name and scenario name.
 */
typedef std::function<FilteringResult(std::string const& fixtureName, std::string const& scenarioName)> Filter2;
/**
 * @brief is function used to filter tests by case name, scenario name and type name.
 */
typedef std::function<FilteringResult(std::string const& fixtureName, std::string const& scenarioName,
									  const std::string& typeName)>
	Filter3;

/**
 * @brief is function used to reorder tests.
 */
typedef std::function<void(rili::test::TestStorage::iterator begin, rili::test::TestStorage::iterator end)> Ordering;

/**
 * @brief defaultFilter is function used by default to filter tests - it mark as disabled these tests which case name
 * starts with"DISABLED_", otherwise mark test to run.
 */
extern Filter2 defaultFilter;

/**
 * @brief defaultOrdering is function used by default to apply order for tests - it sort them by scanario name + case
 * name + type name
 */
extern Ordering defaultOrdering;

/**
 * @brief is used to run one time all tests.
 * @param filter is function which should return if test should be run normally, marked as disabled or skipped
 * @param ordering is function used to reorder tests before run - default one will sort them by name
 * @return regression result - true if pass. false in case of any failure
 */
bool run(Filter2 const& filter = defaultFilter, Ordering const& ordering = defaultOrdering);

/**
 * @brief is used to run one time all tests.
 * @param ordering is function used to reorder tests before run - default one will sort them by name
 * @return regression result - true if pass. false in case of any failure
 */
bool run(Ordering const& ordering);

/**
 * @brief is used to run one time all tests.
 * @param filter is function which should return if test should be run normally, marked as disabled or skipped
 * @param ordering is function used to reorder tests before run - default one will sort them by name
 * @return regression result - true if pass. false in case of any failure
 */
bool run(Filter3 const& filter, Ordering const& ordering = defaultOrdering);

/**
 * @brief run single test
 * @param creator is test creator
 * @return test result - true if pass. false in case of any failure
 */
bool runSingleTest(TestCreatorBase const& creator);

}  // namespace runner
}  // namespace test
}  // namespace rili
