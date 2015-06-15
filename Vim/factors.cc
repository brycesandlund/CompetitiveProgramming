#include <iostream>
#include <vector>
#include <map>
#include <limits>

using namespace std;

#define FOR(v,l,u) for( ULL v = l; v < u; ++v )

typedef unsigned long long int ULL;
typedef vector<ULL> VI;
typedef vector<VI> VVI;

VVI _choose;
void comp_choose() {
    _choose = VVI( 66, VI(66, 0 ));
    FOR(n,0,66) FOR(k,0,66) {
        if( n < k ) _choose[n][k] = 0;
        else if( n == k ) _choose[n][k] = 1;
        else if( k == 0 ) _choose[n][k] = 1;
        else
            _choose[n][k] = _choose[n-1][k-1] + _choose[n-1][k];
    }
}
ULL choose( ULL n, ULL k ) { return _choose[n][k]; }

VI _primes;
void comp_primes() {
    _primes.clear();
    const ULL A[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 47, 53, 59, 61, 67 };
    _primes = VI( A, A+18 );
}
ULL prime_i( ULL i ) { return _primes[i-1]; }


typedef pair<ULL,ULL> II;
typedef pair< ULL, II > III;
typedef map< III, ULL > DPMAP;
ULL solve( DPMAP &DP, ULL i, ULL n, ULL s ) {
    if( DP.find( III(i,II(n,s)) ) != DP.end() ) return DP[ III(i,II(n,s)) ];
    ULL ret;
    if( n == 1 ) {
        ret = 1;
    }
    else {
        ULL pi = prime_i(i);
        ULL ppi = 1;
        ULL opt = numeric_limits<ULL>::max()/2;
        FOR(j,1,64) {
            ppi *= pi;
            //cerr << pi << ", " << j << ", " << ppi << " " << i << endl;
            if( ppi > opt ) break;
            if( s+j > 63 ) break;
            ULL c = choose(s+j,j);
            if( c > n ) break;
            if( (n % c) != 0 ) continue;
            
            ULL candsub = solve(DP,i+1,n/c,s+j);
            if( candsub == numeric_limits<ULL>::max()/2 ) continue;
            if ((double)ppi * (double)candsub > numeric_limits<ULL>::max()) continue;
            
            ULL cand = ppi * candsub;
            opt = min(opt, cand);
        }
        ret = opt;
    }
    return (DP[ III(i,II(n,s)) ] = ret);
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    DPMAP DP;
    comp_choose();
    comp_primes();
    while(1) {
        cin >> ws; if( cin.eof() ) break;
        ULL n; cin >> n;
        ULL ans;
        if( n == 1 ) {
            ans = 2;
        }
        else {
            ans = solve(DP,1,n,0);
        }
        cout << n << " " << ans << endl;
        DP.clear();
    }
    return 0;
}
