#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>

#define INF 1e10

using namespace std;

typedef long long ll;
typedef pair<double, double> dd;
typedef vector<dd> vdd;

double d(dd pt1, dd pt2) {
    return sqrt(pow(pt1.first - pt2.first, 2) + pow(pt1.second - pt2.second, 2));
}

double dot(dd a, dd b) { return a.first*b.first + a.second*b.second; }

double pt_line_d(dd c, dd a, dd b) {
    double r = d(a,b)*d(a,b);
    dd cma = dd(c.first - a.first, c.second - a.second);
    dd bma = dd(b.first - a.first, b.second - a.second);
    r = dot(cma, bma)/r;
    dd pt;
    if (r < 0) pt = a;
    else if (r > 1) pt = b;
    else pt = dd(a.first + bma.first*r, a.second + bma.second*r);
    return d(c, pt);
}

void fill(vdd &pts, ll n) {
    for (ll i = 0; i < n; ++i) {
        cin >> pts[i].first >> pts[i].second;
    }
}

double check(vdd &pts1, ll n1, vdd &pts2, ll n2) {
    double min_dist = INF;
    for (ll i = 0; i < n1; ++i) {
        for (ll j = 0; j < n2; ++j) {
            ll jp1 = (j+1)%n2;
            min_dist = min(min_dist, pt_line_d(pts1[i], pts2[j], pts2[jp1]));
        }
    }
    return min_dist;
}

int main() {
    ll T;
    cin >> T;

    for (ll cs = 1; cs <= T; ++cs) {
        ll ni;
        cin >> ni;
        vdd inner(ni);
        fill(inner, ni);

        ll no;
        cin >> no;
        vdd outer(no);
        fill(outer, no);

        double ans = min(check(inner, ni, outer, no), check(outer, no, inner, ni));
        printf("%.6lf\n", ans/2);
    }
    return 0;
}
