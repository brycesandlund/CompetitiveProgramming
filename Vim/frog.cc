#include <iostream>
#include <vector>
#include <algorithm>

#define INF 100000000000000000LL

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

// returns gcd(a,b), and additionally finds x,y such that gcd(a,b) = ax + by
ll egcd( ll a, ll b, ll &x, ll &y ) {
    if( a < 0 ) {
        ll r = egcd(-a,b,x,y);
        x *= -1;
        return r;
    }
    if( b < 0 ) {
        ll r = egcd(a,-b,x,y);
        y *= -1;
        return r;
    }
    ll u = y = 0,   v = x = 1;
    while( b ) {
        ll q = a/b,     r = a % b;
        a = b,       b = r;
        ll m = u,       n = v;
        u = x - q*u, v = y - q*v;
        x = m,       y = n;
    }
    return a;
}

// Compute x and y so that ax + by = c.
// llhe solution, when it exists, is unique up to the transformation
//     x -> x + kb/g
//     y -> y - ka/g
// for integers k, where g = gcd(a,b).
// llhe solution exists iff gcd(a,b) divides c.
// llhe return value is true iff the solution exists.
bool linear_diophantine( ll a, ll b, ll c, ll &x, ll &y ) {
    ll s,t, g = egcd(a,b,s,t);
    if( (c % g) != 0 )
        return false;
    x = c/g*s; y = c/g*t;
    return true;
}

void find(ll &offset, ll &length, vi &found, ll x, ll h, ll y, ll m) {
    found = vi(m, -1);
    ll counter = 0;
    found[h] = counter++;

    while (true) {
        h = (x*h + y) % m;
        if (found[h] != -1) {
            length = counter - found[h];
            offset = found[h];
            cerr << offset << " " << length << endl;
            return;
        }
        else {
            found[h] = counter++;
        }
    }
}

int main() {
    ll m, h1, a1, x1, y1, h2, a2, x2, y2;
    cin >> m >> h1 >> a1 >> x1 >> y1 >> h2 >> a2 >> x2 >> y2;

    ll offset1, length1, offset2, length2;
    vi found1, found2;
    find(offset1, length1, found1, x1, h1, y1, m);
    find(offset2, length2, found2, x2, h2, y2, m);

    ll ans;
    if (found1[a1] == -1 || found2[a2] == -1)
        ans = -1;
    else if (found1[a1] < offset1 && found2[a2] < offset2) {
        if (found1[a1] == found2[a2])
            ans = found1[a1];
        else
            ans = -1;
    }
    else {
        ll a, b, c;
        if (found1[a1] < offset1) {
            length1 = 0;
        }
        else if (found2[a2] < offset2) {
            length2 = 0;
        }
        
        offset1 = found1[a1];
        offset2 = found2[a2];

        cerr << "offset1:" << offset1 << endl;
        cerr << "offset2:" << offset2 << endl;
        cerr << "length1:" << length1 << endl;
        cerr << "length2:" << length2 << endl;

        ll x, y;
        a = length1;
        b = -length2;
        c = offset2 - offset1;
        if (linear_diophantine(a, b, c, x, y)) {
            ll blah1, blah2;
            ll g = egcd(a, b, blah1, blah2);
            /*if (x < 0) {
                x += ((x+b/g-1) / (b/g)) * (b/g);
            }
            else {
                x -= (x / (b/g)) * (b/g);
            }*/
            while (x > 0) {
                x += b/g;
            }
            while (x < 0) {
                x -= b/g;
            }
            //cerr << x << endl;
            ans = x * length1 + offset1;
        }
        else {
            ans = -1;
        }
    }

    cout << ans << endl;

    return 0;
}
