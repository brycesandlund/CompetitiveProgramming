#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<bool> vb;

int main() {
    string s;
    cin >> s;
    ll m;
    cin >> m;
    vb flip(s.size(), false);
    
    for (ll i = 0; i < m; ++i) {
        ll ai;
        cin >> ai;
        --ai;
        flip[ai] = !flip[ai];
        
        if (ai != 0)
            flip[s.size()-ai] = !flip[s.size()-ai];
    }

    bool rev = false;
    for (ll i = 0; i < flip.size(); ++i) {
        if (flip[i])
            rev = !rev;

        if (rev)
            cout << s[s.size()-1-i];
        else
            cout << s[i];
    }

    cout << endl;

    return 0;
}
