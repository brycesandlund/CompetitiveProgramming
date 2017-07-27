#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

typedef long long ll;

ll gcd(ll a, ll b) {
    if (a < 0) return gcd(-a, b);
    if (b < 0) return gcd(a, -b);
    ll c;
    while (b) { c = a % b; a = b; b = c; }
    return a;
}

struct Barber {
    ll timeFree;
    ll Bi;
    ll i;

    Barber(ll timeFree, ll Bi, ll i) : timeFree(timeFree), Bi(Bi), i(i) {}

    bool operator<(Barber const& rhs, Barber const& lhs) const {
        if (lhs.timeFree < rhs.timeFree) {
            return true;
        }
        else if (lhs.timeFree > rhs.timeFree) {
            return false;
        }
        else {
            return lhs.i < rhs.i;
        }
    }
};

int main() {
    Barber a(0, 0, 0), b(3, 0, 0);
    cerr << (a < b) << endl;

    ll T;
    cin >> T;

    for (ll cs = 1; cs <= T; ++cs) {
        
    }

    return 0;
}
