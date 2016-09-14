#include <iostream>

using namespace std;

typedef long long ll;

int main() {
    string s;
    cin >> s;
    for (ll i = 1; i < s.size(); ++i) {
        if (s[i] == s[i-1]) {
            for (ll c = 'a'; c <= 'z'; ++c) {
                if (s[i-1] != c && (i+1 == s.size() || s[i+1] != c)) {
                    s[i] = c;
                    break;
                }
            }
        }
    }
    cout << s << endl;
    return 0;
}
