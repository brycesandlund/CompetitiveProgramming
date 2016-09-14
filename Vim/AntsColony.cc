#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;

ll log2(ll n) {
    ll j;
    for (j = 0; (1 << j) < n; ++j);
    return j;
}

void get_dist(vvii &tree, vi &dist, vi &L) {
    stack<ll> s;
    s.push(0);
    dist[0] = 0;
    L[0] = 0;
    while (!s.empty()) {
        ll cur = s.top(); s.pop();
        for (ll i = 0; i < tree[cur].size(); ++i) {
            dist[tree[cur][i].first] = dist[cur] + tree[cur][i].second;
            s.push(tree[cur][i].first);
            L[tree[cur][i].first] = L[cur]+1;
        }
    }
}

void preprocess(vvi &P, ll N) {
    for (ll j = 1; (1 << j) < N; ++j) {
        for (ll i = 0; i < N; ++i) {
            if (P[i][j-1] != -1) {
                P[i][j] = P[P[i][j-1]][j-1];
            }
        }
    }
}

ll LCA(ll p, ll q, vvi &P, vi &L, ll N) {
    if (L[p] < L[q])
        swap(p, q);

    for (ll i = log2(N)-1; i >= 0; --i) {
        if (P[p][i] != -1 && L[P[p][i]] >= L[q])
            p = P[p][i];
    }

    if (p == q)
        return p;

    for (ll i = log2(N)-1; i >= 0; --i) {
        if (P[p][i] != P[q][i]) {
            p = P[p][i], q = P[q][i];
        }
    }

    return P[p][0];
}

int main() {
    ll N;
    for (ll cs = 1; cin >> N && N; ++cs) {
        vvii tree(N);
        vvi P(N, vi(log2(N), -1));
        for (ll i = 1; i <= N-1; ++i) {
            ll Ai, Li;
            cin >> Ai >> Li;

            tree[Ai].push_back(ii(i, Li));
            P[i][0] = Ai;
        }

        vi dist(N), L(N);
        get_dist(tree, dist, L);

        preprocess(P, N);

        ll Q;
        cin >> Q;

        for (ll i = 0; i < Q; ++i) {
            ll S, T;
            cin >> S >> T;

            if (i != 0)
                cout << " ";

            ll ancestor = LCA(S, T, P, L, N);
            ll ans = dist[S] + dist[T] - dist[ancestor]*2;
            cout << ans;
        }
        cout << endl;
    }
    
    return 0;
}
