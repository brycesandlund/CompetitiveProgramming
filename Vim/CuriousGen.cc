#include <iostream>

using namespace std;

typedef long long ll;

int main() {
    cout << "50000 50000 1000000" << endl;
    for (ll i = 0; i < 50000; ++i) {
        cout << rand() % 1000000 << " ";
    }
    for (ll i = 0; i < 50000; ++i) {
        cout << rand() % 1000000 << " ";
    }
    
    for (ll i = 0; i < 50000; ++i) {
        cout << min(i, 50000-i) << " " << max(i, 50000-i) << " " << endl;
    }

    /*
    cout << "50000 50000 1000000" << endl;
    for (ll i = 0; i < 50000; ++i) {
        cout << rand() % 1000000 << " ";
    }
    for (ll i = 0; i < 50000; ++i) {
        cout << rand() % 1000000 << " ";
    }
    for (ll i = 0; i < 50000; ++i) {
        ll first = rand() % 50000;
        ll second = rand() % 50000;
        cout << min(first, second) << " " << max(first, second) << " " << endl;
    }*/
}
