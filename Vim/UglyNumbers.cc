#include <cstdio>
#include <iostream>
#include <set>

#define N 1500LL

using namespace std;

typedef long long ll;
typedef set<ll> si;

int main()
{
    ll count = 1;

    si uglyNums;
    uglyNums.insert(1);

    for (; count < N; ++count)
    {
        ll cur = *uglyNums.begin();

        uglyNums.insert(cur*2);
        uglyNums.insert(cur*3);
        uglyNums.insert(cur*5);

        uglyNums.erase(cur);
    }
    
    printf("The %lld'th ugly number is %lld.\n", N, *uglyNums.begin());
}
