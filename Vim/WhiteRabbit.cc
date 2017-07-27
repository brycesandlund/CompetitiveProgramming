#include <iostream>
#include <vector>
#include <map>

#define MOD 13
#define INF 1000000000

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef pair<ll, ll> ii;

ll egcd(ll a, ll b, ll &x, ll &y) {
    if (a < 0) {
        ll r = egcd(-a,b,x,y);
        x *= -1;
        return r;
    }
    if (b < 0) {
        ll r = egcd(a,-b,x,y);
        y *= -1;
        return r;
    }
    ll u = y = 0, v = x = 1;
    while (b) {
        ll q = a/b, r = a%b;
        a = b, b = r;
        ll m = u, n = v;
        u = x - q*u, v = y - q*v;
        x = m, y = n;
    }
    return a;
}

ll modinv(ll a, ll n) {
    ll x, y, g = egcd(a, n, x, y);
    if (g != 1) return -1;
    x %= n;
    if (x < 0) x += n;
    //cerr << "inverse of " << a << " mod 13 is " << x << endl;
    return x;
}

void GaussJordan(vvi &A) {
    ll m = A.size(), n = A[0].size();
    ll pj = 0;
    for (ll k = 0; k < m; ++k) {
        ll pi = k;
        while (pj < n) {
            for (ll i = k; i < m; ++i) if (A[i][pj] > A[pi][pj]) pi = i;
            if (A[pi][pj] != 0) {
                if (pi != k) {
                    swap(A[pi], A[k]);
                    pi = k;
                }
                break;
            }
            for (ll i = k; i < m; ++i) A[i][pj] = 0;
            ++pj;
        }
        if (pj == n) break;
        ll s = modinv(A[pi][pj], MOD);
        for (ll j = pj; j < n; ++j) A[pi][j] = (A[pi][j] * s) % MOD;
        for (ll i = 0; i < m; ++i) if (i != pi) {
            ll a = A[i][pj];
            for (ll j = pj; j < n; ++j) A[i][j] = (A[i][j] - a*A[pi][j] + MOD*MOD) % MOD;
        }
        ++pj;
    }
}

ll SolveLinearSystems(vvi &A, vvi &b, vvi &x, vb &has_sol) {
    ll m = A.size(), n = A[0].size(), q = b[0].size();
    vvi M = A;
    for (ll i = 0; i < m; ++i) for (ll j = 0; j < q; ++j) M[i].push_back(b[i][j]);
    GaussJordan(M);

    x = vvi(n, vi(q, 0));
    ll i = 0, jz = 0;
    while (i < m) {
        while (jz < n && M[i][jz] == 0) ++jz;
        if (jz == n) break;
        for (ll k = 0; k < q; ++k) x[jz][k] = M[i][n+k];
        ++i;
    }
    ll kerd = n - i;
    has_sol = vb(q,true);
    while (i < m) {
        for (ll k = 0; k < q; ++k) if (M[i][n+k] != 0) has_sol[k] = false;
        ++i;
    }
    return kerd;
}

ll getPathIdx(map<ii, ll> &pathToIdx, ll start, ll end) {
    ii path(min(start, end), max(start, end));
    if (!pathToIdx.count(path)) {
        ll size = pathToIdx.size();
        pathToIdx[path] = size;
    }
    return pathToIdx[path];
}

int main() {
    ll N, A, R, T;
    cin >> N >> A >> R >> T;
    --A; --R;

    map<ii, ll> pathToIdx;
    vvi trip(T);
    vvi b(T, vi(1, 0));

    for (ll i = 0; i < T; ++i) {
        ll d, p;
        cin >> d >> p;

        b[i][0] = d;

        trip[i] = vi(p);
        for (ll j = 0; j < p; ++j) {
            cin >> trip[i][j];
            --trip[i][j];
        }

        for (ll j = 0; j < p-1; ++j) {
            getPathIdx(pathToIdx, trip[i][j], trip[i][j+1]);
        }
    }
    
    ll M = pathToIdx.size();
    vvi matrix(T, vi(M, 0));
    vvi x(M, vi(1));

    for (ll i = 0; i < T; ++i) {
        for (ll j = 0; j < trip[i].size()-1; ++j) {
            matrix[i][getPathIdx(pathToIdx, trip[i][j], trip[i][j+1])]++;
        }
    }

    for (ll i = 0; i < T; ++i) {
        for (ll j = 0; j < M; ++j) {
            matrix[i][j] %= MOD;
        }
    }

    vb has_sol(T);
    SolveLinearSystems(matrix, b, x, has_sol);

    vvi dist(N, vi(N, INF));
    for (ll i = 0; i < N; ++i) {
        for (ll j = i+1; j < N; ++j) {
            if (pathToIdx.count(ii(i, j))) {
                dist[i][j] = dist[j][i] = x[getPathIdx(pathToIdx, i, j)][0];
            }
        }
    }

    for (ll i = 0; i < N; ++i)
        dist[i][i] = 0;

    for (ll k = 0; k < N; ++k) {
        for (ll i = 0; i < N; ++i) {
            for (ll j = 0; j < N; ++j) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    cout << dist[A][R] << endl;
}
