#include <iostream>
#include <algorithm>

using namespace std;

#define FOR(v,l,u) for( size_t v = l; v < u; ++v )

typedef unsigned long long int ULL;

const ULL MOD = 1000000007;

int main() {
	ULL dp1[2001][2001];
	FOR(j,0,2001) dp1[0][j] = 0;
	FOR(i,1,2001) dp1[i][0] = 1;
	FOR(i,1,2001)
	FOR(j,1,2001) {
		if( i <= j ) dp1[i][j] = 0;
		else         dp1[i][j] = (dp1[i-1][j] + dp1[i][j-1]) % MOD;
	}

	ULL dp2[2001][2001];
	FOR(j,0,2001) dp2[0][j] = 0;
	FOR(i,1,2001) dp2[i][0] = 1;
	FOR(i,1,2001)
	FOR(j,1,2001) {
		if( i < j )  dp2[i][j] = 0;
		else         dp2[i][j] = (dp2[i-1][j] + dp2[i][j-1]) % MOD;
	}

	size_t T; cin >> T;
	FOR(tt,0,T) {
		size_t t1, t2; char _;
		cin >> t1 >> _ >> t2;
		cout << "Case #" << tt+1 << ": " << dp1[t1][t2] << " " << (t2 > 0 ? dp2[t2][t2-1] : 1) << endl;
	}

	return 0;
}
