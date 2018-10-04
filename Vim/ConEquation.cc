#include <iostream>
#include <vector>

using namespace std;

typedef long long T;

// returns gcd(a,b), and additionally finds x,y such that gcd(a,b) = ax + by
T egcd( T a, T b, T &x, T &y ) {
	if( a < 0 ) {
		T r = egcd(-a,b,x,y);
		x *= -1;
		return r;
	}
	if( b < 0 ) {
		T r = egcd(a,-b,x,y);
		y *= -1;
		return r;
	}
	T u = y = 0,   v = x = 1;
	while( b ) {
		T q = a/b,     r = a % b;
		  a = b,       b = r;
		T m = u,       n = v;
		  u = x - q*u, v = y - q*v;
		  x = m,       y = n;
	}
	return a;
}

// Compute b so that ab = 1 (mod n).
// Returns n if gcd(a,n) != 1, since no such b exists.
T modinv( T a, T n ) {
	T x, y, g = egcd( a, n, x, y );
	if( g != 1 ) return -1;
	x %= n;
	if( x < 0 ) x += n;
	return x;
}

int main() {
    int a, b, p, x;
    cin >> a >> b >> p >> x;

    int cycle_a_size = 1;
    vector<int> dlog_a(p, -1);

    int a2 = a;
    while (a2 != 1) {
        dlog_a[a2] = cycle_a_size;
        a2 = (a2 * a) % p;
        ++cycle_a_size;
    }
    dlog_a[1] = cycle_a_size;

    int total = 0;
    for (int n = 1; n <= p; ++n) {
        int q = (x-n) / p;
        
        int y = (b * modinv(n, p)) % p;

        int z = dlog_a[y];

        int i = z-n;
        if (i < 0) i += p-1;
        if (i < 0) i += p-1;

        cerr << "i: " << i << endl;
        cerr << "z: " << z << endl;

        int n_solutions = (q-i+p-1)/(p-1);
        if (q-i < 0)
            n_solutions = 0;

        if (n_solutions > 0) cerr << n << endl;
        total += n_solutions;
    }
    cout << total << endl;
}
