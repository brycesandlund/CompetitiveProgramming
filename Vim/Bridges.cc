#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <cmath>
#include <map>
#include <set>
#include <cstdio>

#define INF 10000000000000LL
#define EP 1e-10

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<string> vs;
typedef pair<ll, ll> ii;
typedef pair<ll, ii> iii;
typedef vector<iii> viii;
typedef vector<viii> vviii;
typedef vector<vviii> vvviii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<vvii> vvvii;
typedef pair<double, double> dd;
typedef vector<dd> vdd;

ll d, s;

double fun(double a) {
    return a+s - a*cosh(d/(2.0*a));
}

int main() {
    cin >> d >> s;

    double lo = 1e-5, hi = 1;

    while (fun(hi) > 0) {
        hi *= 2;
    }

    cerr << fun(1235134) << endl;
    return 0;

    cerr << hi << endl;
    while ((hi+lo)/2 - lo > 1e-5) {
        double a = (hi+lo)/2;

        if (fun(a) > 0)
            lo = a;
        else
            hi = a;
    }
    cerr << lo << " " << hi << endl;

    double a = lo;
    cout << 2 * a * sinh(d/(2.0*a)) << endl;
}
