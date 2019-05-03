#include <rili/test/Main.h>
#include <rili/Test.h>

int rili::test::main(int argc, char* argv[])
{
	setvbuf(stdout, nullptr, _IONBF, 0);
	rili::test::runner::Filter2 filter = [&](std::string const&, std::string const& name)
	{
		if (name.substr(0, 9) == "DISABLED_") {
			return rili::test::runner::FilteringResult::Disable;
		}
		if (argc <= 1 || name == argv[1]) {
			return rili::test::runner::FilteringResult::Run;
		}
		else {
			return rili::test::runner::FilteringResult::Skip;
		}
	};
	return rili::test::runner::run(filter) ? 0 : 1;
}