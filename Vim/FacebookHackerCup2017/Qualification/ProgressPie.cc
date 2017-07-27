#include <iostream>
#include <cmath>

#define EP 1e-10

using namespace std;

typedef long long ll;

int main() {
    ll T;
    cin >> T;
    for (ll cs = 1; cs <= T; ++cs) {
        ll P, X, Y;
        cin >> P >> X >> Y;

        X -= 50;
        Y -= 50;
        double angle = atan2(Y, X);
        double new_angle = M_PI*2 - (angle - M_PI/2);
        if (new_angle > 2*M_PI) {
            new_angle -= 2*M_PI;
        }

        bool success = false;
        double angle_p = new_angle / (2 * M_PI) * 100;
        if (angle_p-EP <= P) {
            double r = sqrt(X*X + Y*Y);

            if (r-EP <= 50) {
                success = true;
            }
        }

        if (success)
            printf("Case #%lld: black\n", cs);
        else
            printf("Case #%lld: white\n", cs);
    }
}
