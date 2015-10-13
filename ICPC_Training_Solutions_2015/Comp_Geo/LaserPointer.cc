#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

typedef long long ll;


int main() {
    ll T;
    cin >> T;
    for (ll cs = 1; cs <= T; ++cs) {
        ll L, W, Theta;
        cin >> L >> W >> Theta;

        double height = tan(Theta/360.0 * 2*M_PI)*L;
        ll height_int = (ll)height;
        double height_frac = height - height_int;

        double short_height;
       
        if ((height_int / W) % 2 == 0) {
            short_height = height_int % W + height_frac;
        }
        else {
            short_height = W - (height_int % W + height_frac);
        }
       
        double short_dist = sqrt(short_height*short_height + L*L);
        double long_dist = sqrt(height*height + L*L);

        printf("%.3lf\n", long_dist/short_dist);
    }
    return 0;
}
