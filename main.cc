#include "my_template.h"
#include "tools.h"
#include "number_theory.h"
#include "string_algorithms.h"
#include "segment_tree.h"

#include <exception>

void crash()
{
	int* alma = reinterpret_cast<int*>(0x42);
	*alma = 5;
}


int main(int argc, char** argv) 
{
#ifdef HOME
	if(IsDebuggerPresent())
	{
		freopen("../in.txt", "rb", stdin);
		freopen("../out.txt", "wb", stdout);
	}
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);
    cout << fixed;
#endif
	//crash();
	//gcd test
	vector<int> eInt = eulerTotientInterval(100);
	vector<bool> mInt = mobiusSieveInterval(100);
	fore(i, 1, 100)
	{
		if (eulerTotient(i) != eInt[i])
		{
			int alma = 42;
		}
	}

	try
	{
		invoke(crash);
	}
	catch (exception& e)
	{
		cout << "Standard exception: " << e.what() << endl;
	}

	int g2 = invoke(gcd, 5, 7);
	int g = gcd(5, 7);
	
	return 0;
}
