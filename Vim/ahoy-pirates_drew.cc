#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

#define FOR(v,l,u) for( size_t v = l; v < u; ++v )

typedef vector<bool> VB;

char merge_ops( char pre, char post ) {
	switch(post) {
		case 'C': return post;
		case 'R': return post;
		case '.': return pre;
		case 'i': switch(pre) {
			case '.': return 'i';
			case 'i': return '.';
			case 'C': return 'R';
			case 'R': return 'C';
		}
	}
	return 'X';
}

struct seg_tree {
	seg_tree *lsub, *rsub;
	size_t L, R, M;
	char lazy_op; // (i)nvert, set bu(C)caneer, set ba(R)bary.
	size_t amt;

	void unlazy() {
		if( L != R ) {
			lsub->lazy_op = merge_ops( lsub->lazy_op, lazy_op );
			rsub->lazy_op = merge_ops( rsub->lazy_op, lazy_op );
		}
		switch(lazy_op) {
			case 'i': amt = R-L+1 - amt; break;
			case '.': break;
			case 'R': amt = 0;     break;
			case 'C': amt = R-L+1; break;
		}
		lazy_op = '.';
	}

	void init( const VB &ref, size_t _L, size_t _R ) {
		L = _L;  R = _R;  M = (L+R)/2;
		lazy_op = '.';
		if( L == R ) {
			amt = ref[M] ? 1 : 0;
		}
		else {
			lsub->init( ref, L,   M );
			rsub->init( ref, M+1, R );
			amt = lsub->amt + rsub->amt;
		}
	}

	void update( size_t qL, size_t qR, char op ) {
		if( L == qL && qR == R ) {
			lazy_op = merge_ops( lazy_op, op );
		}
		else {
			unlazy();
			if( qL <= M ) lsub->update( qL, min(qR,M), op );
			if( qR >  M ) rsub->update( max(qL,M+1), qR, op );
			lsub->unlazy();
			rsub->unlazy();
			amt = lsub->amt + rsub->amt;
		}
	}

	size_t query( size_t qL, size_t qR ) {
		unlazy();
		if( L == qL && qR == R ) {
			return amt;
		}
		else {
			size_t ret = 0;
			if( qL <= M ) ret += lsub->query( qL, min(qR,M) );
			if( qR >  M ) ret += rsub->query( max(M+1,qL), qR );
			return ret;
		}
	}

	void print_tree( size_t W ) {
		FOR(i,0,L)   cerr << " ";
		FOR(i,L,R+1) cerr << "-";
		FOR(i,R+1,W) cerr << " ";
		cerr << "|   ";
		cerr << "amt=" << amt;
		cerr << "  lazy_op=" << lazy_op;
		cerr << endl;
		if( L != R ) {
			lsub->print_tree(W);
			rsub->print_tree(W);
		}
	}
};

typedef vector<seg_tree> VST;

size_t _l( size_t i ) { return 2*(i+1) + 0 - 1; }
size_t _r( size_t i ) { return 2*(i+1) + 1 - 1; }
void setup_seg_tree( VST &tree, size_t N ) {
	tree = VST(4*N+1);
	FOR(i,0,tree.size()) {
		if( _r(i) < tree.size() ) {
			tree[i].lsub = &tree[_l(i)];
			tree[i].rsub = &tree[_r(i)];
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	size_t T; cin >> T;
	FOR(tt,0,T) {
		size_t M; cin >> M;
		size_t N = 0;
		VB init;
		FOR(mi,0,M) {
			size_t R; string S;
			cin >> R >> S;
			size_t B = N;
			N += R*S.size();
			init.resize( N );
			FOR(r,0,R) FOR(i,0,S.size()) init[B + r*S.size() + i] = ( S[i] == '1' );
		}
		VST tree; setup_seg_tree(tree, N);
		seg_tree *Tr = &tree[0];
		Tr->init( init, 0, N-1 );

		cout << "Case " << 1+tt << ":" << endl;
		//cerr << "N = " << N << endl;
		//FOR(i,0,N) cerr << (init[i] ? '1' : '0'); cerr << endl;
		size_t Q; cin >> Q;
		size_t n_god_queries = 0;
		FOR(qq,0,Q) {
			char t; size_t l, r;
			cin >> t >> l >> r;
			switch(t) {
				case 'F':
					//cerr << "Set [" << l << "," << r << "] = 1" << endl;
					Tr->update(l,r,'C');
					break;
				case 'E':
					//cerr << "Set [" << l << "," << r << "] = 0" << endl;
					Tr->update(l,r,'R');
					break;
				case 'I':
					//cerr << "Invert [" << l << "," << r << "]" << endl;
					Tr->update(l,r,'i');
					break;
				case 'S':
					//cerr << "Query [" << l << "," << r << "]" << endl;
					cout << "Q" << ++n_god_queries << ": " << Tr->query( l, r ) << endl;
					break;
			}
			//FOR(i,0,N) cerr << Tr->query(i,i); cerr << endl;
			//Tr->print_tree(N);
		}
	}
	return 0;
}
