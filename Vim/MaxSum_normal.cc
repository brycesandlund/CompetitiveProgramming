#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

int main()
{
    ll N;
    cin >> N;

    vvi grid(N, vi(N));
    for (ll i = 0; i < N; ++i)
        for (ll j = 0; j < N; ++j)
            cin >> grid[i][j];

    vvi sum(N, vi(N));

    sum[0][0] = grid[0][0];

    for (ll i = 1; i < N; ++i)
    {
        sum[0][i] = sum[0][i-1] + grid[0][i];
        sum[i][0] = sum[i-1][0] + grid[i][0];
    }

    for (ll i = 1; i < N; ++i)
    {
        for (ll j = 1; j < N; ++j)
        {
            sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
        }
    }

    for (ll rowS = 0; rowS < N; ++rowS)
    {
        for (ll rowE = rowS; rowE < N; ++rowE)
        {
            vi row(N);

            row[0] = sum[rowE][0];

            if (rowS > 0)
                row[0] -= sum[rowS-1][0];

            for (ll j = 0; j < N; ++j)
            {
                row[j] = sum[rowE][j] - sum[row
            }
        }
    }
}
