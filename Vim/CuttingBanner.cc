#include <iostream>

using namespace std;

typedef long long ll;


int main() {
    string s;
    cin >> s;
    bool success = false;
    for (ll i = 0; i <= s.size(); ++i) {
        for (ll j = i; j <= s.size(); ++j) {
            string first = s.substr(0, i);
            string second = s.substr(j);
            string both = first + second;
            if (both == "CODEFORCES") {
                success = true;
            }
        }
    }

    if (success) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }
    return 0;
}
