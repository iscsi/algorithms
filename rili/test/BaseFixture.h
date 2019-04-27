#pragma once
/** @file */

#include <memory>
#include <rili/test/MakeUnique.h>
#include <rili/test/EventHandler.h>
#include <string>
#include <vector>

namespace rili {
namespace test {
/**
 * @brief The TestBaseFixture class is base class for test fixture used directly by TEST macro
 * and indirect by TEST_F because TestBaseFixture must be base class for use provided fixture
 */
class TestBaseFixture {
public:
	/**
	 * @brief will be run as preconditional for test
	 * @note you can override it in your fixture if you have special preconditions for your test
	 */
	virtual void before();
	/**
	 * @brief should contain test body - will be provided by TEST_F or TEST
	 */
	virtual void run() = 0;
	/**
	 * @brief will be run after test
	 * @note you can use it to check test post conditions
	 * @note you can use it to release resources aquired in before() or run() and preform teardowns
	 */
	virtual void after();

public:
	TestBaseFixture() = default;
	virtual ~TestBaseFixture() = default;
	/**
	 * @brief used to get test fixture name
	 *
	 * **example:**
	 * ```
	 * TEST(XYZ, ABC)
	 * {
	 *	 std::cout << fixtureName() << std::endl;
	 * }
	 * // will print "XYZ"
	 * ```
	 * @return fixture name as string
	 */
	virtual std::string const& fixtureName() const noexcept = 0;
	/**
	 * @brief used to get test scenario name
	 *
	 * **example:**
	 * ```
	 * TEST(XYZ, ABC)
	 * {
	 *	 std::cout << scenarioName() << std::endl;
	 * }
	 * // will print "ABC"
	 * ```
	 * @return scenario name as string
	 */
	virtual std::string const& scenarioName() const noexcept = 0;

private:
	TestBaseFixture(TestBaseFixture const& other) = delete;
	TestBaseFixture& operator=(TestBaseFixture const&) = delete;
};

/// @cond INTERNAL
class TestCreatorBase {
public:
	typedef std::unique_ptr<TestBaseFixture> TestPtr;
	virtual TestPtr createTest() const = 0;
	virtual ~TestCreatorBase() = default;
	std::string const& fixtureName() const;
	std::string const& scenarioName() const;
	std::string const& typeName() const;
	bool operator<(TestCreatorBase const& other) const noexcept;

protected:
	TestCreatorBase(std::string const& fixtureName, std::string const& scenarioName, std::string const& typeName = "");

private:
	TestCreatorBase(TestCreatorBase const& other) = delete;
	TestCreatorBase& operator=(TestCreatorBase const&) = delete;

private:
	const std::string m_fixtureName;
	const std::string m_scenarioName;
	const std::string m_typeName;
};

template <typename TestType>
class TestCreator final : public TestCreatorBase {
public:
	TestPtr createTest() const override { return rili::make_unique<TestType>(); }
	TestCreator(std::string const& fixtureName, std::string const& scenarioName)
		: TestCreatorBase(fixtureName, scenarioName) {}
};

namespace detail {
std::vector<std::string> getTypeNamesImpl(std::string const& typeNames) noexcept;
}  // namespace detail

template <typename... Ts>
inline std::vector<std::string> getTypeNames(std::string const& typeNames) noexcept {
	auto result = detail::getTypeNamesImpl(typeNames);
	if (result.size() != sizeof...(Ts)) {
		EventHandler::getInstance().expectCustomFailed(
			__FILE__, std::to_string(__LINE__),
			"This is rili::Test internal error, which should never happen. Please report it to maintainers");
		std::terminate();
	}
	return result;
}

template <template <typename> class TestType, typename... Ts>
class TypedTestCreator;

template <template <typename> class TestType, typename T1, typename... Ts>
class TypedTestCreator<TestType, T1, Ts...> final : public TestCreatorBase {
public:
	TestPtr createTest() const override { return rili::make_unique<TestType<T1>>(); }
	TypedTestCreator(std::string const& fixtureName, std::string const& scenarioName,
					 std::vector<std::string> const& typeNames)
		: TestCreatorBase(fixtureName, scenarioName, typeNames[typeNames.size() - sizeof...(Ts)-1]),
		  m_creator(fixtureName, scenarioName, typeNames) {}

private:
	::rili::test::TypedTestCreator<TestType, Ts...> m_creator;
};

template <template <typename> class TestType, typename T1>
class TypedTestCreator<TestType, T1> final : public TestCreatorBase {
public:
	TestPtr createTest() const override { return rili::make_unique<TestType<T1>>(); }
	TypedTestCreator(std::string const& fixtureName, std::string const& scenarioName,
					 std::vector<std::string> const& typeNames)
		: TestCreatorBase(fixtureName, scenarioName, typeNames.back()) {}
};

/// @endcond INTERNAL
}  // namespace test
}  // namespace rili
