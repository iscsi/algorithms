#include <algorithm>
#include <iterator>
#include <rili/test/BaseFixture.h>
#include <rili/test/TestStorage.h>
#include <string>
#include <utility>
#include <vector>

namespace rili {
namespace test {
void TestBaseFixture::before() {}

void TestBaseFixture::after() {}

const std::string& TestCreatorBase::fixtureName() const { return m_fixtureName; }

const std::string& TestCreatorBase::scenarioName() const { return m_scenarioName; }

const std::string& TestCreatorBase::typeName() const { return m_typeName; }

bool TestCreatorBase::operator<(const TestCreatorBase& other) const noexcept {
	return m_fixtureName + "@" + m_scenarioName + "@" + m_typeName <
		   other.m_fixtureName + "@" + other.m_scenarioName + "@" + other.m_typeName;
}

TestCreatorBase::TestCreatorBase(const std::string& fixtureName, const std::string& scenarioName,
								 std::string const& typeName)
	: m_fixtureName(fixtureName), m_scenarioName(scenarioName), m_typeName(typeName) {
	TestStorage::getInstance().registerTestCreator(*this);
}

namespace detail {
std::vector<std::string> getTypeNamesImpl(std::string const& typeNames) noexcept {
	std::vector<std::string> types;
	int bracketsCounter = 0;
	std::string currentType;
	for (auto it = typeNames.begin(); it != typeNames.end(); it++) {
		char back = 0;
		if (!currentType.empty()) {
			back = currentType.back();
		}
		switch (*it) {
			case '<': {
				bracketsCounter++;
				if (back == ' ') {
					currentType.back() = '<';
				} else {
					currentType += "<";
				}

				break;
			}
			case '>': {
				bracketsCounter--;
				if (back == ' ') {
					currentType.back() = '>';
				} else {
					currentType += ">";
				}
				break;
			}
			case ':': {
				if (back == ' ') {
					currentType.back() = ':';
				} else {
					currentType += ":";
				}
				break;
			}
			case ',': {
				if (bracketsCounter == 0) {
					types.push_back(currentType);
					currentType.clear();
				} else {
					if (back == ' ') {
						currentType.back() = ',';
					} else {
						currentType += ", ";
					}
				}
				break;
			}
			case '\t':
			case '\r':
			case '\n':
			case ' ': {
				if (back != 0 && back != '>' && back != '<' && back != ':' && back != ' ') {
					currentType += " ";
				}
				break;
			}
			default: {
				currentType += *it;
				break;
			}
		}
	}

	if (!currentType.empty()) {
		types.push_back(currentType);
	}

	return types;
}
}  // namespace detail

}  // namespace test
}  // namespace rili
