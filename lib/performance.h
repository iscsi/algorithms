#pragma once
#include <my_template.h>

namespace performance
{
	using namespace std::chrono;
	typedef time_point<steady_clock> performancePoint;

	performancePoint now()
	{
		return steady_clock::now();
	}

	double performanceTest(std::function<void(uint32_t)> f, uint32_t n)
	{
		performancePoint start = steady_clock::now();
		f(n);
		return static_cast<double>(duration_cast<microseconds>(steady_clock::now() - start).count());
	}

	double performanceTest(std::function<void(uint32_t, performancePoint&, performancePoint&)> f, uint32_t n)
	{
		performancePoint start, end;
		f(n, start, end);
		return static_cast<double>(duration_cast<microseconds>(end - start).count());
	}

	enum class Complexity : uint8_t
	{
		Constant = 0,
		Logarithmic = 1,
		SquareRoot = 2,
		Linear = 3,
		NLogN = 4,
		NLog2N = 5,
		NSqrtN = 6,
		Square = 7,
		Cube = 8,
		PolyN = 9,
		Exponential = 10,
		Factorial = 11,
		Complexity_End = Factorial + 1,
	};

	std::function<double(uint32_t, double)> getComplexityFunction(Complexity complexity)
	{
		switch (complexity)
		{
		case performance::Complexity::Constant:
			return [](uint32_t n, double d) { return d; };
		case performance::Complexity::Logarithmic:
			return [](uint32_t n, double d) { return d / log(static_cast<double> (n) ); };
		case performance::Complexity::SquareRoot:
			return [](uint32_t n, double d) { return d / sqrt(static_cast<double> (n)); };
		case performance::Complexity::Linear:
			return [](uint32_t n, double d) { return d / n; };
		case performance::Complexity::NLogN:
			return [](uint32_t n, double d) { return d / (n * log(static_cast<double> (n))); };
		case performance::Complexity::NLog2N:
			return [](uint32_t n, double d) 
			{ 
				double ltmp = log(static_cast<double> (n));
				return d / (ltmp * ltmp); 
			};
		case performance::Complexity::NSqrtN:
			return [](uint32_t n, double d)
			{
				double tmp = sqrt(static_cast<double>(n));
				return d / (n * tmp);
			};
		case performance::Complexity::Square:
			return [](uint32_t n, double d) { return d / (n * n); };
		case performance::Complexity::Cube:
			return [](uint32_t n, double d) { return d / (n * n * n); };
		case performance::Complexity::PolyN:
			break;
		case performance::Complexity::Exponential:
			return [](uint32_t n, double d) { return log(d / n); };
		case performance::Complexity::Factorial:
			break;
		default:
			break;
		}
		return [](uint32_t n, double d) { return -1.0; };
	}

	double calculateComplexityScore(Complexity complexity, const vector<pair<uint32_t, double> >& data)
	{
		std::function<double(uint32_t, double)> f = getComplexityFunction(complexity);
		double mi = numeric_limits<double>::max();
		double mx = numeric_limits<double>::min();
		for (auto& av : data)
		{
			double tmp = f(av.first, av.second);
			umax(mx, tmp);
			umin(mi, tmp);
		}

		if(mx < 1e-9)
			return numeric_limits<double>::max();//invalid

   		double res = 0;
		for (auto& av : data)
		{
			double tmp = f(av.first, av.second) / mx;
			res += abs(1.0 - tmp);
		}
		return res;
	}

	Complexity calculateComplexity( const vector<pair<uint32_t, double> >& data)
	{	
		Complexity res = Complexity::Complexity_End;
		double bestScore = numeric_limits<double>::max();
		forn(i, Complexity::Complexity_End)
		{
			double actualScore = calculateComplexityScore(static_cast<Complexity>(i), data);
			if (actualScore < bestScore)
			{
				res = static_cast<Complexity>(i);
				bestScore = actualScore;
			}
		}
		assert(res != Complexity::Complexity_End);
		return res;
	}
}
