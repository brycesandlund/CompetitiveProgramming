#include <iostream>
#include <fstream>

using namespace std;

typedef long long ll;

int main() {
    ifstream cin("input.txt");
    ofstream cout("output.txt");
    
    ll h, w;
    cin >> h >> w;

    if (h == 1 || w == 1)
        cout << 0 << endl;
    else {
        ll horizontal = (h/2) * (w-1);
        ll vertical = (w/2) * (h-1);
        if (horizontal >= vertical) {
            cout << horizontal << endl;
            for (ll i = 1; i < h; i += 2) {
                for (ll j = 1; j < w; ++j) {
                    cout << i << " " << j << endl;
                }
            }   
        }
        else {
            cout << vertical << endl;
            for (ll i = 1; i < w; i += 2) {
                for (ll j = 1; j < h; ++j) {
                    cout << j << " " << i << endl;
                }
            }
        }
    }
}
