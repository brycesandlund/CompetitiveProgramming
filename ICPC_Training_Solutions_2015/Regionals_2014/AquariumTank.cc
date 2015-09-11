#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<double> vd;
typedef pair<ll, ll> ii;
typedef pair<double, double> dd;
typedef vector<dd> vdd;
typedef vector<ii> vii;

ll N, D, L;

double cross(dd one, dd two) {
    return one.first*two.second - one.second*two.first;
}

double ComputeArea(const vdd &p) {
    double area = 0;
    for (ll i = 0; i < p.size(); ++i) {
        ll z = (i+1) % p.size();
        area += cross(p[i], p[z]);
    }
    return fabs(area / 2.0);
}

dd point_on_mid(dd p1, dd p2, double mid) {
    double height = p2.second - p1.second;
    double small_height = mid - p1.second;
    double width = p2.first - p1.first;
    double scale = small_height / height;
    double small_width = width * scale;
    return dd(p1.first+small_width, mid);
}

double get_volume(vdd &points, double mid) {
    vdd new_points;
    for (ll i = 0; i < N; ++i) {
        if (points[i].second <= mid) {
            new_points.push_back(points[i]);
        }
        
        ll ip1 = (i+1)%N;
        if (points[i].second <= mid && points[ip1].second >= mid) {
            new_points.push_back(point_on_mid(points[i], points[ip1], mid));
        }

        if (points[ip1].second <= mid && points[i].second >= mid) {
            new_points.push_back(point_on_mid(points[i], points[ip1], mid));
        }
    }

    double area = ComputeArea(new_points);
    return area*D*.001;
}

int main() {
    for (ll cs = 1; cin >> N; ++cs) {
        cin >> D >> L;

        vdd points(N);
        double max_y = 0;
        for (ll i = 0; i < N; ++i) {
            cin >> points[i].first >> points[i].second;
            max_y = max(max_y, points[i].second);
        }
        
        double lo = 0, hi = max_y;
        while (hi - lo > .00001) {
            double mid = (lo + hi) / 2;
            
            double volume = get_volume(points, mid);
            if (volume > L)
                hi = mid;
            else
                lo = mid;
        }

        printf("%.2lf\n", lo);
    }
    return 0;
}
