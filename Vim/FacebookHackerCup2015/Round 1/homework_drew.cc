#include <iostream>
#include <vector>

using namespace std;

#define FOR(v,l,u) for( size_t v = l; v < u; ++v )

typedef vector<size_t> VI;
typedef vector<VI>     VVI;

const size_t UB = 10000000;

VVI ans;

void do_sieve() {
	VI primacity( UB+1, 0 );
	FOR(p,2,UB+1) {
		if( primacity[p] != 0 ) continue;
		FOR(m,1,UB+1) {
			if( p*m > UB ) break;
			else           ++primacity[p*m];
		}
	}
	size_t max_primacity = 0;
	FOR(i,0,primacity.size()) max_primacity = max(max_primacity, primacity[i]);
	ans = VVI( max_primacity+1, VI(UB+1, 0) );
	FOR(i,0,primacity.size())
		++ans[ primacity[i] ][i];
	FOR(k,0,max_primacity+1)
	FOR(i,1,primacity.size()+1)
		ans[k][i] += ans[k][i-1];
}

size_t q( size_t A, size_t B, size_t K ) {
	if( K >= ans.size() ) return 0;
	else                  return ans[K][B] - ans[K][A-1];
}

int main() {
	do_sieve();
	size_t T; cin >> T;
	FOR(tt,0,T) {
		size_t A, B, K; cin >> A >> B >> K;
		cout << "Case #" << tt+1 << ": " << q(A,B,K) << endl;
	}
	return 0;
}
