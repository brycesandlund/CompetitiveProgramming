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

void fill(ll minr, ll maxr, ll minc, ll maxc, vvb &apartment) {
    for (ll i = minr; i <= maxr; ++i) {
        for (ll j = minc; j <= maxc; ++j) {
            apartment[i][j] = true;
        }
    }
}

int main() {
    ll n, m;
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
    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < m; ++j) {
            if (apartment[i][j] && !visited[i][j]) {
                queue<ii> q;
                q.push(ii(i, j));

                visited[i][j] = true;

                ll minr = i;
                ll maxr = i;
                ll minc = j;
                ll maxc = j;

                while (!q.empty()) {
                    ii cur = q.front();
                    ll r = cur.first;
                    ll c = cur.second;
                    q.pop();

                    if (r > maxr) {
                        maxr = r;
                        fill(maxr, maxr, minc, maxc, apartment);
                    }
                    if (r < minr) {
                        minr = r;
                        fill(minr, minr, minc, maxc, apartment);
                    }
                    if (c > maxc) {
                        maxc = c;
                        fill(minr, maxr, maxc, maxc, apartment);
                    }
                    if (c < minc) {
                        minc = c;
                        fill(minr, maxr, minc, minc, apartment);
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
