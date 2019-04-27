#include <rili/test/Formater.h>

namespace rili {
namespace test {
Formater::Formater(std::ostream& logStream) : m_stream(logStream) {}
std::ostream& Formater::stream() noexcept { return m_stream; }
}  // namespace test
}  // namespace rili
