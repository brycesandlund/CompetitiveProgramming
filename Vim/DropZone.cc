#include <iostream>
#include <vector>

#define INF 1000000000

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<char> vc;
typedef vector<vc> vvc;

ll R, C;

struct edmondskarp_graph {
    ll N;
    vvi A;
    vvi C, F;
    edmondskarp_graph(ll _N) : N(_N), A(N), C(N,vi(N,0)), F(N,vi(N,0)) {}
    void add_capacity(ll s, ll t, ll cap) {
        if (C[s][t] == 0 && C[t][s] == 0) {
            A[s].push_back(t);
            A[t].push_back(s);
        }
        C[s][t] += cap;
        C[t][s] += cap; //undirected flows
    }
    ll Augment(vi &P) {
        ll amt = INF;
        for (ll i = 0; i < P.size()-1; ++i) amt = min(amt, C[P[i]][P[i+1]]);
        for (ll i = 0; i < P.size()-1; ++i) {
            ll u = P[i], v = P[i+1];
            C[u][v] -= amt;
            C[v][u] += amt;
            if (F[v][u] > amt) {
                F[v][u] -= amt;
            }
            else {
                F[u][v] += amt - F[v][u];
                F[v][u] = 0;
            }
        }
        return amt;
    }
    bool bfs(ll s, ll t, vi &P) {
        P = vi(N,N);
        vi Q(N); ll qh=0, qt=0;
        P[Q[qt++] = s] = s;
        while (qh < qt && P[t] == N) {
            ll c = Q[qh++];
            for (ll i = 0; i < A[c].size(); ++i) {
                ll u = A[c][i];
                if (C[c][u] == 0) continue;
                if (P[u] != N) continue;
                P[Q[qt++] = u] = c;
            }
        }
        return P[t] != N;
    }
    ll ComputeMaxFlow(ll s, ll t) {
        ll flow = 0;
        vi P;
        while (bfs(s,t,P)) {
            vi path(1,t);
            ll z = t;
            while (z != P[z]) path.push_back(z = P[z]);
            path = vi(path.rbegin(), path.rend());
            flow += Augment(path);
        }
        return flow;
    }
};

ll convert(ll r, ll c) {
    return C*(r) + c;
}

int main() {
    ll N;    
    cin >> N;
    for (ll cs = 1; cs <= N; ++cs) {
        cin >> R >> C;
        
        edmondskarp_graph G(R*C + 2);

        ll s = R*C;
        ll t = R*C+1;

        vvc board(R, vc(C));
        for (ll i = 0; i < R; ++i) {
            for (ll j = 0; j < C; ++j) {
                cin >> ws >> board[i][j];

                if (board[i][j] != 'X') {
                    if (i > 0) {
                        if (board[i-1][j] != 'X')
                            G.add_capacity(convert(i, j), convert(i-1, j), 1);
                    }
                    else {
                        G.add_capacity(convert(i, j), s, 1);
                    }
                    if (i == R-1) {
                        G.add_capacity(convert(i, j), s, 1);
                    }

                    if (j > 0) {
                        if (board[i][j-1] != 'X')
                            G.add_capacity(convert(i, j), convert(i, j-1), 1);
                    }
                    else {
                        G.add_capacity(convert(i, j), s, 1);
                    }
                    if (j == C-1) {
                        G.add_capacity(convert(i, j), s, 1);
                    }
                }
                if (board[i][j] == 'D') {
                    G.add_capacity(convert(i, j), t, INF);
                }
            }
        }

        cout << G.ComputeMaxFlow(s, t) << endl;
    }
}
