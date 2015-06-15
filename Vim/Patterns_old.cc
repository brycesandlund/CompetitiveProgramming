#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<string> vs;

ll occurrences(string &q, string &big) {
    ll count = 0;
    for (ll i = 0; i < (ll)big.size(); ++i) {
        bool success = true;
        for (ll j = 0; j < (ll)q.size(); ++j) {
            if (big[i+j] != q[j]) {
                success = false;
                break;
            }
        }

        if (success) {
            ++count;
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
            counts[i] = occurrences(queries[i], big);
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
