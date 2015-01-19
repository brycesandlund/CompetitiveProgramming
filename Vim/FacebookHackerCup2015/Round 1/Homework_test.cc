#include <iostream>
#include <cstdio>

using namespace std;

typedef long long ll;

int main()
{
    cout << 100 << endl;

    for (ll i = 0; i < 100; ++i)
    {
        ll A = 0, B = 10000001;

        ll K = rand()%100;

        printf("%lld %lld %lld\n", A, B, K);
    }    
}
