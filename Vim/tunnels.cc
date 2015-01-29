#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef vector<bool> vb;
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

ll maxFlow(vvi &adjMatrix, ll s, ll t)
{
    memset( deg, 0, sizeof( deg ) );
    for( int u = 0; u < adjMatrix.size(); u++ )
        for( int v = 0; v < adjMatrix.size(); v++ ) if( adjMatrix[u][v] || adjMatrix[v][u] )
            adj[u][deg[u]++] = v;


    memset( cap, 0, sizeof( cap ) );

    for (ll j = 0; j < adjMatrix.size(); ++j)
    {
        for (ll k = 0; k < adjMatrix.size(); ++k)
        {
            cap[j][k] = adjMatrix[j][k];
        }
    }

    return dinic(adjMatrix.size(), s, t);
}

int main() {
    for (ll caseNum = 1; true; ++caseNum)
    {
        ll R, T;
        cin >> R >> T;

        if (R == 0 && T == 0)
            break;


        vvi adjMatrix(R+1, vi(R+1, 0));
        for (ll i = 0; i < T; ++i)
        {
            ll x, y;
            cin >> x >> y;
            
            ++adjMatrix[x][y];
            ++adjMatrix[y][x];
        }

        vi best(R+1, INF);
        vb present(R+1, true);
        ll x = 0;
        while (true)
        {
            for (ll i = 1; i < R+1; ++i)
            {
                if (present[i])
                {
                    best[i] = min(best[i], maxFlow(adjMatrix, i, 0) + x);
                }
            }

            vi remove;
            ll minVal = INF;
            for (ll i = 1; i < R+1; ++i)
            {
                if (present[i])
                {
                    if (best[i] == minVal)
                        remove.push_back(i);
                    else if (best[i] < minVal)
                    {
                        minVal = best[i];
                        remove.clear();
                        remove.push_back(i);
                    }
                }
            }

            for (ll i = 0; i < remove.size(); ++i)
            {
                if (remove[i] == 1)
                    goto END;

                present[remove[i]] = false;
            }

            for (ll i = 0; i < adjMatrix.size(); ++i)
            {
                for (ll j = 0; j < adjMatrix.size(); ++j)
                {
                    if (!present[i] || !present[j])
                    {
                        adjMatrix[i][j] = 0;
                    }
                }
            }

            x = minVal;
        }

END:
        printf("Case %lld: %lld\n\n", caseNum, best[1]);
    }
    
}
