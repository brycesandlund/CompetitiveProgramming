#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;

int dc[] = {1, 0, -1, 0};
int dr[] = {0, 1, 0, -1};

ll find(vi &UF, ll i) { return UF[i] == i ? i : UF[i] = find(UF, i); }

ll un(vi &UF, vi &size, ll i, ll j) {
    ll pi = find(UF, i);
    ll pj = find(UF, j);

    if (size[pi] > size[pj]) {
        UF[pj] = pi;
        size[pi] += size[pj];
    }
    else {
        UF[pi] = pj;
        size[pj] += size[pi];
    }
}

ll convert(ll i, ll j, ll n, ll m) {
    return i*m + j;
}

int main() {
    ll n, m;
    cin >> n >> m;

    vvb apartment(n, vb(m));
    vi UF(n*m);
    vi size(n*m, 1);
    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < m; ++j) {
            UF[convert(i, j, n, m)] = convert(i, j, n, m);
        }
    }

    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < m; ++j) {
            char c;
            cin >> ws >> c;
            if (c == '.')
                apartment[i][j] = true;
            else
                apartment[i][j] = false;

            if (apartment[i][j]) {
                for (ll k = 0; k < 4; ++k) {
                    un(UF, size, convert(i, j), convert(i+dr[k], j+dc[k]));
                }
            }
        }
    }

    vi maxr(n*m, -1);
    vi minr(n*m, -1);
    vi maxc(n*m, -1);
    vi minc(n*m, -1);

    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < m; ++j) {
            ll p = find(UF, convert(i, j));
            maxr[p] = max(maxr[p], i);
            minr[p] = min(minr[p], i);
            maxc[p] = max(maxc[p], j);
            minc[p] = min(minc[p], j);
        }
    }

    vvi component(n, vi(m, -1));
    for (ll i = 0; i < n; ++i)

    return 0;
}
