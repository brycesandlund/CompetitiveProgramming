#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>

#define INF 1000000000

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> ii;

int main() {
    for (ll cs = 1; true; ++cs) {
        ll N;
        cin >> N;

        if (N == 0)
            break;

        vvi moveMatrix(N, vi(N));
        for (ll i = 0; i < N; ++i) {
            for (ll j = 0; j < N; ++j) {
                cin >> moveMatrix[i][j];
                --moveMatrix[i][j];
            }
        }

        ll N1, N2, N3;
        cin >> N1 >> N2 >> N3;
        --N1;
        --N2;
        --N3;

        queue<ii> q;
        q.push(ii(N1, N2));
        vvi dist(N, vi(N, INF));
        dist[N1][N2] = 0;

        ll ans = -1;
        while (!q.empty()) {
            ll u = q.front().first;
            ll v = q.front().second;
            q.pop();

            if (u == N3 || v == N3) {
                ans = dist[u][v];
                break;
            }

            if (moveMatrix[u][v] != -1) {
                ll u2 = moveMatrix[u][v];
                if (dist[u][v]+1 < dist[u2][v]) {
                    dist[u2][v] = dist[u][v]+1;
                    q.push(ii(u2, v));
                }
            }

            if (moveMatrix[v][u] != -1) {
                ll v2 = moveMatrix[v][u];
                if (dist[u][v]+1 < dist[u][v2]) {
                    dist[u][v2] = dist[u][v]+1;
                    q.push(ii(u, v2));
                }
            }
        }

        printf("Game #%lld\n", cs);
        if (ans == -1)
            cout << "Destination is Not Reachable !" << endl;
        else
            printf("Minimum Number of Moves = %lld\n", ans);
        cout << endl;
    }
    return 0;
}
