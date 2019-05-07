#pragma once
#include <my_template.h>

namespace performance
{
	using namespace std::chrono;

	double performanceTest(std::function<void(uint32_t, time_point<steady_clock>&, time_point<steady_clock>&)> f, uint32_t n)
	{
		time_point<steady_clock> start, end;
		f(n, start, end);
		return static_cast<double>(duration_cast<microseconds>(end - start).count());
	}

	enum Complexity {
		Constant,
		Logarithmic,
		SquareRoot,
		Linear,
		NLogN,
		NLog2N,
		NSqrtN,
		Square,
		Cube,
		PolyN,
		Exponential,
		Factorial
	};

	double calculateScore(const vector<double>& v)
	{	//input is normalized
		double res = 0;
		forn(i, v.size())
			res += (v[i] - 1)*(v[i] - 1);
		return res;
	}
}
