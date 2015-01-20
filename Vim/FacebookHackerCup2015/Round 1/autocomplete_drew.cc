#include <iostream>
#include <vector>

#define FOR(v,l,u) for( size_t v = l; v < u; ++v )

using namespace std;

char i2c( size_t i ) { return 'a'+(char)i; }
size_t c2i( char c ) { return c - 'a'; }

struct tree;
typedef vector<tree *> VT;

vector<tree> tree_pool;
size_t ti;
tree * next_tree();

struct tree {
	VT C;
	size_t n;
	tree() : C(26,0L), n(0) {}
	void add_word( const char *word ) {
		++n;
		if( word[0] != '\0' ) {
			size_t s = c2i(word[0]);
			if( C[s] == 0L ) C[s] = next_tree();
			C[s]->add_word( word+1 );
		}
	}
	size_t word_lookup( const char *word ) {
		if( word[0] == '\0' ) return 0;
		size_t s = c2i(word[0]);
		if( n == 1 ) return 0;
		else         return 1+C[s]->word_lookup(word+1);
	}
};

tree * next_tree() {
	ti = (ti+1) % 1000010;
	tree_pool[ti] = tree();
	return &tree_pool[ti];
}

int main() {
	tree_pool.resize( 1000010 ); ti = 0;
	size_t T; cin >> T;
	//T = 100; // TODO
	FOR(tt,0,T) {
		tree Tr;
		size_t N; cin >> N;
		//N = 1; // TODO
		size_t ttl = 0;
		FOR(i,0,N) {
			char word[1000001];
			cin >> word;
			//FOR(i,0,1000000) word[i] = 'a'; word[1000000] = '\0'; // TODO
			Tr.add_word( word );
			if( ttl == 0 ) ++ttl;
			ttl += Tr.word_lookup( word );
		}
		cout << "Case #" << tt+1 << ": " << ttl << endl;
	}
	return 0;
}
