#include <iostream>
#include <vector>
#include <queue>

#define INF 1000000000

using namespace std;

typedef long long ll;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<ll> vi;

ll n, m;

ll bfs(vvb &adj_matrix) {
    queue<ll> q;
    q.push(0);

    vi dist(n, INF);
    dist[0] = 0;

    while (!q.empty()) {
        ll u = q.front();
        q.pop();

        if (u == n-1)
            break;

        for (ll i = 0; i < n; ++i) {
            if (adj_matrix[u][i] && dist[u]+1 < dist[i]) {
                q.push(i);
                dist[i] = dist[u]+1;
            }
        }
    }

    return dist[n-1];
}

int main() {
    cin >> n >> m;

    vvb adj_matrix(n, vb(n, false));
    vvb adj_matrix_inv(n, vb(n, true));

    for (ll i = 0; i < m; ++i) {
        ll u, v;
        cin >> u >> v;
        --u;
        --v;

        adj_matrix[u][v] = true;
        adj_matrix[v][u] = true;
        adj_matrix_inv[u][v] = false;
        adj_matrix_inv[v][u] = false;
    }

    ll railroad = bfs(adj_matrix);
    ll road = bfs(adj_matrix_inv);

    ll ans = max(railroad, road);

    if (ans == INF)
        cout << -1 << endl;
    else
        cout << ans << endl;
    
    return 0;
}
