#pragma once
/** @file */

#include <functional>
#include <rili/test/BaseFixture.h>
#include <vector>

namespace rili {
namespace test {

/**
 * @brief The TestStorage is used to store registered tests.
 */
class TestStorage {
public:
	/**
	 * @brief is test creators storage type
	 */
	typedef std::vector<std::reference_wrapper<const TestCreatorBase>> TestInstanceCreators;
	/**
	 * @brief is iterator type, you can use it to iterate over registered test creators
	 */
	typedef TestInstanceCreators::const_iterator const_iterator;
	/**
	 * @brief is iterator type, you can use it to iterate over registered test creators
	 */
	typedef TestInstanceCreators::iterator iterator;
	/**
	 * @brief type in which is stored number of registered tests
	 */
	typedef TestInstanceCreators::size_type size_type;

public:
	/**
	 * @brief is used to get first iterator for registered test creators collection
	 * @return begin iterator
	 */
	const_iterator begin() const noexcept;
	/**
	 * @brief is used to get one after last iterator for registered test creators collection
	 * @return end iterator
	 */
	const_iterator end() const noexcept;
	/**
	 * @brief is used to get first iterator for registered test creators collection
	 * @return begin iterator
	 */
	iterator begin() noexcept;
	/**
	 * @brief is used to get one after last iterator for registered test creators collection
	 * @return end iterator
	 */
	iterator end() noexcept;
	/**
	 * @brief return number of registered test creators
	 * @return number of registered test creators
	 */
	size_type size() const noexcept;

public:
	/**
	 * @brief get or create instance of TestStorage
	 * @return instance of TestStorage
	 */
	static TestStorage& getInstance() noexcept;

	/// @cond INTERNAL
	void registerTestCreator(TestCreatorBase const& instanceCreator) noexcept;
	/// @endcond INTERNAL

private:
	TestStorage();
	TestStorage(TestStorage const& other) = delete;
	TestStorage& operator=(TestStorage const&) = delete;
	TestInstanceCreators m_storage;
};

}  // namespace test
}  // namespace rili
