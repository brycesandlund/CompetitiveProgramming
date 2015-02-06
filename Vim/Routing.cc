#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

#define INF 1000000000LL

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> ii;
typedef pair<ll, ii> iii;

void push(priority_queue<iii, vector<iii>, greater<iii> > &pq, vvi &dist, vvi &cost, ll start, ll end, ll i, ll j, ll curCost) {
    ll newCost = curCost + dist[end][i] + dist[j][start] + dist[i][j] - 1;

    if (newCost < cost[i][j] && (i != start && i != end && j != start && j != end)) {
        cost[i][j] = newCost;
        pq.push(iii(newCost, ii(i, j)));
    } 
}

int main() {
    for (ll cs = 1; true; ++cs) {
        ll N, M;
        cin >> N >> M;

        if (N == 0 && M == 0) break;

        vvi dist(N, vi(N, INF));

        for (ll i = 0; i < M; ++i) {
            ll X, Y;
            cin >> X >> Y;
            --X; --Y;
            dist[X][Y] = 1;
        }

        for (ll i = 0; i < N; ++i)
            dist[i][i] = 0;

        for (ll k = 0; k < N; ++k)
            for (ll i = 0; i < N; ++i)
                for (ll j = 0; j < N; ++j)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

        printf("Network %lld\n", cs);
        if (dist[0][1] == INF || dist[1][0] == INF) {
            printf("Impossible\n");
        }
        else {
            priority_queue<iii, vector<iii>, greater<iii> > pq;
            pq.push(iii(1, ii(0, 0)));

            vvi cost(N, vi(N, INF));
            while (true) {
                iii cur = pq.top(); pq.pop();

                ll curCost = cur.first;
                ll start = cur.second.first;
                ll end = cur.second.second;

                if (curCost > cost[start][end]) continue;

            //    cerr << start << " " << end << " " << curCost << endl;
                cost[start][end] = curCost;

                if (start == 1 && end == 1) break;

                for (ll i = 0; i < N; ++i) {
                    for (ll j = 0; j < N; ++j) {
                        push(pq, dist, cost, start, end, i, j, curCost);
                    }
                }
            }

            printf("Minimum number of nodes = %lld\n", cost[1][1]);
        }

        printf("\n");
    }
}
