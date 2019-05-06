#pragma once
#include <my_template.h>

double performanceTest(std::function<void(uint32_t)> f, uint32_t n)
{
	using namespace std::chrono;
	auto start = steady_clock::now();
	f(n);
	return static_cast<double>( duration_cast<microseconds>(steady_clock::now() - start).count());
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


