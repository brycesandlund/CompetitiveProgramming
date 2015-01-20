#include <iostream>
#include <vector>
#include <set>
#include <limits>

using namespace std;

#define FOR(V,L,U) for( size_t V = L; V < U; ++V )
#define FORit(IT,C,T) for( T::iterator IT = C.begin(); IT != C.end(); ++IT )

typedef unsigned long long int ULL;
typedef vector<ULL> VULL;
typedef set<ULL>    SULL;

const ULL ULL_MAX = numeric_limits<ULL>::max();

struct tree;
typedef vector<tree *> VTp;

struct tree {
	VTp C;
	size_t opt_c;
	ULL opt_1, opt_2;
	void add_child( tree *c ) { C.push_back(c); }
	ULL get_opt( size_t avoid ) {
		if( avoid == opt_c ) return opt_2;
		else                 return opt_1;
	}
	void compute() {
		FOR(i,0,C.size()) C[i]->compute();
		SULL options;
		FOR(i,0,C.size()) options.insert( C[i]->opt_c );
		FOR(cc,1,C.size()+2) {
			if( options.find(cc) == options.end() ) {
				options.insert(cc);
				break;
			}
		}
		options.insert(2); // guarantee at least 2 things
		opt_1 = opt_2 = ULL_MAX;
		FORit(it,options,SULL) {
			ULL c = *it;
			ULL option = c;
			FOR(i,0,C.size()) option += C[i]->get_opt(c);
			if( option < opt_1 ) {
				opt_2 = opt_1;
				opt_1 = option;
				opt_c = c;
			}
			else if( option < opt_2 ) {
				opt_2 = option;
			}
		}
	}
};
typedef vector<tree>   VT;

int main() {
	size_t T; cin >> T;
	FOR(tt,0,T) {
		size_t N; cin >> N;
		VT employees(N);
		tree *ceo = 0L;
		FOR(i,0,N) {
			size_t p; cin >> p;
			if( p > 0 ) {
				--p;
				employees[p].add_child( &employees[i] );
			}
			else {
				ceo = &employees[i];
			}
		}
		ceo->compute();
		cout << "Case #" << tt+1 << ": " << ceo->opt_1 << endl;
	}
	return 0;
}

