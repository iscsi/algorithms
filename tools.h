#pragma once
#include <my_template.h>
#include <lib/performance.h>

/*#include <windows.h>


//input format:
//output format:
//constraints:
//complexity:
//resource:

//Logger start

enum LOGCOLOUR
{
	GREY = 8,
	BLUE, //=FOREGROUND_BLUE,//1
	GREEN, // = FOREGROUND_GREEN,//2
	TURQUISE, // = FOREGROUND_BLUE | FOREGROUND_GREEN,
	RED, // = FOREGROUND_RED,//4
	PURPLE, //= FOREGROUND_RED | FOREGROUND_BLUE,//5
	YELLOW,// = FOREGROUND_RED | FOREGROUND_GREEN,//6,
	WHITE,//7
};

struct LOGGER
{
	std::ostringstream mOs;
	static string sLogFileName;

	LOGGER() { mOs.precision(10); }
	virtual ~LOGGER()
	{
		mOs << std::endl;
		fprintf(stderr, "%s", mOs.str().c_str());
		fflush(stderr);
		if (!sLogFileName.empty())
		{
			std::ofstream logFile;
			logFile.open(sLogFileName, std::ofstream::out | std::ofstream::app);
			logFile << mOs.str();
			logFile.close();
		}
	}
	std::ostringstream& Get(LOGCOLOUR col = WHITE)
	{
		HANDLE  hConsole = GetStdHandle(STD_ERROR_HANDLE);
		SetConsoleTextAttribute(hConsole, static_cast<int>(col));
		std::time_t t = std::time(nullptr);
		mOs << put_time(localtime(&t), "--%F %H:%M:%S - ");//__TIMESTAMP__
		//SetConsoleTextAttribute(hConsole, static_cast<int>(LOGCOLOUR::WHITE));
		return mOs;
	}
};

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define LOG(colour_, message_)                  \
    LOGGER().Get(colour_)                       \
    << __FILENAME__ << ":" << __LINE__ <<" --- " << message_;\

string LOGGER::sLogFileName("log.txt");
*/
//Logger end

//random start

std::mt19937 rng(0x15c51);

template<typename T>
T getRandom(T from, T to)
{
	std::uniform_int_distribution<T> distribution(from, to);
	return distribution(rng);
}

template<>
double getRandom(double from, double to)
{
	std::uniform_real_distribution<double> distribution(from, to);
	return distribution(rng);
}

//random end

//generate random vector Integral

template <typename T>
vector<T> generateVector(size_t _size, T from, T to)
{
	vector<T> res(_size);
	forn(i, _size)
		res[i] = getRandom<T>(from, to);
	return res;
}

/*
void generate(int seed = 0)
{
	srand(seed);
	int n = getRandom(2, 10);
	printf("%d\n", n);
	set<int> used;
	for (int i = 0; i < n; ++i) {
		int x;
		do {
			x = getRandom(1, 10);
		} while (used.count(x));
		printf("%d ", x);
		used.insert(x);
	}
	puts("");
}

void generateTree(int seed = 0)
{
	srand(seed);
	int n = getRandom(2, 20);
	printf("%d\n", n);
	for (int i = 2; i <= n; ++i)
	{
		printf("%d %d\n", getRandom(1, i - 1), i);
	}
}

void generateTree2(int seed = 0)
{
	srand(seed);
	int n = rand(2, 20);
	printf("%d\n", n);
	vector<pair<int, int>> edges;
	for (int i = 2; i <= n; ++i) {
		edges.emplace_back(rand(1, i - 1), i);
	}

	vector<int> perm(n + 1); // re-naming vertices
	for (int i = 1; i <= n; ++i) {
		perm[i] = i;
	}
	random_shuffle(perm.begin() + 1, perm.end());

	random_shuffle(edges.begin(), edges.end()); // random order of edges

	for (pair<int, int> edge : edges) {
		int a = edge.first, b = edge.second;
		if (rand() % 2) {
			swap(a, b); // random order of two vertices
		}
		printf("%d %d\n", perm[a], perm[b]);
	}
}*/

template<typename T>
struct GeometricProgression
{
	T start;
	T scale;
	GeometricProgression(T _start, T _scale):
	start(_start),
	scale(_scale){}
	T get(uint32_t n) const
	{
		T as = scale, res = start;
		while (n)
		{
			if (n)
				res *= as;
			as *= as;
			n >>= 1;
		}
		return res;
	}
	T getStart() const
	{
		return start;
	}
	T getNext(T act) const
	{
		return act * scale;
	}
};

template<typename T>
struct ArithmeticProgression
{
	T start;
	T diff;
	ArithmeticProgression(T _start, T _diff) :
		start(_start),
		diff(_diff) {}
	T get(uint32_t n) const
	{
		T ad = diff, res = start;
		while (n)
		{
			if (n)
				res += ad;
			ad *= 2;
			n >>= 1;
		}
		return res;
	}
	T getStart() const
	{
		return start;
	}
	T getNext(T act) const
	{
		return act + diff;
	}
};

