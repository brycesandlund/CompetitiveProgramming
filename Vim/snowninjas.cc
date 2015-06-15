#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <queue>

using namespace std;

#define FOR(v,l,u) for( LL v = l; v < u; ++v )

typedef signed long long int LL;
typedef pair<LL,LL> PII;
typedef set<PII> SPII;
typedef vector<SPII> VSPII;
typedef vector<LL> VI;
typedef vector<bool> VB;

LL delta( LL cx, LL x ) {
    return (LL)sqrt( 100*100 - (cx-x)*(cx-x) );
}

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);
    LL n_cases; cin >> n_cases;
    FOR(qqq,0,n_cases) {
        LL N = 0; cin >> N;
        VI x(N), y(N);
        FOR(i,0,N) cin >> x[i] >> y[i];
        ++N; x.push_back(0); y.push_back(0);
        FOR(i,0,N) x[i] += 30000;
        VSPII buckets( 60002 );
        FOR(i,0,N) buckets[ x[i] ].insert( PII(y[i],i) );
        VB V(N,false);
        queue<LL> Q;
        Q.push( N-1 ); V[N-1] = true;
        while( !Q.empty() ) {
            LL c = Q.front(); Q.pop();
            //cerr << "visit " << x[c] << " " << y[c] << endl;
            for( LL d = -100; d <= 100; ++d ) {
                if( x[c] + d < 0 || x[c] + d >= (LL)buckets.size() ) continue;
                if( buckets[ x[c]+d ].size() == 0 ) continue;
                LL del = delta( x[c], x[c] + d );
                //cerr << "look for x=" << x[c]+d << ", y in [" << y[c]-del << "," << y[c]+del << "]" << endl;
                SPII::iterator lb, ub;
                lb = buckets[ x[c]+d ].lower_bound( PII(y[c]-del,0) );
                ub = buckets[ x[c]+d ].upper_bound( PII(y[c]+del,N) );
                for( SPII::iterator it = lb; it != ub; ++it ) {
                    //cerr << "tick" << endl;
                    //if( it->first < y[c]-del ) { cerr << "yikes" << endl; continue; }
                    //if( it->first > y[c]+del ) { cerr << "yikes" << endl; continue; }
                    //if( V[ it->second ] ) continue;
                    //cerr << "tick" << endl;
                    V[ it->second ] = true;
                    Q.push( it->second );
                }
                
                buckets[x[c] + d].erase(lb, ub);
            }
        }
        FOR(i,0,N) x[i] -= 30000;
        LL max_dist = 0;
        FOR(i,0,N) if( V[i] ) max_dist = max((double)max_dist, sqrt(x[i]*x[i] + y[i]*y[i])) + 1e-6;
        cout << max_dist << endl;
    }
    return 0;
}
