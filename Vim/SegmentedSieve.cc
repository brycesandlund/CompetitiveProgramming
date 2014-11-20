#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>

#define EP 1e-10

using namespace std;

typedef vector<int> vi;
typedef long long LL;

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

vector<bool> segSieve(LL start, LL end)
{
    vector<int> primes = primesToN((int)(sqrt(end)+EP));

    vector<bool> sieve(end-start+1, true);
    
    if (start <= 1)
        sieve[0] = false;

    if (start == 0)
        sieve[1] = false;

    for (int i = 0; i < (int)primes.size(); ++i)
    {
        for (LL j = primes[i] * max((start + primes[i]-1)/primes[i], 2LL); j <= end; j += primes[i])
        {
            sieve[j-start] = false;
        }
    }

    return sieve;

    /*vector<ll> numbers;
    for (int i = 0; i < sieve.size(); ++i)
    {
        numbers.push_back(sieve[i]+start);
    }

    return numbers;
    */
}

long long mult_mod(long long a, long long b, long long m) {
    long long q;
    long long r;
    asm(
            "mulq %3;"
            "divq %4;"
            : "=a"(q), "=d"(r)
            : "a"(a), "rm"(b), "rm"(m));
    return r;
}

/* Computes a^b mod m. Assumes 1 <= m <= 2^62-1 and 0^0=1.
 * The return value will always be in [0, m) regardless of the sign of a.
 */
long long pow_mod(long long a, long long b, long long m) {
    if (b == 0) return 1 % m;
    if (b == 1) return a < 0 ? a % m + m : a % m;
    long long t = pow_mod(a, b / 2, m);
    t = mult_mod(t, t, m);
    if (b % 2) t = mult_mod(t, a, m);
    return t >= 0 ? t : t + m;
}

/* A deterministic implementation of Miller-Rabin primality test.
 * This implementation is guaranteed to give the right result for n < 2^64
 * by using a 7-number magic base.
 * Alternatively, the base can be replaced with the first 12 prime numbers
 * (prime numbers <= 37) and still working correctly.
 */
bool is_prime(long long n) {
    long long small_primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (int i = 0; i < 12; ++i)
        if (n > small_primes[i] && n % small_primes[i] == 0)
            return false;
    long long base[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    long long d = n - 1;
    int s = 0;
    for (; d % 2 == 0; d /= 2, ++s);
    for (int i = 0; i < 7; ++i) {
        long long a = base[i] % n;
        if (a == 0) continue;
        long long t = pow_mod(a, d, n);
        if (t == 1 || t == n - 1) continue;
        bool found = false;
        for (int r = 1; r < s; ++r) {
            t = pow_mod(t, 2, n);
            if (t == n - 1) {
                found = true;
                break;
            }
        }
        if (!found)
            return false;
    }
    return true;
}


int main()
{
    LL lower = 10;
    LL upper = 50;
    vector<bool> sieve = segSieve(10, 50);
    for (LL i = lower; i <= upper; ++i)
    {
        if (sieve[i-lower])
            cout << i << endl;
    }

    lower = 999999000000;
    upper = 1000000000000LL;
    vector<bool> sieve2 = segSieve(lower, upper);

    int nPrimes = 0;
    for (LL i = lower; i <= upper; ++i)
    {
        if (sieve2[i-lower])
            ++nPrimes;
    }

    cout << nPrimes << endl;

    nPrimes = 0;

    for (LL i = lower; i <= upper; ++i)
    {
        if (is_prime(i))
            ++nPrimes;
    }

    cout << nPrimes << endl;

    /*vector<int> primes = primesToN((int)(sqrt(upper)+EP));
    
    nPrimes = 0;
    for (LL i = lower; i <= upper; ++i)
    {
        bool isPrime = true;
        for (size_t j = 0; j < primes.size(); ++j)
        {
            if (i % primes[j] == 0)
            {
                isPrime = false;
                break;
            }
        }

        if (isPrime)
            ++nPrimes;
    }

    cout << nPrimes << endl;*/
}
