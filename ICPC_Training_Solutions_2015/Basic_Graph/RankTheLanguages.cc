#include <iostream>
#include <cstdio>
#include <stack>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<string> vs;
typedef vector<ll> vi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef pair<ll, ll> ii;

ll dr[] = {0, 1, 0, -1};
ll dc[] = {1, 0, -1, 0};

bool myfunction(pair<ll, char> left, pair<ll, char> right) {
    if (left.first == right.first)
        return right < left;
    else
        return left < right;
}

int main() {
    ll N;
    cin >> N;
    for (ll cs = 1; cs <= N; ++cs) {
        ll H, W;

        cin >> H >> W;

        vs map(H);
        for (ll i = 0; i < H; ++i) {
            cin >> map[i];
        }

        vvb visited(H, vb(W, false));
        vi components(26, 0);
        for (ll i = 0; i < H; ++i) {
            for (ll j = 0; j < W; ++j) {
                if (!visited[i][j]) {
                    stack<ii> spots;
                    spots.push(ii(i, j));

                    while (!spots.empty()) {
                        ll r = spots.top().first;
                        ll c = spots.top().second;
                        spots.pop();

                        if (r < 0 || r >= H || c < 0 || c >= W)
                            continue;

                        if (visited[r][c] || map[r][c] != map[i][j])
                            continue;

                        visited[r][c] = true;

                        for (ll k = 0; k < 4; ++k) {
                            spots.push(ii(r + dr[k], c + dc[k]));
                        }
                    }

                    ++components[map[i][j] - 'a'];
                }
            }
        }

        vector<pair<ll, char> > languages;
        for (ll i = 0; i < 26; ++i) {
            if (components[i] != 0) {
                languages.push_back(make_pair(components[i], i + 'a'));
            }
        }

        sort(languages.rbegin(), languages.rend(), myfunction);

        printf("World #%lld\n", cs);
        for (ll i = 0; i < languages.size(); ++i) {
            printf("%c: %lld\n", languages[i].second, languages[i].first);
        }
    }
    return 0;
}
