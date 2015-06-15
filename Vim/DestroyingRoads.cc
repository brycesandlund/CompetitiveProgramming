#include <iostream>
#include <vector>
#include <queue>

#define INF 1000000000LL

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> ii;

void bfs(ll u, vvi &adjList, ll n, vi &dist) {
    queue<ll> q;
    q.push(u);
    dist = vi(n, INF);
    dist[u] = 0;

    while (!q.empty()) {
        ll cur = q.front();
        q.pop();

        for (ll i = 0; i < adjList[cur].size(); ++i) {
            if (dist[cur]+1 < dist[adjList[cur][i]]) {
                q.push(adjList[cur][i]);
                dist[adjList[cur][i]] = dist[cur]+1;
            }
        }
    }
}

int main() {
    ll n, m;
    cin >> n >> m;

    vvi adjList(n);
    for (ll i = 0; i < m; ++i) {
        ll a, b;
        cin >> a >> b;
        --a;
        --b;
        adjList[a].push_back(b);
        adjList[b].push_back(a);
    }

    vvi dist(n, vi(n));
    for (ll i = 0; i < n; ++i) {
        bfs(i, adjList, n, dist[i]);
    }

    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < n; ++j) {
        //    cerr << i << ", " << j << " " << dist[i][j] << endl;
        }
    }

    ll s1, t1, l1, s2, t2, l2;
    cin >> s1 >> t1 >> l1 >> s2 >> t2 >> l2;
    --s1;
    --t1;
    --s2;
    --t2;

    ll shortest = INF;
    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < n; ++j) {
            ll path1A = dist[s1][i] + dist[i][j] + dist[j][t1];
            ll path1B = dist[s1][j] + dist[j][i] + dist[i][t1];
            ll path1 = min(path1A, path1B);

            ll path2A = dist[s2][i] + dist[i][j] + dist[j][t2];
            ll path2B = dist[s2][j] + dist[j][i] + dist[i][t2];
            ll path2 = min(path2A, path2B);

            ll cost = path1 + path2 - dist[i][j];

            if (path1 <= l1 && path2 <= l2) {
                shortest = min(shortest, cost);
            }
        }
    }

    if (dist[s1][t1] <= l1 && dist[s2][t2] <= l2) {
        shortest = min(shortest, dist[s1][t1] + dist[s2][t2]);
    }

    if (shortest == INF) {
        cout << -1 << endl;
    }
    else {
        cout << m - shortest << endl;
    }

    return 0;
}
