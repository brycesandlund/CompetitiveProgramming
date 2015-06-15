#include <iostream>
#include <set>
#include <vector>
#include <map>

#define M 1000000009

using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;
typedef pair<ll, ii> iii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef vector<bool> vb;

ll dx[] = {-1, 0, 1};

bool removable(ll x, ll y, set<ii> &positions) {
    bool success = true;
    for (ll i = 0; i < 3; ++i) {
        if (positions.count(ii(x+dx[i], y+1))) {
            bool okay = false;
            for (ll j = 0; j < 3; ++j) {
                ll reach_x = x+dx[i]+dx[j];
                if (reach_x == x)
                    continue;
                if (positions.count(ii(reach_x, y)))
                    okay = true;
            }
            if (!okay)
                success = false;
        }
    }

    return success;
}

int main() {
    ll m;
    cin >> m;

    set<ii> positions;
    map<ii, ll> pos_to_num;
    set<ll> q;
    vii num_to_pos(m);

    for (ll i = 0; i < m; ++i) {
        ll x, y;
        cin >> x >> y;

        positions.insert(ii(x, y));
        pos_to_num[ii(x, y)] = i;
        num_to_pos[i] = ii(x, y);
    }

    for (ll i = 0; i < m; ++i) {
        ii cur_pos = num_to_pos[i];
        if (removable(cur_pos.first, cur_pos.second, positions)) {
            q.insert(i);
        }
    }

    vi moves(m);
    for (ll i = 0; i < m; ++i) {
        ll cur_num;
        ii cur_pos;
        ll cur_x;
        ll cur_y;
        while (true) {
            if (i % 2 == 0) {
                cur_num = *q.rbegin();
            }
            else {
                cur_num = *q.begin();
            }
            cur_pos = num_to_pos[cur_num];
            cur_x = cur_pos.first;
            cur_y = cur_pos.second;

            q.erase(cur_num);
            if (removable(cur_x, cur_y, positions))
                break;
        }

        moves[i] = cur_num;
        positions.erase(cur_pos);

        for (ll j = 0; j < 3; ++j) {
            if (positions.count(ii(cur_x+dx[j], cur_y-1))) {
                if (removable(cur_x+dx[j], cur_y-1, positions)) {
                    q.insert(pos_to_num[ii(cur_x+dx[j], cur_y-1)]);
                }
            }
        }
    }

    /*for (ll i = 0; i < m; ++i) {
        cerr << moves[i] << endl;
    }
    cerr << endl;*/

    ll ans = 0;
    ll power = 1;
    for (ll i = m-1; i >= 0; --i) {
        ans = (ans + moves[i] * power) % M;
        power = (power * m) % M;
    }

    cout << ans << endl;

    return 0;
}
