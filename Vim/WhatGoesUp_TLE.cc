#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

void printSol(ll cur, vi &parent, vi &nums)
{
    if (cur == -1)
        return;

    printSol(parent[cur], parent, nums);

    cout << nums[cur] << endl;
}

int main()
{
    vi nums;

    ll num;
    while (cin >> num)
    {
        nums.push_back(num);
    }

    vi best(nums.size(), -1);
    vi parent(nums.size());

    best[0] = 1;
    parent[0] = -1;

    for (ll i = 1; i < best.size(); ++i)
    {
        for (ll j = 0; j < i; ++j)
        {
            if (nums[j] < nums[i] && best[j] >= best[i])
            {
                best[i] = best[j]+1;
                parent[i] = j;
            }
        }
    }

    ll gBest = best[0];
    ll gBestI = 0;

    for (ll i = 0; i < best.size(); ++i)
    {
        if (best[i] >= gBest)
        {
            gBest = best[i];
            gBestI = i;
        }
    }

    cout << gBest << endl << '-' << endl;

    printSol(gBestI, parent, nums);
}
