#include <algorithm>
#include <rili/test/TestStorage.h>

namespace rili {
namespace test {

TestStorage::const_iterator TestStorage::begin() const noexcept { return m_storage.begin(); }
TestStorage::const_iterator TestStorage::end() const noexcept { return m_storage.end(); }
TestStorage::iterator TestStorage::begin() noexcept { return m_storage.begin(); }
TestStorage::iterator TestStorage::end() noexcept { return m_storage.end(); }
TestStorage::size_type TestStorage::size() const noexcept { return m_storage.size(); }

TestStorage& TestStorage::getInstance() noexcept {
	static TestStorage instance;
	return instance;
}

void TestStorage::registerTestCreator(TestCreatorBase const& instanceCreator) noexcept {
	m_storage.emplace_back(std::cref(instanceCreator));
}

TestStorage::TestStorage() : m_storage() {}
}  // namespace test
}  // namespace rili
