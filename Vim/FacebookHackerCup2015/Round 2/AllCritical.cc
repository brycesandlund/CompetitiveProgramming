#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

#define N 25

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<double> vd;

vvi nCr(N, vi(N));

void preprocess()
{
    for (ll i = 0; i < N; ++i)
    {
        nCr[i][0] = 1;
        nCr[i][i] = 1;
    }

    for (ll i = 1; i < N; ++i)
    {
        for (ll j = 1; j < i; ++j)
        {
            nCr[i][j] = nCr[i-1][j-1] + nCr[i-1][j];
        }
    }
}

double prob(double p, ll success, ll total)
{
    return nCr[total][success] * pow(p, success) * pow(1-p, total-success);
}

int main()
{
    preprocess();

    ll T;
    cin >> T;

    for (ll caseNum = 1; caseNum <= T; ++caseNum)
    {
        double p;
        cin >> p;

        vd E(21, 0);
        for (ll i = 1; i <= 20; ++i)
        {
            double others = 0;
            for (ll j = 1; j <= i; ++j)
            {
                others += prob(p, j, i) * (1 + E[i-j]);
            }

            E[i] = (prob(p, 0, i) + others) / (1 - prob(p, 0, i));
        }

        printf("Case #%lld: %.5lf\n", caseNum, E[20]);
    }
}
