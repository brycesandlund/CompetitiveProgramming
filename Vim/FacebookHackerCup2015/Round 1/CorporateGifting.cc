#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

#define INF 1000000000000000000LL

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

vi bestSum;
vi bestGift;
vi secondSum;
vvi tree;

void process(ll node)
{
    if (tree[node].size() == 0)
    {
        bestSum[node] = 1;
        bestGift[node] = 1;
        secondSum[node] = 2;
    }
    else
    {
        ll total = 0;
        vi complement(tree[node].size()+3, 0);
        for (ll i = 0; i < tree[node].size(); ++i)
        {
            total += bestSum[tree[node][i]];

            if (bestGift[tree[node][i]] < complement.size())
            {
                complement[bestGift[tree[node][i]]] -= bestSum[tree[node][i]];
                complement[bestGift[tree[node][i]]] += secondSum[tree[node][i]];
            }
        }

        ll minimum = INF;
        ll minGift;
        ll secondMin = INF;
        for (ll me = 1; me <= tree[node].size()+2; ++me)
        {
            ll cur = total + complement[me] + me;

            if (cur < minimum)
            {
                secondMin = minimum;
                minimum = cur;
                minGift = me;
            }
            else if (cur < secondMin)
            {
                secondMin = cur;
            }
        }

        bestSum[node] = minimum;
        bestGift[node] = minGift;
        secondSum[node] = secondMin;
    }
}

void processAll()
{
    vi q;

    q.push_back(0);

    for (ll i = 0; i < q.size(); ++i)
    {
        for (ll j = 0; j < tree[q[i]].size(); ++j)
        {
            q.push_back(tree[q[i]][j]);
        }
    }

    for (ll i = q.size()-1; i >= 0; --i)
    {
        process(q[i]);
    }
}

int main()
{
    ll T;
    cin >> T;

    for (ll caseNum = 1; caseNum <= T; ++caseNum)
    {
        ll N;
        cin >> N;

        bestSum = vi(N);
        bestGift = vi(N);
        secondSum = vi(N);
        tree = vvi(N);

        for (ll i = 0; i < N; ++i)
        {
            ll parent;
            cin >> parent;

            if (parent != 0)
                tree[parent-1].push_back(i);
        }

        processAll();

        for (ll i = 0; i < N; ++i)
        {
            if (bestSum[i] <= 0)
                cerr << "best sum negative" << endl;
        }
        printf("Case #%lld: %lld\n", caseNum, bestSum[0]);
    }
}
