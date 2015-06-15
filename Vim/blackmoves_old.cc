#include <iostream>
#include <cmath>

using namespace std;

typedef long long ll;

void getPos(ll &r, ll &c) {
    char ch;
    cin >> ws >> ch;
    r = ch - 'a';
    cin >> ws >> ch;
    c = ch - '1';
}

bool kAttack(ll kr, ll kc, ll r, ll c) {
    return abs(kr - r) <= 1 && abs(kc - c) <= 1;
}

bool between(ll x, ll y, ll z) {
    return z >= min(x, y) && z <= max(x, y);
}

bool rAttack(ll kr, ll kc, ll rr, ll rc, ll r, ll c) {
    if (rr == r && rc == c)
        return false;
    if (rr == r && !between(rc, c, kc))
        return true;
    if (rc == c && !between(rr, r, kr))
        return true;
    return false; 
}

bool attacked(ll kr, ll kc, ll rr, ll rc, ll r, ll c) {
    //cerr << "here: " << r << " " << c << " " << rAttack(kr, kc, rr, rc, r, c) << endl;
    return (rAttack(kr, kc, rr, rc, r, c) || kAttack(kr, kc, r, c));
}

int main() {
    ll wkr, wkc, wrr, wrc, bkr, bkc;

    getPos(wkr, wkc);
    getPos(wrr, wrc);
    getPos(bkr, bkc);

    if (kAttack(wkr, wkc, bkr, bkc)) {
        cout << "Strange" << endl;
    }
    else {
        bool makeValidMove = false;
        for (ll i = bkr-1; i <= bkr+1; ++i) {
            for (ll j = bkc-1; j <= bkc+1; ++j) {
                if (i < 0 || i >= 8 || j < 0 || j >= 8)
                    continue;
                if (i == bkr && j == bkc)
                    continue;
                if (!attacked(wkr, wkc, wrr, wrc, i, j))
                {
                //    cerr << i << " " << j << endl;
                    makeValidMove = true;
                }
            }
        }

        bool threatened = attacked(wkr, wkc, wrr, wrc, bkr, bkc);
        if (!threatened && makeValidMove) {
            cout << "Normal" << endl;
        }
        else if (threatened && makeValidMove) {
            cout << "Check" << endl;
        }
        else if (!threatened && !makeValidMove) {
            cout << "Stalemate" << endl;
        }
        else
            cout << "Checkmate" << endl;
    }
}
