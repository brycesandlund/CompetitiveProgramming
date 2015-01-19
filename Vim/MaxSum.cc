#include <iostream>
#include <vector>

#define INF 1000000000LL

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

int main()
{
    ll N;
    cin >> N;

    vvi grid(N+1, vi(N+1, 0));
    for (ll i = 1; i < N+1; ++i)
        for (ll j = 1; j < N+1; ++j)
            cin >> grid[i][j];

    vvi sum(N+1, vi(N+1, 0));

    for (ll i = 1; i < N+1; ++i)
    {
        for (ll j = 1; j < N+1; ++j)
        {
            sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + grid[i][j];
        }
    }

    ll maxGrid = -INF;
    for (ll rowS = 1; rowS < N+1; ++rowS)
    {
        for (ll rowE = rowS; rowE < N+1; ++rowE)
        {
            vi row(N, 0);

            for (ll j = 1; j < N+1; ++j)
            {
                row[j-1] = sum[rowE][j] - sum[rowE][j-1] - sum[rowS-1][j] + sum[rowS-1][j-1];
            }

            ll maxSum = row[0];
            ll diff = row[0];
            for (ll i = 1; i < N; ++i)
            {
                diff = max(diff, 0LL) + row[i];
                maxSum = max(maxSum, diff); 
            }

            maxGrid = max(maxGrid, maxSum);
        }
    }

    cout << maxGrid << endl;
}
