#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

#define EP 1e-10
#define INF 1000000000000LL

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef pair<double, double> dd;
typedef vector<dd> vdd;

int dx[] = {1, -1, -1, 1};
int dy[] = {-1, -1, 1, 1};

double cross(dd a, dd b) {
    return a.first*b.second - a.second*b.first;
}

ll isLeft(dd a, dd b, dd c) {
    double z = cross(dd(b.first-a.first, b.second-a.second), dd(c.first-a.first, c.second-a.first));
    if (abs(z) < EP) return 0;
    else if (z > 0) return 1;
    else return -1;
}

ll WindingNumber(vdd &p, dd q) {
    ll wn = 0;
    vi state(p.size());
    for (ll i = 0; i < p.size(); ++i) {
        if (abs(p[i].second - q.second) < EP) state[i] = 0;
        else if (p[i].second < q.second) state[i] = -1;
        else state[i] = 1;
    }
    for (ll i = 1; i < p.size(); ++i) if(state[i] == 0) state[i] = state[i-1];
    for (ll i = 0; i < p.size()-1; ++i) if(state[i] == 0) state[i] = state[i+1];
    for (ll i = 0; i < p.size(); ++i) {
        ll z = (i+1)%p.size();
        if (state[z] == state[i]) continue;
        else if (state[z] == 1 && isLeft(p[i],p[z],q) > 0) ++wn;
        else if (state[z] == 1 && isLeft(p[i],p[z],q) < 0) --wn;
    }
    return wn;
}

vdd shrink(vdd &points, vi &orient, double r) {
    vdd shrunk = points;
    for (ll i = 0; i < shrunk.size(); ++i) {
        shrunk[i].first += dx[orient[i]] * r;
        shrunk[i].second += dy[orient[i]] * r;
    }
    return shrunk;
}

bool valid(vdd &points, vi &orient, double r) {
    vdd shrunk = shrink(points, orient, r);

    for (ll i = 0; i < shrunk.size(); ++i) {
        dd testPt;
        testPt.first = shrunk[i].first + dx[orient[i]] * .00001;
        testPt.second = shrunk[i].second + dy[orient[i]] * .00001;
        if (WindingNumber(shrunk, testPt) == 1) {
            return true;
        }
    }

    return false;
}

int main() {
    for (ll cs = 1; true; ++cs) {
        ll n;
        cin >> n;

        if (n == 0) break;

        vdd points;
        vi orient;

        points.push_back(dd(0, 0));
        char lastChar = ' ';
        for (ll i = 1; true; ++i) {
            ll m;
            char d;
            cin >> m >> d;

            if (i == n) break;

            if (d != lastChar)
                points.push_back(points[i-1]);
            
            lastChar = d;
            
            if (d == 'R')
                points.back().first += m;
            else if (d == 'L')
                points.back().first -= m;
            else if (d == 'U')
                points.back().second += m;
            else
                points.back().second -= m;
        }

        for (ll i = 0; i < points.size(); ++i) {
            dd before = points[(i+points.size()-1)%points.size()];
            dd after = points[(i+1)%points.size()];
            if (before.first < points[i].first) {
                if (after.second > points[i].second) {
                    orient.push_back(2);
                }
                else
                    orient.push_back(3);
            }
            else if (before.first > points[i].first) {
                if (after.second > points[i].second) {
                    orient.push_back(1);
                }
                else
                    orient.push_back(0);
            }
            else if (before.second < points[i].second) {
                if (after.first > points[i].first) {
                    orient.push_back(2);
                }
                else
                    orient.push_back(1);
            }
            else
                if (after.first > points[i].first) {
                    orient.push_back(3);
                }
                else
                    orient.push_back(0);
        }

        double lo = 0, hi = INF;
        while (hi - lo > .0001) {
            double r = (hi+lo)/2;

            if (valid(points, orient, r)) {
                lo = r;
            }
            else
                hi = r;
        }

        if (cs != 1)
            printf("\n");

        printf("Case Number %lld radius is: %.2lf\n", cs, lo);
    }

    return 0;
}
