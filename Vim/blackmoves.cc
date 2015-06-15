#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<bool> vb;
typedef vector<vb> vvb;

int dr[] = {0, 1, 0, -1};
int dc[] = {1, 0, -1, 0};

void getPos(ll &r, ll &c) {
    char ch;
    cin >> ws >> ch;
    r = ch - 'a';
    cin >> ws >> ch;
    c = ch - '1';
}

int main() {
    ll wkr, wkc, wrr, wrc, bkr, bkc;

    getPos(wkr, wkc);
    getPos(wrr, wrc);
    getPos(bkr, bkc);

    vvb kAttack(8, vb(8, false));
    for (ll i = wkr-1; i <= wkr+1; ++i) {
        for (ll j = wkc-1; j <= wkc+1; ++j) {
            if (i < 0 || i >= 8 || j < 0 || j >= 8)
                continue;
            if (i == wkr && j == wkc)
                continue;
            kAttack[i][j] = true;
        }
    }

    vvb rAttack(8, vb(8, false));
    for (ll i = 0; i < 4; ++i) {
        for (ll j = 1; true; ++j) {
            ll newr = wrr + dr[i]*j;
            ll newc = wrc + dc[i]*j;

            if (newr < 0 || newr >= 8 || newc < 0 || newc >= 8)
                break;

            if (newr == wkr && newc == wkc)
                break;

            rAttack[newr][newc] = true;
        }
    }

    if (kAttack[bkr][bkc]) {
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
                
                if (!rAttack[i][j] && !kAttack[i][j])
                    makeValidMove = true;
            }
        }
        bool threatened = rAttack[bkr][bkc] || kAttack[bkr][bkc];
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
