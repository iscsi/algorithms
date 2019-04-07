
int gcd(int a, int b)
{
	return b ? gcd(b, a%b) : a;
}

int gcd2(int a, int b)
{
	int c;
	while (b)
	{
		a %= b;
		c = a;
		a = b;
		b = c;
	}
	return a;
}

//ax+by = gcd(a,b)
int gcdExtended(int a, int b, int& x, int& y)
{
	if (a == 0)
	{
		x = 0;
		y = 1;
		return b;
	}
	int x1, y1;
	int g = gcdExtended(b%a, a, x1, y1);

	// Update x and y using results of recursive 
	// call 
	x = y1 - (b / a) * x1;
	y = x1;

	return g;
}

//https://codeforces.com/blog/entry/53925
//mobius function nu(p^k)=[k==0]-[k==1]

vector<bool> mobiusSieveInterval(int n)
{
	vector<bool> res(n + 1,true);
	for (int i = 2; i*i <= n; ++i) if(res[i])
	{
		int j = 2*i;
		while (j <= n)
		{
			res[j] = false;
			j += i;
		}
	}
	return res;
}

//Euler totient function fi(p^k) = p^k-p^(k-1)
//http://e-maxx.ru/algo/euler_function

int eulerTotient(int n) {
	int result = n;
	for (int i = 2; i*i <= n; ++i)
	{
		if (n % i == 0)
		{
			while (n % i == 0)
				n /= i;
			result -= result / i;
		}
	}
	if (n > 1)
		result -= result / n;
	return result;
}


vector<int> eulerTotientInterval(int n)
{
	vector<int> res(n + 1, 1);
	for (int i = 2; i <= n; ++i) if (res[i] == 1)
	{
		int j = i;
		while (j <= n)
		{
			res[j] *= i-1;
			j += i;
		}
		int64_t k = static_cast<int64_t>(i)*i;
		while (k <= n)
		{
			int64_t m = k;
			while (m <= n)
			{
				res[m] *= i;
				m += k;
			}
			k *= i;
		}
	}
	return res;
}


//\sum_{i:1..n}\sum_{j:1..n}[gcd(i,j)==1]

int64_t coPrimePairs(int n)
{
	vector<bool> mobiusFunc = mobiusSieveInterval(n);
	int64_t res = static_cast<int64_t>(n) * n;
	fore(i, 2, n) if(mobiusFunc[i])
	{
		int64_t tmp = (n / i);
		res -= tmp * tmp;
	}
	return res;
}

//\sum_{i:1..n}\sum_{j:1..n} gcd(i,j)==1

int64_t sumGcdOfPairs(int n)
{
	vector<int> eulerTotient = eulerTotientInterval(n);
	int64_t res = static_cast<int64_t>(n) * n;
	fore(i, 2, n) 
	{
		int64_t tmp = (n / i);
		res += tmp * tmp * eulerTotient[i];
	}
	return res;
}


//\sum_{i:1..n}\sum_{j:1..n} lcm(i,j)==1

int64_t sumLcmOfPairs(int n)
{
	vector<int> eulerTotient = eulerTotientInterval(n);
	int64_t res = static_cast<int64_t>(n) * n;
	fore(i, 2, n)
	{
		int64_t tmp = (n / i);
		int64_t tmp2 = (tmp * (1 + tmp) / 2);
		res += tmp2 * tmp2 * eulerTotient[i];
	}
	return res;
}
