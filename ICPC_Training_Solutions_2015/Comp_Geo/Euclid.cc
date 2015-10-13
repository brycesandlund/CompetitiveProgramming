#include <iostream>
#include <cstdio>
#include <cmath>

#define EP .000001

using namespace std;

typedef long long ll;
typedef pair<double, double> dd;

double cross(dd pt1, dd pt2) {
    return pt1.first*pt2.second - pt1.second*pt2.first;
}

double cross(dd a, dd b, dd c) {
    dd amb(a.first-b.first, a.second-b.second);
    dd cmb(c.first-b.first, c.second-b.second);
    return cross(amb, cmb);
}

void readp(dd &p) {
    cin >> p.first >> p.second;
}

bool zero(dd p) {
    return p.first == 0 && p.second == 0;
}

int main() {
    for (ll cs = 1; true; ++cs) {
        dd A, B, C, D, E, F;
        readp(A);
        readp(B);
        readp(C);
        readp(D);
        readp(E);
        readp(F);

        if (zero(A) && zero(B) && zero(C) && zero(D) && zero(E) && zero(F))
            break;

        double tri_area = abs(cross(D, E, F) / 2);

        double lo = 0, hi = 1000000000000.0;
        double GX = 0, GY = 0, HX = 0, HY = 0;
        bool first = true;
        while (true) {
            double mid = (hi+lo)/2;
            double HX_new = mid*C.first + (1-mid)*A.first;
            double HY_new = mid*C.second + (1-mid)*A.second;
            double GX_new = B.first + (HX_new-A.first);
            double GY_new = B.second + (HY_new-A.second);

            if (!first && abs(HX_new - HX) < EP && abs(HY_new - HY) < EP
                    && abs(GX_new - GX) < EP && abs(GY_new - GY) < EP) {
                break;
            }
            first = false;
            HX = HX_new;
            HY = HY_new;
            GX = GX_new;
            GY = GY_new;

            dd H(HX, HY);

            double quad_area = abs(cross(H, A, B));

            if (quad_area > tri_area) {
                hi = mid;
            }
            else {
                lo = mid;
            }
        }

        printf("%.3lf %.3lf %.3lf %.3lf\n", GX, GY, HX, HY);
    }
    return 0;
}
