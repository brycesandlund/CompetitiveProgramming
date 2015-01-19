#include <iostream>
#include <algorithm>
#include <vector>

#define INF 1000000000

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

int main()
{
    while (true)
    {
        vvi bins(3, vi(3));
        
        for (size_t i = 0; i < 3; ++i)
            for (size_t j = 0; j < 3; ++j)
                if (!(cin >> bins[i][j]))
                    goto END;

        ll perm[] = {0, 1, 2};
        ll minCost = INF;
        string binStr = "BGC";
        string minPerm;

        do
        {
            ll curCost = 0;
            for (size_t i = 0; i < 3; ++i)
                for (size_t j = 0; j < 3; ++j)
                {
                    if (j != perm[i])
                        curCost += bins[i][j];
                }

            string curPerm = "___";
            for (size_t i = 0; i < 3; ++i)
                curPerm[i] = binStr[perm[i]];

            if (curCost < minCost || (curCost == minCost && curPerm < minPerm))
            {
                minPerm = curPerm;
                minCost = curCost;
            }
        }
        while (next_permutation(perm, perm+3));

        cout << minPerm << " " << minCost << endl;
    }

END:;
}
