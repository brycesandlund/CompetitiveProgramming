#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <cmath>
#include <map>
#include <set>

#define INF 10000000000000LL
#define EP 1e-10

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<string> vs;
typedef pair<ll, ll> ii;
typedef pair<ll, ii> iii;
typedef vector<iii> viii;
typedef vector<viii> vviii;
typedef vector<vviii> vvviii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<vvii> vvvii;

double dist(ii one, ii two) {
    return sqrt(pow(one.first - two.first, 2) + pow(one.second - two.second, 2));
}

int main() {
    ll x = 5000, y = 5000;

    vi dx, dy;
    for (ll i = 0; i < 10000; ++i) {
        for (ll j = 0; j < 10000; ++j) {
            if (abs(dist(ii(x, y), ii(i, j)) - 2018) < EP) {
                dx.push_back(i - x);
                dy.push_back(j - y);
            }
        }
    }

    ll n;
    cin >> n;

    set<ii> point;
    for (ll i = 0; i < n; ++i) {
        ll pointx, pointy;
        cin >> pointx >> pointy;
        point.insert(ii(pointx, pointy));
    }

    ll pairs = 0;
    for (auto it = point.begin(); it != point.end(); ++it) {
        x = it->first;
        y = it->second;

        for (ll i = 0; i < dx.size(); ++i) {
            if (point.count(ii(x+dx[i], y+dy[i])))
                ++pairs;
        }
    }
    cout << pairs/2 << endl;
}
