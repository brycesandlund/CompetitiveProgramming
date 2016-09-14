#include <iostream>
#include <vector>

#define M_PI 3.14159265358979323846

#include <cstdio>
#include <cstdlib>

#include <cmath>
#include <iomanip>

#define INF 1000000000
#define EP 1e-10

using namespace std;

typedef long long ll;
typedef pair<double, double> ii;
typedef vector<ii> vii;

double d(double x1, double y1, double x2, double y2) {
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

double d(ii one, ii two) {
    return sqrt(pow(one.first - two.first, 2) + pow(one.second - two.second, 2));
}

double area_circ(double r) {
    return M_PI * r * r;
}

double dot(ii a, ii b) { return a.first * b.first + a.second * b.second; }
double norm(ii a) { return sqrt(dot(a, a)); }

ii ProjectPointSegment(ii a, ii b, ii c) {
    double r = d(a, b) * d(a, b);
    if (abs(r) < EP) return a;
    r = dot(ii(c.first - a.first, c.second - a.second), ii(b.first - a.first, b.second - a.second))/r;
    if (r < 0) return a;
    if (r > 1) return b;
    return ii(a.first + (b.first - a.first) * r, a.second + (b.second - a.second) * r);
}

void update(ii &max_p, ii &min_p, ii pt1, ii pt2, ii origin) {
    ii projection = ProjectPointSegment(pt1, pt2, origin);

    if (d(projection, origin) < d(min_p, origin))
        min_p = projection;

    if (d(pt1, origin) > d(max_p, origin))
        max_p = pt1;
}

int main() {
    ll n;
    ii origin;
    cin >> n >> origin.first >> origin.second;

    ii max_p = origin, min_p(INF, INF);

    vii poly(n);
    for (ll i = 0; i < n; ++i) {
        cin >> poly[i].first >> poly[i].second;
    }

    for (ll i = 0; i < n-1; ++i) {
        update(max_p, min_p, poly[i], poly[i+1], origin);
    }
    update(max_p, min_p, poly[n-1], poly[0], origin);

    cout << setprecision(20);
    double ans = area_circ(d(max_p, origin)) - area_circ(d(min_p, origin));
    cout << ans << endl;
    return 0;
}
