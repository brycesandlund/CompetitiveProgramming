#include <iostream>
#include <cmath>
#include <vector>
#include <map>

#define EP 1e-10
#define x first
#define y second

using namespace std;

typedef long long ll;
typedef pair<double, double> Pt;
typedef vector<Pt> vp;

ll C, N;
double R;

Pt operator - (Pt a, Pt b) { return Pt(a.x-b.x, a.y-b.y); }
Pt operator + (Pt a, Pt b) { return Pt(a.x+b.x, a.y+b.y); }
Pt operator / (Pt a, double s) { return Pt(a.x/s, a.y/s); }
Pt operator * (Pt a, double s) { return Pt(a.x*s, a.y*s); }

double cross(Pt a, Pt b) { return a.x*b.y - a.y*b.x; }

double dist(Pt a, Pt b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}

ll isLeft(Pt a, Pt b,  Pt c) {
    double z = cross(b-a,c-a);
    if (fabs(z) < EP) return 0;
    else if (z > 0) return 1;
    else return -1;
}

Pt RotateCW90(Pt p) { return Pt(p.y,-p.x); }

bool LinesParallel(Pt a, Pt b, Pt c, Pt d) {
    return fabs(cross(b-a,c-d)) < EP;
}

bool LinesColinear(Pt a, Pt b, Pt c, Pt d) {
    return LinesParallel(a,b, c,d)
        && isLeft(a,b, c) == 0
        && isLeft(c,d, a) == 0;
}

Pt ComputeLineIntersection(Pt a, Pt b, Pt c, Pt d) {
    b=b-a; d=d-c; c=c-a;
    return a + b*cross(c,d)/cross(b,d);
}

Pt ComputeCircleCenter(Pt a, Pt b, Pt c) {
    b=(b-a)/2; c=(c-a)/2;
    return a + ComputeLineIntersection(b, b+RotateCW90(b), c, c+RotateCW90(c));
}

ll count(vp &Z, Pt center) {
    ll result = 0;
    for (ll i = 0; i < N; ++i) {
        if (dist(Z[i], center) < R+EP) {
            ++result;
        }
    }
    return result;
}

int main() {
    cin >> C;

    for (ll cs = 1; cs <= C; ++cs) {
        cin >> R >> N;

        vp Z(N);
        for (ll i = 0; i < N; ++i) {
            cin >> Z[i].x >> Z[i].y;
        }

        ll best = N > 0;
        
        for (ll i = 0; i < N; ++i) {
            for (ll j = i+1; j < N; ++j) {
                best = max(best, count(Z, (Z[i]+Z[j])/2));
            }
        }

        for (ll i = 0; i < N; ++i) {
            for (ll j = i+1; j < N; ++j) {
                for (ll k = j+1; k < N; ++k) {
                    if (!LinesColinear(Z[i], Z[j], Z[j], Z[k])) {
                        best = max(best, count(Z, ComputeCircleCenter(Z[i], Z[j], Z[k])));
                    }
                }
            }
        }

        cout << best << endl;
    }
    return 0;
}
