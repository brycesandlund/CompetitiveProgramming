#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

#define NN 51
const int INF = 2000000000;

int cap[NN][NN], deg[NN], adj[NN][NN];

int q[NN], par[NN];
int dinic( int n, int s, int t ) {
    int flow = 0;
    while( true ) {
        memset( par, -1, sizeof( par ) );
        int qf = 0, qb = 0;
        par[q[qb++] = s] = -2;
        while ( qb > qf && par[t] == -1 )
            for ( int u = q[qf++], i = 0, v; i < deg[u]; i++ )
                if( par[v = adj[u][i]] == -1 && cap[u][v] )
                    par[q[qb++] = v] = u;
        if ( par[t] == -1) break;
        for ( int z = 0; z < n; z++ ) if( cap[z][t] && par[z] != -1 ) {
            int bot = cap[z][t];
            for ( int v = z, u = par[v]; u >= 0; v = u, u = par[v] )
                bot = min(bot, cap[u][v]);
            if ( !bot ) continue;
            cap[z][t] -= bot;
            cap[t][z] += bot;
            for ( int v = z, u = par[v]; u >= 0; v = u, u = par[v] ) {
                cap[u][v] -= bot;
                cap[v][u] += bot;
            }
            flow += bot;
        }
    }

    return flow;
}

vi memo;

ll solve(ll u, vi &flow)
{
    if (u == 0)
        return INF;

    if (memo[u] != -1)
        return memo[u];

    memo[u] = 0;

    ll maxChild = -1;
    for (ll i = 0; i < deg[u]; ++i)
    {
        maxChild = max(maxChild, solve(adj[u][i], flow));
    }

    return memo[u] = min(flow[u], maxChild);
}

int main() {
    for (ll caseNum = 1; true; ++caseNum)
    {
        ll R, T;
        cin >> R >> T;

        if (R == 0 && T == 0)
            break;

        if (caseNum != 1)
            printf("\n");

        vvi adjMatrix(R+1, vi(R+1, 0));
        for (ll i = 0; i < T; ++i)
        {
            ll x, y;
            cin >> x >> y;
            
            ++adjMatrix[x][y];
            ++adjMatrix[y][x];
        }

        memset( deg, 0, sizeof( deg ) );
        for( int u = 0; u < R+1; u++ )
            for( int v = 0; v < R+1; v++ ) if( adjMatrix[u][v] || adjMatrix[v][u] )
                adj[u][deg[u]++] = v;

        vi flow(R+1);
        for (ll i = 1; i < R+1; ++i)
        {
            memset( cap, 0, sizeof( cap ) );

            for (ll j = 0; j < R+1; ++j)
            {
                for (ll k = 0; k < R+1; ++k)
                {
                    cap[j][k] = adjMatrix[j][k];
                }
            }

            flow[i] = dinic(R+1, i, 0);
        }

        memo = vi(R+1, -1);

        printf("Case %lld: %lld\n", caseNum, solve(1, flow));
    }
    
}
