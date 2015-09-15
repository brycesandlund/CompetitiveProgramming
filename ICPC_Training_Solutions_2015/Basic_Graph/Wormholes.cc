#include <iostream>
#include <vector>
#include <limits>

using namespace std;

#define FOR(v,l,u) for( size_t v = l; v < u; ++v )

typedef signed long long int T;
typedef vector<T>       VT;
typedef vector<VT>     VVT;
typedef vector<bool>    VB;
typedef vector<VB>     VVB;
typedef vector<size_t>  VI;
typedef vector<VI>     VVI;
const T UNBOUNDED = numeric_limits<T>::min(); // -infinity for doubles
const T INFINITY  = numeric_limits<T>::max(); // infinity for doubles

struct graph {
	size_t N; // number of nodes
	VVI    A; // adjacency list
	VVT    W; // weight of edges
	VT     D; // shortest distance
	graph( size_t N ) : N(N), A(N), W(N) {}
	void add_edge( size_t s, size_t t, T w ) {
		A[s].push_back(t);
		W[s].push_back(w);
	}
	bool bellmanford( size_t S ) {
		D = VT(N, INFINITY); D[S] = 0;
		FOR(k,0,N)
		FOR(s,0,N)
		FOR(i,0,A[s].size()) {
			size_t t = A[s][i];
			if( D[s] == INFINITY ) continue;
			if( D[t] > D[s] + W[s][i] ) {
				if( k == N-1 ) {
					D[t] = UNBOUNDED;
				}
				else {
					D[t] = D[s] + W[s][i];
				}
			}
		}
		FOR(v,0,N) if( D[v] == UNBOUNDED ) return false;
		return true;
	}
};

int main() {
	size_t n_cases;
	cin >> n_cases;
	FOR(qqq,0,n_cases) {
		size_t N, M;
		cin >> N >> M;
		graph G(N);
		FOR(e,0,M) {
			size_t s, t;
			T delta;
			cin >> s >> t >> delta;
			G.add_edge( s, t, delta );
		}
		if( G.bellmanford(0) ) {
			cout << "not possible" << endl;
		}
		else {
			cout << "possible" << endl;
		}
	}
	return 0;
}
