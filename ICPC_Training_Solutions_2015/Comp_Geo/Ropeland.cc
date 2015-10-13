#include <iostream>
#include <cmath>

using namespace std;

typedef long long ll;
typedef pair<double, double> dd;

double dist(dd p1, dd p2) {
    return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}

int main() {
    ll N;
    cin >> N;
    for (ll cs = 1; cs <= N; ++cs) {
        dd A, B;
        double r;
        cin >> A.first >> A.second >> B.first >> B.second >> r;

        double AC = dist(A, dd(0, 0));
        double BC = dist(B, dd(0, 0));
        double AB = dist(A, B);
        double angle_ACB = acos((BC*BC + AC*AC - AB*AB) / (2*BC*AC)); //law of cosines

        double AD = sqrt(AC*AC - r*r);
        double BF = sqrt(BC*BC - r*r);
        
        double angle_ACD = acos(r/AC);
        double angle_BCF = acos(r/BC);
        double angle_DCF = angle_ACB - angle_ACD - angle_BCF;

        double ans;
        if (angle_DCF < 0) {
            ans = AB;
        }
        else {
            ans = AD + BF + r*angle_DCF;
        }

        printf("%.3lf\n", ans);
    }
    return 0;
}
