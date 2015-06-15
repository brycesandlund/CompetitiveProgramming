#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef pair<ll, ll> ii;

int dc[] = {1, 0, -1, 0};
int dr[] = {0, 1, 0, -1};

ll n, m;

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

void getBounds(ll &minr, ll &maxr, ll &minc, ll &maxc, vvb &visited, vvb &apartment) {
    queue<ii> q;
    q.push(ii(minr, minc));

    visited[minr][minc] = true;

    while (!q.empty()) {
        ii cur = q.front();
        ll r = cur.first;
        ll c = cur.second;
        q.pop();

        if (r > maxr) {
            maxr = r;
        }
        if (r < minr) {
            minr = r;
        }
        if (c > maxc) {
            maxc = c;
        }
        if (c < minc) {
            minc = c;
        }

        for (ll k = 0; k < 4; ++k) {
            ll newr = r + dr[k];
            ll newc = c + dc[k];
        
            if (newr < 0 || newr >= n || newc < 0 || newc >= m)
                continue;

            if (apartment[newr][newc] && !visited[newr][newc]) {
                visited[newr][newc] = true;
                q.push(ii(newr, newc));
            }
        }
    }
}

ll check(ll minr, ll maxr, ll minc, ll maxc, vii &component, ll this_c) {
    ll result = -1;

    for (ll i = minr; i <= maxr; ++i) {
        for (ll j = minc; j <= maxc; ++j) {
            if (i < 0 || i >= n || j < 0 || j >= m)
                continue;

            if (component[i][j] == this_c)
                continue;

            result = max(result, component[i][j]);
        }
    }

    return result;
}

void fill(ll minr, ll maxr, ll minc, ll maxc, vii &component, ll this_c) {
    for (ll i = minr; i <= maxr; ++i) {
        for (ll j = minc; j <= maxc; ++j) {
            if (i < 0 || i >= n || j < 0 || j >= m)
                continue;

            component[i][j] = this_c;
        }
    }
}

int main() {
    cin >> n >> m;

    vvb apartment(n, vb(m));

    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < m; ++j) {
            char c;
            cin >> ws >> c;
            if (c == '.')
                apartment[i][j] = true;
            else
                apartment[i][j] = false;
        }
    }

    vvb visited(n, vb(m, false));
    vii component(n, vi(m, -1));
    vi global_minr;
    vi global_maxr;
    vi global_minc;
    vi global_maxc;

    ll this_c = 0;
    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < m; ++j) {
            if (apartment[i][j] && !visited[i][j]) {
                ll minr = i;
                ll maxr = i;
                ll minc = j;
                ll maxc = j;
                getBounds(minr, maxr, minc, maxc, visited, apartment);

                bool restart = true;
                while (restart) {
                    restart = false;
                    
                    ll other = check(minr-1, minr-1, minc-1, maxc+1);
                    other = max(other, check(maxr+1, maxr+1, minc-1, maxc+1));
                    other = max(other, check(minr-1, maxr+1, minc-1, minc-1));
                    other = max(other, check(minr-1, maxr+1, maxc+1, maxc+1));

                    fill(minr, minr, minc, maxc, component, this_c);
                    fill(maxr, maxr, minc, maxc, component, this_c);
                    fill(minr, maxr, minc, minc, component, this_c);
                    fill(minr, maxr, maxc, maxc, component, this_c);

                    if (other != -1) {
                        minr = min(minr, global_minr[other]);
                        maxr = max(maxr, global_maxr[other]);
                        minc = min(minc, global_minc[other]);
                        maxc = max(maxc, global_maxc[other]);
                        restart = true;
                    }
                }

                
            }
        }
    }

    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < m; ++j) {
            cout << (apartment[i][j] ? '.' : '*');
        }
        cout << endl;
    }

    return 0;
}
