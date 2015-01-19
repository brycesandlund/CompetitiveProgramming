#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main()
{
    ll N;
    cin >> N;

    for (size_t caseNum = 1; caseNum <= N; ++caseNum)
    {
        ll L;
        cin >> L;

        vi train(L);

        for (size_t i = 0; i < L; ++i)
            cin >> train[i];

        ll count = 0;
        for (ll i = 1; i <= L; ++i)
        {
            for (ll j = 0; j < L; ++j)
            {
                if (train[j] == i)
                    break;

                if (train[j] > i)
                    ++count;
            }
        }

        printf("Optimal train swapping takes %lld swaps.\n", count);
    }
}
