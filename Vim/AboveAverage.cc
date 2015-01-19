#include <cstdio>
#include <iostream>
#include <vector>

#define EP 1e-10

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main()
{
    ll C;
    cin >> C;

    for (ll caseNum = 1; caseNum <= C; ++caseNum)
    {
        ll N;
        cin >> N;

        vi grades(N);

        ll total = 0;
        for (ll i = 0; i < N; ++i)
        {
            cin >> grades[i];
            total += grades[i];
        }

        double average = (double)total / N;
        ll above = 0;
        for (ll i = 0; i < N; ++i)
        {
            if (grades[i] > average + EP)
            {
                ++above;
            }
        }

        printf("%.3lf%%\n", 100*(double)above/N);
    }
}
