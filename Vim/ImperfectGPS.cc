#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <cmath>
#include <map>
#include <set>
#include <cstdio>

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
typedef pair<double, double> dd;
typedef vector<dd> vdd;

double dist(dd one, dd two) {
    return sqrt(pow(one.first - two.first, 2) + pow(one.second - two.second, 2));
}

long double distance(vdd &path) {
    long double d = 0;
    for (ll i = 1; i < path.size(); ++i) {
        d += dist(path[i], path[i-1]);
    }
    return d;
}

dd measure(vdd &point, vi time, ll spot) {
    for (ll i = 0; i < time.size(); ++i) {
        if (time[i] == spot)
            return point[i];
    }
    
    ll leg = 0;
    for (ll i = 0; i < time.size()-1; ++i) {
        if (time[i] < spot && time[i+1] > spot) {
            leg = i;
            break;
        }
    }

    double portion = (spot - time[leg])/((double) time[leg+1] - time[leg]);
    return dd(point[leg].first * (1-portion) + point[leg+1].first * portion,
            point[leg].second * (1-portion) + point[leg+1].second * portion);
}

int main() {
    ll n, t;
    cin >> n >> t;

    vdd point(n);
    vi time(n);

    for (ll i = 0; i < n; ++i) {
        cin >> point[i].first >> point[i].second >> time[i];
    }

    vdd gps;
    for (ll spot = 0; spot < time[n-1]; spot += t) {
        gps.push_back(measure(point, time, spot));
    }
    gps.push_back(point[n-1]);

    printf("%.20Lf\n", 100 * (1 - distance(gps) / distance(point)));
}
