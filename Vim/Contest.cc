#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int main() {
    ll n;
    cin >> n;

    bool good = false;
    for (ll i = 0; i < n; ++i) {
        string name;
        ll before;
        ll after;
        cin >> name >> before >> after;

        if (before >= 2400 && after > before) {
            good = true;
        }
    }
    if (good)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    return 0;
}
