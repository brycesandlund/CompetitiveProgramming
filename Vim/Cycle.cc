#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

int main() {
    ll n, m;
    cin >> n >> m;

    vvi adjlist(n);
    for (ll i = 0; i < m; ++i) {
        ll u, v;
        cin >> u >> v;
        adjlist[u].add(v);
        adjlist[v].add(u);
    }

    ll t;
    ll w;
    if (m == 0) {
        t = 3;
        w = (n*(n-1)*(n-2)) / 6;
    }
    else {
        ll nPathsL2 = 0;
        for (ll i = 0; i < n; ++i) {
            if (adjList[i].size() > 1) {
                nPathsL2 += adjList[i].size()*(adjList[i].size()-1) / 2;
            }
        }

        if (nPathsL2 > 0) {
            t = 1;
            w = nPathsL2;
        }
        else {
            t = 2;
            w = m * ((n-2)*(n-3)/2);
        }
    }

    cout << t << " " << w << endl;

    return 0;
}
