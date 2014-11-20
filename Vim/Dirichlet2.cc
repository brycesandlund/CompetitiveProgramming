#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>

#define EP 1e-10

using namespace std;

typedef vector<int> vi;
typedef long long T;

vector<int> primesToN(int n)
{
	vector<bool> sieve(n+1, true);
	vector<int> numbers;
	for (int i = 2; i <= sqrt(n)+EP; ++i)
	{
		if (sieve[i])
		{
			for (int j = i+i; j <= n; j += i)
			{
				sieve[j] = false;
			}
		}
	}

	for (int i = 2; i <= n; ++i)
	{
		if (sieve[i])
		{
			numbers.push_back(i);
		}
	}

	return numbers;
}

// returns gcd(a,b), and additionally finds x,y such that gcd(a,b) = ax + by
T egcd( T a, T b, T &x, T &y ) {
	if( a < 0 ) {
		T r = egcd(-a,b,x,y);
		x *= -1;
		return r;
	}
	if( b < 0 ) {
		T r = egcd(a,-b,x,y);
		y *= -1;
		return r;
	}
	T u = y = 0,   v = x = 1;
	while( b ) {
		T q = a/b,     r = a % b;
		  a = b,       b = r;
		T m = u,       n = v;
		  u = x - q*u, v = y - q*v;
		  x = m,       y = n;
	}
	return a;
}

// Compute x and y so that ax + by = c.
// The solution, when it exists, is unique up to the transformation
//     x -> x + kb/g
//     y -> y - ka/g
// for integers k, where g = gcd(a,b).
// The solution exists iff gcd(a,b) divides c.
// The return value is true iff the solution exists.
bool linear_diophantine( T a, T b, T c, T &x, T &y, T &g ) {
	T s,t; g = egcd(a,b,s,t);
	if( (c % g) != 0 )
		return false;
	x = c/g*s; y = c/g*t;
	return true;
}

int main()
{
    T limit = 1000000;
    
    vi primes = primesToN(limit);

    for (int caseNum = 1; true; ++caseNum)
    {
        T a, b, L, U;
        cin >> a;
        
        if (a == 0)
            break;

        cin >> b >> L >> U;

        vector<bool> indexPrime(U-L+1, true);
        
        for (size_t i = 0; i < primes.size(); ++i)
        {
            T x, y, g;

            T p = primes[i];

            if (p > sqrt(a*U+b) + EP)
                break;

            bool success = linear_diophantine(a, -p, -b, x, y, g);

            if (success)
            {
                for (T k = g*(L - x) / p; true; ++k)
                {
                    T xCur = x + k*(p/g);

                    if (xCur - L < 0)
                        continue;

                    if (xCur > U)
                        break;
                    
                    if (xCur*a + b != p)
                        indexPrime[xCur-L] = false;
                }
            }
        }

        int nPrimes = 0;        
        for (size_t i = 0; i < indexPrime.size(); ++i)
        {
            if (indexPrime[i] && a*(i+L)+b >= 2)
            {
                ++nPrimes;
            }
        }

        printf("Case %d: %d\n", caseNum, nPrimes);
    }
}
