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

list<LL> primes(list<LL> nums, )
{
    vector<int> primes = primesToN((int)(sqrt(nums.back())+EP));


    vector<bool> sieve(end-start+1, true);

    if (nums.front() == 0)
        nums.erase(nums.begin());

    if (nums.front() == 1)
        nums.erase(nums.begin());    

    for (int i = 0; i < (int)primes.size(); ++i)
    {
        


        for (LL j = primes[i] * max(start/primes[i] + 1, 2LL); j <= end; j += primes[i])
        {
            sieve[j-start] = false;
        }
    }

    return sieve;
}

int main()
{
    for (int caseNum = 1; true; ++caseNum)
    {
        LL a, b, L, U;
        cin >> a;
        
        if (a == 0)
            break;

        cin >> b >> L >> U;
        vector<bool> sieve = segmentedSieve(a*L + b, a*U + b);
        
        //cout << "here" << endl;

        int nPrimes = 0;
        for (LL n = L; n <= U; ++n)
        {
            LL tn = a*n + b;

            //cout << tn << endl;
            //cout << (tn - (a*L + b)) << endl;
            //cout << sieve[(tn - (a*L + b))] << endl;

            if (sieve[tn - (a*L + b)])
            {
                ++nPrimes;
            }
        }

        printf("Case %d: %d\n", caseNum, nPrimes);
    }
}
