#include <rili/test/Config.h>
#include <rili/test/InternalException.h>
#include <rili/test/MockDefinitions.h>

namespace rili {
namespace test {
namespace mock {
#ifdef RILI_TEST_WITH_EXCEPTIONS
[[noreturn]] void onUnexpectedCall() { throw detail::UnexpectedCall(); }
#else
[[noreturn]] void onUnexpectedCall() { std::terminate(); }
#endif
}  // namespace mock
}  // namespace test
}  // namespace rili
