#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cstdio>
#include <cmath>

#define INF 1000000000
#define EP 1e-10

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

ll dist(ii one, ii two) {
    return max(abs(one.first - two.first), abs(one.second - two.second));
}

void check(unordered_map<ll, vii> &right_cubes, ll cube_idx, ii left_pt, ll &d4) {
    if (right_cubes.count(cube_idx)) {
        vii cubes = right_cubes[cube_idx];
        for (ll i = 0; i < cubes.size(); ++i) {
            d4 = min(d4, dist(left_pt, cubes[i]));
        }
    }
}

ll solve(ll left_idx, ll right_idx, vii &points) {
    if (left_idx == right_idx)
        return INF;
    else if (left_idx+1 == right_idx)
        return dist(points[left_idx], points[right_idx]);
    else {
        ll mid_idx = (left_idx + right_idx) / 2;
        ll d1 = solve(left_idx, mid_idx, points);
        ll d2 = solve(mid_idx+1, right_idx, points);
        ll d3 = min(d1, d2);
        ll cross = points[mid_idx].first;

        unordered_map<ll, vii> right_cubes;
        for (ll i = mid_idx+1; i <= right_idx; ++i) {
            if (cross + d3 < points[i].first)
                break;
            
            ll cube_idx = points[i].second/d3;
            if (!right_cubes.count(cube_idx)) {
                right_cubes[cube_idx] = vii();
            }
            right_cubes[cube_idx].push_back(points[i]);
        }

        ll d4 = d3;
        for (ll i = mid_idx; i >= left_idx; --i) {
            if (cross - d3 > points[i].first)
                break;

            ll cube_idx = points[i].second/d3;
            check(right_cubes, cube_idx, points[i], d4);
            check(right_cubes, cube_idx-1, points[i], d4);
            check(right_cubes, cube_idx+1, points[i], d4);
        }

        return d4;
    }
}

int main() {
    ll N;
    for (ll cs = 1; cin >> N; ++cs) {
        vii points(N);
        for (ll i = 0; i < N; ++i) {
            cin >> points[i].first >> points[i].second;
        }

        sort(points.begin(), points.end());
        cout << solve(0, N-1, points) << endl;
    }
}
