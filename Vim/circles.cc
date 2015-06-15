#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#define EP 1e-12

using namespace std;

typedef long long ll;
typedef vector<double> vd;
typedef pair<double, double> dd;

dd incircle(dd a, dd b, dd c, ll A, ll B, ll C) {
    double p = A+B+C;
    double x = (A*a.first + B*b.first + C*c.first) / p;
    double y = (A*a.second + B*b.second + C*c.second) / p;
    return dd(x, y);
}

int main() {
    ll n;
    cin >> n;

    vd radii;

    for (ll i = 0; i < n; ++i) {
        ll A, B, C;
        cin >> A >> B >> C;

        double x = (double)(B*B - C*C - A*A) / (2.0*A);
        double y = sqrt(C*C - x*x);

        dd c(0, 0), b(A, 0), a(A+x, y);
        dd pt = incircle(a, b, c, A, B, C);
        radii.push_back(pt.second);
    }

    sort(radii.begin(), radii.end());
    ll counter = 1;
    ll best = 1;
    for (ll i = 1; i < n; ++i) {
        if (abs(radii[i] - radii[i-1]) < EP) {
            ++counter;
            if (counter > best) {
                best = counter;
            }
        }
        else {
            counter = 1;
        }
    }

    cout << best << endl;
}
