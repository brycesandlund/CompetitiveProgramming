#include <iostream>
#include <vector>
#include <cmath>

#define NUM 2500 // change when submit!
#define EP 1e-10

using namespace std;

#define FOR(v,l,u) for( size_t v = l; v < u; ++v )
typedef double         T;   // the code below only supports fields
typedef vector<T>      VT;
typedef vector<VT>     VVT;
typedef vector<size_t> VI;
typedef vector<bool>   VB;
typedef unsigned long long ll;
typedef vector<ll> vi;

// Given an m-by-n matrix A, compute its reduced row echelon form,
// returning a value like the determinant.
// If m = n, the returned value *is* the determinant of A.
// If m != n, the returned value is nonzero iff A has full row rank.
// To compute rank(A), get its RREF, and count the nonzero rows.
T GaussJordan( VVT &A ) {
	const size_t m = A.size(), n = A[0].size();
	T det = 1;
	size_t pj = 0;        // walking pointer for the pivot column
	FOR(k,0,m) {
		size_t pi = k;
		while( pj < n ) {    // find the best row below k to pivot
			FOR(i,k,m) if( fabs(A[i][pj]) > fabs(A[pi][pj]) ) pi = i;
			if(fabs( A[pi][pj]) > EP) { // we have our new pivot
				if( pi != k ) {
					swap( A[pi], A[k] );
					pi = k;
					det *= -1;
				}
				break;
			}
			FOR(i,k,m) A[i][pj] = 0; // This column is zeros below row k
			++pj;                    // So move on to the next column
		}
		if( pj == n ) { det = 0; break; } // we're done early
		T s = 1.0/A[pi][pj];        // scale the pivot row
		FOR(j,pj,n) A[pi][j] *= s;
		det /= s;
		FOR(i,0,m) if( i != pi ) { // subtract pivot from other rows
			T a = A[i][pj];          // multiple of pivot row to subtract
			FOR(j,pj,n) A[i][j] -= a*A[pi][j];
		}
		++pj;
	}
	return det;
}

// Given m-by-n A and m-by-q b, compute a matrix x with Ax = b.
// This solves q separate systems of equations simultaneously.
// Fix k in [0,q).
// x[*][k] indicates a candidate solution to the jth equation.
// has_sol[k] indicates whether a solution is actually solution.
// The return value is the dimension of the kernel of A.
// Note that this is the dimension of the space of solutions when
// they exist.
size_t SolveLinearSystems( const VVT &A, const VVT &b, VVT &x, VB &has_sol ) {
	const size_t m = A.size(), n = A[0].size(), q = b[0].size();
	VVT M = A;                                     // copy
	FOR(i,0,m) FOR(j,0,q) M[i].push_back(b[i][j]); // augment
	GaussJordan( M );                              // RREF
	x = VVT(n, VT(q, 0));
	size_t i = 0, jz = 0;
	while( i < m ) {
		while( jz < n && fabs(M[i][jz]) < EP ) ++jz;
		if( jz == n ) break; // all zero means we're starting the kernel
		FOR(k,0,q) x[jz][k] = M[i][n+k]; // first nonzero is always 1
		++i;
	}
	size_t kerd = n - i; // i = row rank = column rank
	has_sol = VB(q,true);
	while( i < m ) {
		FOR(k,0,q) if( fabs(M[i][n+k]) > EP ) has_sol[k] = false;
		++i;
	}
	return kerd;
}

int main() {
    VVT A = {{1, 1, 1, 1, 1},
             {-2, -1, 0, 1, 2},
             /*{2, .5, 0, .5, 2},*/
             {-4.0/3, -1.0/6, 0, 1.0/6, 4.0/3},
             {2.0/3, 1.0/24, 0, 1.0/24, 2.0/3}};
    VVT b = {{0}, {1}, {0}, {0}, {0}};
    VVT x(5, VT(1));

    GaussJordan(A);
    for (ll i = 0; i < A.size(); ++i) {
        for (ll j = 0; j < A[0].size(); ++j) {
            cerr << A[i][j] << " ";
        }
        cerr << endl;
    }


    /*
    VB has_sol(5);
    SolveLinearSystems(A, b, x, has_sol);
    
    for (ll i = 0; i < 5; ++i) {
        cout << x[i][0] << endl;
    }
    */
    
    return 0;
}
