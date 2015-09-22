#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

typedef long long ll;
typedef vector<char> vc;
typedef vector<vc> vvc;

void compose(vvc &bits, ll t, ll b, ll l, ll r, vc &result) {
    if (t > b || l > r)
        return;

    char output = bits[t][l];
    for (ll i = t; i <= b; ++i) {
        for (ll j = l; j <= r; ++j) {
            if (bits[i][j] != output) {
                output = 'D';
                goto OUTER;
            }
        }
    }

OUTER:
    result.push_back(output);
    if (output == 'D') {
        ll lmid = (l+r)/2;
        ll tmid = (t+b)/2;
        compose(bits, t, tmid, l, lmid, result);
        compose(bits, t, tmid, lmid+1, r, result);
        compose(bits, tmid+1, b, l, lmid, result);
        compose(bits, tmid+1, b, lmid+1, r, result);
    }
}

void decompose(ll t, ll b, ll l, ll r, vvc &bits) {
    if (t > b || l > r)
        return;

    char c;
    cin >> ws >> c;
    
    if (c == 'D') {
        ll lmid = (l+r)/2;
        ll tmid = (t+b)/2;
        decompose(t, tmid, l, lmid, bits);
        decompose(t, tmid, lmid+1, r, bits);
        decompose(tmid+1, b, l, lmid, bits);
        decompose(tmid+1, b, lmid+1, r, bits);
    }
    else {
        for (ll i = t; i <= b; ++i) {
            for (ll j = l; j <= r; ++j) {
                bits[i][j] = c;
            }
        }
    }
}

int main() {
    char map;
    for (ll cs = 1; cin >> ws >> map; ++cs) {
        if (map == '#')
            break;
        
        ll rows, cols;
        cin >> rows >> cols;
        
        vc result;
        if (map == 'B') {
            vvc bits(rows, vc(cols));
            for (ll i = 0; i < rows; ++i) {
                for (ll j = 0; j < cols; ++j) {
                    cin >> ws >> bits[i][j];
                }
            }
            compose(bits, 0, rows-1, 0, cols-1, result);
        }
        else {
            vvc bits(rows, vc(cols));
            decompose(0, rows-1, 0, cols-1, bits);

            for (ll i = 0; i < rows; ++i) {
                for (ll j = 0; j < cols; ++j) {
                    result.push_back(bits[i][j]);
                }
            }
        }

        printf("%c%4lld%4lld\n", map == 'D' ? 'B' : 'D', rows, cols);
        for (ll i = 0; i < result.size(); ++i) {
            if (i % 50 == 0 && i != 0)
                cout << endl;
            cout << result[i];
        }
        cout << endl;
    }
    return 0;
}
