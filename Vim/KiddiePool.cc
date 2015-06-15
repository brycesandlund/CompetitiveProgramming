#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

#define EP 1e-6

using namespace std;

typedef long long ll;
typedef vector<double> vd;

ll N;
double V, X;

double getNum(vd &x, vd &R, vd &C) {
    double num = 0;
    for (ll i = 0; i < N; ++i) {
        num += R[i]*x[i]*C[i];
    }

    return num;
}

double getDen(vd &x, vd &R, vd &C) {
    double den = 0;
    for (ll i = 0; i < N; ++i) {
        den += R[i]*x[i];
    }

    return den;
}

double getTemp(vd &x, vd &R, vd &C) {
    return getNum(x, R, C) / getDen(x, R, C);
}

int main() {
    ll T;
    cin >> T;
    for (ll cs = 1; cs <= T; ++cs) {
        cin >> N >> V >> X;

        vd R(N), C(N);
        bool over = false;
        bool under = false;
        for (ll i = 0; i < N; ++i) {
            cin >> R[i] >> C[i];

            if (C[i] >= X)
                over = true;
            if (C[i] <= X)
                under = true;
        }

        if (over && under) {
            vd x(N, 1);
            double temp = getTemp(x, R, C);
            cerr << temp << endl;
            ll changeIdx;
            
            if (abs(temp - X) > EP) {
                for (ll k = 0; k < 200; ++k) {
                    cerr << temp << " " << X << endl;
                    if (temp > X) {
                        ll hottestIdx = -1;
                        for (ll i = 0; i < N; ++i) {
                            if ((C[i] > C[hottestIdx] || hottestIdx == -1) && x[i] != 0) {
                                hottestIdx = i;
                            }
                        }

                        x[hottestIdx] = 0;
                        double newTemp = getTemp(x, R, C);
                        if (newTemp <= X + EP) {
                            changeIdx = hottestIdx;
                            break;
                        }
                    }
                    else {
                        ll coldestIdx = -1;
                        for (ll i = 0; i < N; ++i) {
                            if ((C[i] < C[coldestIdx] || coldestIdx == -1) && x[i] != 0) {
                                coldestIdx = i;
                            }
                        }

                        x[coldestIdx] = 0;
                        double newTemp = getTemp(x, R, C);
                        if (newTemp >= X - EP) {
                            changeIdx = coldestIdx;
                            break;
                        }
                    }
                    for (ll i = 0; i < N; ++i) {
                        cerr << x[i] << " ";
                    }
                    cerr << endl;
                }

                //cerr << changeIdx << endl;
                double A = getNum(x, R, C);
                double B = getDen(x, R, C);
                x[changeIdx] = (B*X - A) / (R[changeIdx]*C[changeIdx] - R[changeIdx]*X);
            }

            for (ll i = 0; i < N; ++i) {
                cerr << x[i] << endl;
            }
            
            double volume = 0;
            for (ll i = 0; i < N; ++i) {
                volume += R[i]*x[i];
            }

            double ans = V / volume;
            printf("Case #%lld: %.9lf\n", cs, ans);
        }
        else {
            printf("Case #%lld: IMPOSSIBLE\n", cs);
        }
    }
    return 0;
}
