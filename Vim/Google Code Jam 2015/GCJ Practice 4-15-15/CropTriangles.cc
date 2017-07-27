#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

ll nC2(ll n) {
    return n*(n-1)/2;
}

int main() {
    ll N;
    cin >> N;
    for (ll cs = 1; cs <= N; ++cs) {
        ll n, A, B, C, D, x0, y0, M;
        cin >> n >> A >> B >> C >> D >> x0 >> y0 >> M;

        vii points(n);
        
        ll X = x0, Y = y0;
        for (ll i = 0; i < n; ++i) {
            points[i] = ii(X%3, Y%3);
            X = (A * X + B) % M;
            Y = (C * Y + D) % M; 
        }

        vvi mod(3, vi(3, 0));
        ll total = 0;
        for (ll i = 0; i < n; ++i) {
            for (ll x1 = 0; x1 < 3; ++x1) {
                for (ll x2 = 0; x2 < 3; ++x2) {
                    for (ll y1 = 0; y1 < 3; ++y1) {
                        for (ll y2 = 0; y2 < 3; ++y2) {
                            if ((x1+x2+points[i].first)%3==0 && (y1+y2+points[i].second)%3==0) {
                                if (x1==x2 && y1==y2) {
                                    total += 2*nC2(mod[x1][y1]);
                                }
                                else {
                                    total += mod[x1][y1] * mod[x2][y2];
                                }
                            }
                        }
                    }
                }
            } 
            
            ++mod[points[i].first][points[i].second];
        }

        printf("Case #%lld: %lld\n", cs, total/2);
    }
    return 0;
}
