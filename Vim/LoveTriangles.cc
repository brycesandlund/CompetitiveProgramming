#include <iostream>
#include <vector>
#include <stack>

#define M 1000000007

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;


ll n, m;

bool satisfiable(vvii &adjList, ll start, vi &status) {
    stack<ll> q;
    q.push(start);
    status[start] = 0;
    while (!q.empty()) {
        //cerr << "here" << endl;
        ll u = q.top();
        q.pop();

        for (ll i = 0; i < adjList[u].size(); ++i) {
            ll v = adjList[u][i].first;
            if (status[v] == -1) {
                status[v] = (status[u] ^ (!adjList[u][i].second));
                q.push(v);
            }
            else if (status[v] != (status[u] ^ (!adjList[u][i].second))) {
                return false;
            }
        }
    }
    return true;
}

bool countComponents(ll &nComponents, vvii &adjList) {
    vi status(n, -1);
    nComponents = 0;
    for (ll i = 0; i < n; ++i) {
        if (status[i] == -1) {
            if (!satisfiable(adjList, i, status))
                return false;
            ++nComponents;
        }
    }
    return true;
}

int main() {
    cin >> n >> m;

    vvii adjList(n);
    for (ll i = 0; i < m; ++i) {
        ll u, v, l;
        cin >> u >> v >> l;
        --u;
        --v;
        adjList[u].push_back(ii(v, l));
        adjList[v].push_back(ii(u, l));
    }

    ll nComponents = 0;
    ll ans;
    if (countComponents(nComponents, adjList)) {
        ans = 1;
        for (ll i = 0; i < nComponents-1; ++i) {
            ans = (ans * 2) % M;
        }
    }
    else
        ans = 0;

    cout << ans << endl;

    return 0;
}
