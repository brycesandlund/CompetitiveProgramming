#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <cmath>

#define EP 1e-10

using namespace std;

typedef long long ll;
typedef pair<double, double> dd;
typedef vector<dd> vdd;

double cross(dd pt1, dd pt2) {
    return pt1.first*pt2.second - pt1.second*pt2.first;
}

double dist(dd pt1, dd pt2) {
    return sqrt(pow(pt1.first-pt2.first,2) + pow(pt1.second-pt2.second,2));
}

ll isLeft(dd a, dd b, dd c) {
    dd bma = dd(b.first-a.first,b.second-a.second);
    dd cma = dd(c.first-a.first,c.second-a.second);
    double z = cross(bma, cma);
    if (abs(z) < EP) return 0;
    else if (z > 0) return 1;
    else return -1;
}

double ComputePerimeter(vdd &p) {
    double perim = 0;
    for (ll i = 0; i < p.size(); ++i) {
        perim += dist(p[i], p[(i+1)%p.size()]);
    }
    return perim;
}

void ConvexHull(vdd &Z) {
    sort(Z.begin(), Z.end());
    Z.resize(unique(Z.begin(), Z.end()) - Z.begin());
    if (Z.size() < 2) return;
    vdd up, dn;
    for (ll i = 0; i < Z.size(); ++i) {
        while (up.size() > 1 && isLeft(up[up.size()-2],up.back(),Z[i]) > 0)
            up.pop_back();
        while (dn.size() > 1 && isLeft(dn[dn.size()-2],dn.back(),Z[i]) < 0)
            dn.pop_back();
        up.push_back(Z[i]);
        dn.push_back(Z[i]);
    }
    Z = dn;
    for (ll i = up.size()-2; i >= 1; --i) Z.push_back(up[i]);
}

int main() {
    ll n;
    for (ll cs = 1; cin >> n && n; ++cs) {
        vdd points(n);
        for (ll i = 0; i < n; ++i) {
            cin >> points[i].first >> points[i].second;
        }
        
        ConvexHull(points);
        points = vdd(points.rbegin(), points.rend());
        if (cs != 1) {
            printf("\n");
        }
        printf("Region #%lld:\n", cs);
        for (ll i = 0; i < points.size(); ++i) {
            printf("(%.1lf,%.1lf)-", points[i].first, points[i].second);
        }
        printf("(%.1lf,%.1lf)\n", points[0].first, points[0].second);
        printf("Perimeter length = %.2lf\n", ComputePerimeter(points));
    }
    return 0;
}
