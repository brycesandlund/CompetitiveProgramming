#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

int main() {
    ll n, m;
    cin >> n >> m;

    vvi children(n);
    vi parent(n, -1);

    for (ll i = 0; i < m; ++i) {
        ll p, q;
        cin >> p >> q;
        --p; --q;
        children[p].push_back(q);
        parent[q] = p;
    }

    vi depth(n);
    queue q;
    for (ll i = 0; i < n; ++i) {
        if (parent[i] == -1) {
            q.push(i);
            depth[i] = 0;
        }
    }

    while (!q.empty()) {
        ll cur = q.front();
        q.pop();

        for (ll i = 0; i < children[cur].size(); ++i) {
            depth[children[cur][i]] = depth[cur] + 1;
            q.push(children[cur][i]);
        }
    }

    vii depthchild(n);
    for (ll i = 0; i < n; ++i) {
        depthchild[i] = ii(depth[i], i);
    }
    
    sort(depthchild.begin(), depthchild.end());

    vi list
    for (ll i = 0; i < n; ++i) {
        
    }
}
