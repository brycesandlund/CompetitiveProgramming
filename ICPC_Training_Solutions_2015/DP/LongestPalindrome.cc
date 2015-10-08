#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;

int main() {
    ll T;
    cin >> T;
    string blah;
    getline(cin, blah);
    for (ll cs = 1; cs <= T; ++cs) {
        string s;
        getline(cin, s);
        vvi longest(s.size(), vi(s.size(), 1));
        
        for (ll i = 1; i < s.size(); ++i)
            longest[i-1][i] = s[i-1] == s[i] ? 2 : 1;

        for (ll i = 2; i < s.size(); ++i) {
            for (ll j = i; j < s.size(); ++j) {
                if (s[j-i] == s[j]) {
                    longest[j-i][j] = longest[j-i+1][j-1] + 2;
                }
                longest[j-i][j] = max(longest[j-i][j], max(longest[j-i+1][j], longest[j-i][j-1]));
            }
        }
        if (s.size() == 0)
            cout << 0 << endl;
        else
            cout << longest[0][s.size()-1] << endl;
    }
    return 0;
}
