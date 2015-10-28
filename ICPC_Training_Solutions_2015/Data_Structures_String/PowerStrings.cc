#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

void KMP_table(string &w, vi &T) {
    T.resize(w.size()+1);
    ll i = 2, j = 0;
    T[1] = 0;
    while (i <= w.size()) {
        if (w[i-1] == w[j]) { T[i] = j+1; ++i; ++j; }
        else if (j > 0) { j = T[j]; }
        else { T[i] = 0; ++i; }
    }
}

ll KMP(string &s, string &q) {
    size_t m, z; m = z = 0;
    vi T; KMP_table(q, T);
    while (m+z < s.size()) {
        if (q[z] == s[m+z]) {
            ++z;
            if (z == q.size()) return m;
        }
        else if (z > 0) {
            m += z - T[z]; z = T[z];
        }
        else {
            m += 1; z = 0;
        }
    }
    return s.size();
}

int main() {
    string s;
    for (ll cs = 1; cin >> s && s != "."; ++cs) {
        string ss = s.substr(1) + s;
        ll overlap = KMP(ss, s);
        
        cout << s.size() / (overlap + 1) << endl;
    }
}
