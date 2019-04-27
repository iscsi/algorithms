#pragma once
/** @file */

#include <rili/test/BaseFixture.h>
#include <rili/test/TestStorage.h>
#include <string>

/// @cond INTERNAL
#define RILI_TYPED_TEST_IMPL(CASE_NAME, SCENARIO_NAME)												   \
	{																									\
	public:																							 \
		riliTest##CASE_NAME##SCENARIO_NAME() : m_caseName(#CASE_NAME), m_scenarioName(#SCENARIO_NAME) {} \
		void run() override;																			 \
		std::string const& fixtureName() const noexcept override { return m_caseName; }				  \
		std::string const& scenarioName() const noexcept override { return m_scenarioName; }			 \
		virtual ~riliTest##CASE_NAME##SCENARIO_NAME() = default;										 \
																										 \
	private:																							\
		const std::string m_caseName;																	\
		const std::string m_scenarioName;																\
	};																								   \
	template <typename TypeParam>																		\
	void riliTest##CASE_NAME##SCENARIO_NAME<TypeParam>::run()
/// @endcond INTERNAL

/**
 * @brief Define test using rili::test::TestBaseFixture that can be parametrized with types. Test is using provided
 * fixture(CASE_NAME) that has to be a class template taking one template parameter.
 *
 * override rili::TestBaseFixture::run() method.
 *
 * @note all test names need to be unique (CASE_NAME + SCENARIO_NAME)
 * @hideinitializer
 */
#define TYPED_TEST_F(CASE_NAME, SCENARIO_NAME)															 \
	template <typename TypeParam>																		  \
	class riliTest##CASE_NAME##SCENARIO_NAME : public CASE_NAME<TypeParam> RILI_TYPED_TEST_IMPL(CASE_NAME, \
																								SCENARIO_NAME)

/**
 * @brief Define test using rili::test::TestBaseFixture that can be parametrized with types.
 *
 * override rili::TestBaseFixture::run() method.
 *
 * @note all test names need to be unique (CASE_NAME + SCENARIO_NAME)
 * @hideinitializer
 */
#define TYPED_TEST(CASE_NAME, SCENARIO_NAME)	   \
	typedef rili::test::TestBaseFixture CASE_NAME; \
	template <typename TypeParam>				  \
	class riliTest##CASE_NAME##SCENARIO_NAME : public CASE_NAME RILI_TYPED_TEST_IMPL(CASE_NAME, SCENARIO_NAME)

/**
 * @brief Parametrize and register multiple tests in rili::test::TestStorage. Test must be defined earlier by PARAM_TEST
 * or PARAM_TEST_F macro.
 *
 * override rili::TestBaseFixture::run() method.
 *
 * @note all test names need to be unique (CASE_NAME + SCENARIO_NAME)
 * @hideinitializer
 */
#define PARAMETERIZE_TYPED_TEST(CASE_NAME, SCENARIO_NAME, ...)							 \
	static ::rili::test::TypedTestCreator<riliTest##CASE_NAME##SCENARIO_NAME, __VA_ARGS__> \
		riliTest##CASE_NAME##SCENARIO_NAME##typedTestCreator(#CASE_NAME, #SCENARIO_NAME,   \
															 ::rili::test::getTypeNames<__VA_ARGS__>(#__VA_ARGS__));

/**
 * @brief Define and register single test in rili::test::TestStorage using provided fixture(CASE_NAME)
 *
 * override rili::TestBaseFixture::run() method.
 *
 * @note all test names need to be unique (CASE_NAME + SCENARIO_NAME)
 * @hideinitializer
 */
#define TEST_F(CASE_NAME, SCENARIO_NAME)																			  \
	class riliTest##CASE_NAME##SCENARIO_NAME : public CASE_NAME {													 \
	public:																										  \
		riliTest##CASE_NAME##SCENARIO_NAME() : CASE_NAME(), m_caseName(#CASE_NAME), m_scenarioName(#SCENARIO_NAME) {} \
		void run() override;																						  \
		std::string const& fixtureName() const noexcept override { return m_caseName; }							   \
		std::string const& scenarioName() const noexcept override { return m_scenarioName; }						  \
		virtual ~riliTest##CASE_NAME##SCENARIO_NAME() = default;													  \
																													  \
	private:																										 \
		static ::rili::test::TestCreator<riliTest##CASE_NAME##SCENARIO_NAME> m_creator;							   \
		const std::string m_caseName;																				 \
		const std::string m_scenarioName;																			 \
	};																												\
	::rili::test::TestCreator<riliTest##CASE_NAME##SCENARIO_NAME> riliTest##CASE_NAME##SCENARIO_NAME::m_creator(	  \
		#CASE_NAME, #SCENARIO_NAME);																				  \
	void riliTest##CASE_NAME##SCENARIO_NAME::run()

/**
 * @brief Define and register single test in rili::test::TestStorage using rili::test::TestBaseFixture
 *
 * override rili::TestBaseFixture::run() method.
 *
 * @note all test names need to be unique (CASE_NAME + SCENARIO_NAME)
 * @hideinitializer
 */
#define TEST(CASE_NAME, SCENARIO_NAME)			 \
	typedef rili::test::TestBaseFixture CASE_NAME; \
	TEST_F(CASE_NAME, SCENARIO_NAME)
