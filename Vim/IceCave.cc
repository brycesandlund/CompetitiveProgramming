#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef long long ll;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef pair<ll, ll> ii;

int dc[] = {1, 0, -1, 0};
int dr[] = {0, 1, 0, -1};

int main() {
    ll n, m;
    cin >> n >> m;

    vvb cracked(n, vb(m));
    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < m; ++j) {
            char c;
            cin >> ws >> c;
            if (c == '.')
                cracked[i][j] = false;
            else
                cracked[i][j] = true;
        }
    }

    ll r1, c1;
    cin >> r1 >> c1;
    --r1;
    --c1;

    ll r2, c2;
    cin >> r2 >> c2;
    --r2;
    --c2;

    queue<ii> q;
    q.push(ii(r1, c1));
    
    cracked[r1][c1] = false;
    
    bool reachable = false;
    vvb visited(n, vb(m, false));
    while (!q.empty()) {
        ll r = q.front().first;
        ll c = q.front().second;
        q.pop();

        if (r < 0 || r >= n || c < 0 || c >= m)
            continue;

        if (r == r2 && c == c2) {
            reachable = true;
            break;
        }

        if (cracked[r][c])
            continue;

        if (visited[r][c])
            continue;

        visited[r][c] = true;

        for (ll i = 0; i < 4; ++i) {
            q.push(ii(r + dr[i], c + dc[i]));
        }
    }
    

    ll stableBorders = 0;
    for (ll i = 0; i < 4; ++i) {
        ll r = r2 + dr[i];
        ll c = c2 + dc[i];

        if (r < 0 || r >= n || c < 0 || c >= m)
            continue;

        if (!cracked[r][c])
            ++stableBorders;
    }

    bool possible = false;
    if (reachable) {
        if (cracked[r2][c2])
            possible = true;
        else if (stableBorders >= 2 || (r1 == r2 && c1 == c2 && stableBorders >= 1))
            possible = true;
    }

    if (possible)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

    return 0;
}
