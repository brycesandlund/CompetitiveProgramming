#include <iostream>
#include <vector>

#define INF 1000000000000000000LL

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

int main() {
    ll N;
    cin >> N;
    for (ll cs = 1; cs <= N; ++cs) {
        ll m, k;
        cin >> m >> k;
        vi p(m);
        ll max_pi = 0;
        for (ll i = 0; i < m; ++i) {
            cin >> p[i];
            max_pi = max(max_pi, p[i]);
        }

        ll lo = max_pi, hi = INF;
        vi divisions_ans;
        
        while (lo + 1 != hi) {
            ll mid = (lo+hi)/2;

            vi divisions;
            ll rolling_sum = 0;
            for (ll i = m-1; i >= 0; --i) {
                if (p[i] + rolling_sum > mid || i+2 == k-divisions.size()) {
                    rolling_sum = 0;
                    divisions.push_back(i);
                    ++i;
                }
                else {
                    rolling_sum += p[i];
                }
            }

            if (divisions.size() == k-1) {
                hi = mid;
                divisions_ans = divisions;
            }
            else
                lo = mid;
        }
        divisions_ans = vi(divisions_ans.rbegin(), divisions_ans.rend());

        for (ll i = 0, j = 0; i < m-1; ++i) {
            cout << p[i] << " ";
            if (j < divisions_ans.size() && divisions_ans[j] == i) {
                cout << "/ ";
                ++j;
            }
        }
        cout << p[m-1] << endl;
    }
    return 0;
}
