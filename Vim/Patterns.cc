#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<string> vs;

void KMP_table(string &w, vi &T) {
    T = vi(w.size()+1);
    ll i = 2, j = 0;
    T[1] = 0;
    while (i < w.size()) {
        if (w[i-1] == w[j]) { T[i] = j+1; ++i; ++j; }
        else if (j > 0) { j = T[j]; }
        else { T[i] = 0; ++i; }
    }
}

ll KMP(string &s, string q) {
    ll m, z; m = z = 0;
    vi T; KMP_table(q, T);
    ll count = 0;
    while (m+z < s.size()) {
        if (q[z] == s[m+z]) {
            ++z;
            if (z == q.size()-1) {
                ++count;
            }
        }
        else if (z > 0) {
            m += z - T[z]; z = T[z];
        }
        else {
            m += 1; z = 0;
        }
    }

    return count;
}

int main() {
    for (ll cs = 1; true; ++cs) {
        ll N;
        cin >> N;

        if (N == 0) break;

        vs queries(N);
        for (ll i = 0; i < N; ++i) {
            cin >> queries[i];
        }

        string big;
        cin >> big;

        vi counts(N);
        for (ll i = 0; i < N; ++i) {
            counts[i] = KMP(big, queries[i] + "_");
        }

        vi maxes;
        ll maxCount = -1;
        for (ll i = 0; i < N; ++i) {
            if (counts[i] > maxCount) {
                maxes.clear();
                maxes.push_back(i);
                maxCount = counts[i];
            }
            else if (counts[i] == maxCount) {
                maxes.push_back(i);
            }
        }

        cout << maxCount << endl;
        for (ll i = 0; i < (ll)maxes.size(); ++i) {
            cout << queries[maxes[i]] << endl;
        }
    }
}
