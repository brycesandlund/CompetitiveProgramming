#include <iostream>
#include <vector>
#include <algorithm>

#define INF 1000000000

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

// Compute b so that ab = 1 (mod n).
// Returns n if gcd(a,n) != 1, since no such b exists.
ll modinv( ll a, ll n ) {
    ll x, y, g = egcd( a, n, x, y );
    if( g != 1 ) return -1;
    x %= n;
    if( x < 0 ) x += n;
    return x;
}

// Find all solutions to ax = b (mod n),
// and push them onto S.
// Returns the number of solutions.
// Solutions exist iff gcd(a,n) divides b.
// If solutions exist, then there are exactly gcd(a,n) of them.
ll modsolve( ll a, ll b, ll n, vi &S ) {
    ll _1,_2, g = egcd(a,n,_1,_2); // modinv uses egcd already
    if( (b % g) == 0 ) {
        ll x = modinv( a/g, n/g );
        x = (x * b/g) % (n/g);
        for( ll k = 0; k < g; k++ )
            S.push_back( (x + k*(n/g)) % n );
        return (ll)g;
    }
    return 0;
}

void find(ll &offset, ll &length, vi &found, ll x, ll h, ll y, ll m) {
    found = vi(m, -1);
    ll counter = 0;
    found[h] = 0;

    while (true) {
        h = (x*h + y) % m;
        if (found[h] != -1) {
            length = counter - found[h] + 1;
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
        ll a, b;
        if (found1[a1] < offset1) {
            offset1 = found1[a1];
            offset2 = found2[a2];
            
            a = length2;
            b = (offset1 - offset2 + m) % m;
        }
        else if (found2[a2] < offset2) {
            offset1 = found1[a1];
            offset2 = found2[a2];

            a = length1;
            b = (offset2 - offset1 + m) % m;
        }
        else {
            offset1 = found1[a1];
            offset2 = found2[a2];
            
            a = (length1 - length2 + m) % m;
            b = (offset2 - offset1 + m) % m;
        }

        vi S;
        ll result = modsolve(a, b, m, S);

        if (result == 0)
            ans = -1;
        else {
            ans = INF;
            for (ll i = 0; i < S.size(); ++i) {
                ans = min(ans, S[i] * a + 
            }
        }
    }

    cout << ans << endl;

    return 0;
}
