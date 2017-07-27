#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

struct edge{
    ll s, t;
    ll cap, flow, cost;
    ll di;
    edge *dual;
};
typedef vector<edge> ve;
typedef vector<ve> vve;
typedef pair<ll,ll> DijkP;
typedef priority_queue<DijkP, vector<DijkP>, std::greater<DijkP> > DijkPQ;

struct mcmf_graph {
    ll N; vve adj; vi pot;
    mcmf_graph(ll N) : N(N), adj(N), pot(N,0) {}
    void add_edge(ll s, ll t, ll cap, ll cost) {
        edge f, r;
        f.s = s; f.t = t; f.cap = cap; f.flow = 0; f.cost = cost;
        r.s = t; r.t = s; r.cap = 0; r.flow = 0; r.cost = -cost;
        f.di = adj[t].size(); r.di = adj[s].size();
        adj[s].push_back(f); adj[t].push_back(r);
    }
    void compile_edges() {
        for (ll v = 0; v < N; ++v)
            for (ll i = 0; i < adj[v].size(); ++i) {
                edge &e = adj[v][i];
                e.dual = &adj[e.t][e.di];
            }
    }
    ll Augment(ve &path) {
        ll push = path[0].cap;
        for (ll i = 0; i < path.size(); ++i) push = min(push, path[i].cap);
        for (ll i = 0; i < path.size(); ++i) {
            edge &e = *(path[i].dual->dual);
            e.cap -= push; e.dual->cap += push;
            if (e.dual->flow >= push) e.dual->flow -= push;
            else { e.flow += push - e.dual->flow; e.dual->flow = 0; }
        }
        return push;
    }
    void ApplyPotential(vi &delta) {
        for (ll v = 0; v < N; ++v) {
            for (ll i = 0; i < adj[v].size(); ++i) {
                adj[v][i].cost += delta[v];
                adj[v][i].dual->cost -= delta[v];
            }
            pot[v] += delta[v];
        }
    }
    void shortest_paths(ll S, ve &P, vi &W) {
        DijkPQ Q; P = ve(N); W = vi(N,0);
        for (ll i = 0; i < N; ++i) P[i].s = N; edge x; x.s = x.t = S;
        Q.push(DijkP(0,0)); ve trv; trv.push_back(x);
        while (!Q.empty()) {
            ll wt = Q.top().first; edge e = trv[Q.top().second];
            ll v = e.t; Q.pop();
            if (P[v].s != N) continue;
            W[v] = wt; P[v] = e;
            for (ll i = 0; i < adj[v].size(); ++i) {
                edge &f = adj[v][i];
                if (f.cap == 0) continue;
                Q.push(DijkP(W[v]+f.cost, trv.size()));
                trv.push_back(f);
            }
        }
    }
    ll ComputeMinCostMaxFlow(ll SRC, ll DST) {
        compile_edges();
        ll flow = 0; ve P; vi W; shortest_paths(SRC, P, W);
        while (P[DST].s != N) {
            ve ap;
            for (ll v = DST; v != SRC; v = P[v].s) ap.push_back(P[v]);
            ap = ve(ap.rbegin(), ap.rend());
            flow += Augment(ap);
            ApplyPotential(W);
            shortest_paths(SRC, P, W);
        }
        return flow;
    }
    ll Cost() {
        ll c = 0;
        for (ll v = 0; v < N; ++v) {
            for (ll i = 0; i < adj[v].size(); ++i) {
                edge &e = adj[v][i];
                c += e.flow * (e.cost - pot[e.s] + pot[e.t]);
            }
        }
        return c;
    }
};

int main() {
    ll n;
    for (ll cs = 1; cin >> n && n; ++cs) {
        ll m;
        cin >> m;

        mcmf_graph G(n+2);
        for (ll i = 0; i < m; ++i) {
            ll u, v, c;
            cin >> u >> v >> c;
            --u;
            --v;
            
            G.add_edge(u, v, 1, c);
            G.add_edge(v, u, 1, c);
        }
        G.add_edge(n, 0, 2, 0);
        G.add_edge(n-1, n+1, 2, 0);

        if (G.ComputeMinCostMaxFlow(n, n+1) == 2) {
            cout << G.Cost() << endl;
        }
        else {
            cout << "Back to jail" << endl;
        }
    }
}
