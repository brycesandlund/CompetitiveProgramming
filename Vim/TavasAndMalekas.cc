#include <iostream>
#include <vector>

#define MOD 1000000007LL

using namespace std;

typedef long long ll;
typedef vector<bool> vb;
typedef vector<ll> vi;

void KMP_table(string &w, vi &T) {
    T = vi(w.size()+1);
    size_t i = 2, j = 0;
    T[0] = -1;
    T[1] = 0;
    while (i <= w.size()) {
        if (w[i-1] == w[j]) { T[i] = j+1; ++i; ++j; }
        else if (j > 0)   { j = T[j]; }
        else              { T[i] = 0; ++i; }
    }
}

vi prefix(string p) {
    vi pi(p.size(), -1);
    int k = -1;
    for (ll i = 1; i < p.size(); ++i) {
        while (k != -1 && p[k+1] != p[i])
            k = pi[k];
        if (p[k+1] == p[i])
            k++;
        p[i] = k;
    }
    return pi;
}

int main() {
    string test = "abcabc abcabc";
    vi T(8, -1);
    KMP_table(test, T);
    for (ll i = 0; i < test.size(); ++i) {
        cerr << test[i] << " ";
    }
    cerr << endl;
    for (ll i = 1; i < T.size(); ++i) {
        cerr << T[i] << " ";
    }
    cerr << endl;


    ll n, m;
    cin >> n >> m;

    string p;
    cin >> p;

    vb matches(p.size()+1, true);
    for (ll i = p.size()-1; i >= 0; --i) {
        matches[i] = matches[i+1] && p[i] == p[0];
    }

    vi y(m);
    for (ll i = 0; i < m; ++i) {
        cin >> y[i];
        --y[i];
    }

    bool success = true;
    ll usedSpots = 0;
    if (m >= 1)
        usedSpots = p.size();

    for (ll i = 1; i < m; ++i) {
        ll overlapIdx = y[i] - y[i-1];
        if (overlapIdx < p.size()) {
            if (!matches[overlapIdx]) {
                success = false;
                break;
            }

            usedSpots += overlapIdx;
        }
        else {
            usedSpots += p.size();
        }
    }

    if (success) {
        ll total = 1;
        for (ll i = 0; i < n-usedSpots; ++i) {
            total = (total * 26) % MOD;
        }

        cout << total << endl;
    }
    else {
        cout << 0 << endl;
    }

    return 0;
}
