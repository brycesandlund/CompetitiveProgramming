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

void push(priority_queue<iii, vector<iii>, greater<iii> > &pq, vvi &cost, ll i, ll j, ll newCost) {
    if (newCost < cost[i][j]) {
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
                ll fwd = cur.second.first;
                ll bwd = cur.second.second;

                if (curCost > cost[fwd][bwd]) continue;

                if (fwd == 1 && bwd == 1) break;

                // extend either the forward or backward path only
                for (ll i = 0; i < N; ++i) {
                    ll newCost = curCost + dist[fwd][i];
                    push(pq, cost, i, bwd, newCost);
                }
                for (ll i = 0; i < N; ++i) {
                    ll newCost = curCost + dist[i][bwd];
                    push(pq, cost, fwd, i, newCost);
                }
                
                // utilize the path in the same direction from fwd to bwd
                // either swaping the two positions, or moving to one of them
                if (fwd != bwd) {    
                    push(pq, cost, bwd, fwd, curCost+dist[fwd][bwd]-1);
                //    push(pq, cost, bwd, bwd, curCost+dist[fwd][bwd]-1);
                    push(pq, cost, fwd, fwd, curCost+dist[fwd][bwd]-1);
                }
            }

            printf("Minimum number of nodes = %lld\n", cost[1][1]);
        }

        printf("\n");
    }
}
