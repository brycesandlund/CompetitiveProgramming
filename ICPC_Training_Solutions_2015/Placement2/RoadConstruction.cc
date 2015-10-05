#include <iostream>
#include <vector>

#define INF 1000000000000LL

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

int main() {
    ll t, n;
    for (ll cs = 1; cin >> t >> n; ++cs) {
        vi east, west;
        vi east_i, west_i;
        for (ll i = 0; i < n; ++i) {
            char c;
            ll a, r;
            cin >> ws >> c >> a >> r;
            if (c == 'W') {
                west.push_back(a);
                west_i.push_back(r);
            }
            else {
                east.push_back(a);
                east_i.push_back(r);
            }
        }

        vvi best_time(east.size()+1, vi(west.size()+1, INF));
        vvi best_ir(east.size()+1, vi(west.size()+1, INF));

        best_time[0][0] = 0;
        best_ir[0][0] = 0;

        for (ll i = 0; i <= east.size(); ++i) {
            for (ll j = 0; j <= west.size(); ++j) {
                ll start = best_time[i][j]-3;
                ll ir = best_ir[i][j];
                for (ll k = i+1; k <= east.size(); ++k) {
                    start = max(start+3, east[k-1]);
                    best_time[k][j] = min(best_time[k][j], start+t);
                    if (start - east[k-1] > east_i[k-1]) {
                        ++ir;
                    }
                    best_ir[k][j] = min(best_ir[k][j], ir);
                }

                start = best_time[i][j]-3;
                ir = best_ir[i][j];
                for (ll k = j+1; k <= west.size(); ++k) {
                    start = max(start+3, west[k-1]);
                    best_time[i][k] = min(best_time[i][k], start+t);
                    if (start - west[k-1] > west_i[k-1]) {
                        ++ir;
                    }
                    best_ir[i][k] = min(best_ir[i][k], ir);
                }
            }
        }

        cout << best_ir[east.size()][west.size()] << endl;
    }
    return 0;
}
