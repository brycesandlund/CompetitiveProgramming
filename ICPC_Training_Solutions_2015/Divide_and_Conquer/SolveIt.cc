#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

typedef long long ll;

ll p, q, r, s, t, u;

double f(double x) {
    return p*exp(-x) + q*sin(x) + r*cos(x) + s*tan(x) + t*x*x + u;
}

int main() {
    for (ll cs = 1; cin >> p >> q >> r >> s >> t >> u; ++cs) {
        double lo = 0, hi = 1;
        while (hi > lo + 1e-10) {
            double x = (hi+lo)/2;

            if (f(x) < 0)
                hi = x;
            else
                lo = x;
        }

        if (fabs(f(lo) - 0) < 1e-5) {
            printf("%.4lf\n", lo);
        }
        else {
            cout << "No solution" << endl;
        }
    }
    
    return 0;
}
