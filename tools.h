#include <windows.h>
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
