#include <iostream>

using namespace std;

typedef long long ll;

string exp;
ll l, r;
ll cur_int;

bool is_d(char c) {
    return c >= '0' && c <= '9';
}

void nextsym() {
    l = r+1;
    r = l;
    while (r < exp.size() && is_d(exp[r])) {
        ++r;
    }

    if (is_d(exp[l])) {
        --r;
        cur_int = stoi(exp.substr(l, r-l+1));
    }
}

bool accept(char s) {
    if (l < exp.size() && l == r && exp[l] == s) {
        nextsym();
        return true;
    }
    return false;
}

bool accept_int() {
    if (l < exp.size() && is_d(exp[l])) {
        nextsym();
        return true;
    }
    return false;
}

void expect(char s) {
    if (!accept(s))
        throw 20;
}

ll expression();

ll factor() {
    if (accept_int()) {
        return cur_int;
    }
    else {
        expect('(');
        ll ans = expression();
        expect(')');
        return ans;
    }
}

ll component() {
    ll ans = factor();
    if (accept('*')) {
        ans *= component();
    }
    return ans;
}

ll expression() {
    ll ans = component();
    if (accept('+')) {
        ans += expression();
    }
    return ans;
}

int main() {
    ll n;
    cin >> n;
    for (ll cs = 1; cs <= n; ++cs) {
        cin >> exp;
        l = r = -1;
        ll ans;
        bool success = true;

        try {
            nextsym();
            ans = expression();
        }
        catch (int e) {
            success = false;
        }

        if (l < exp.size()) {
            success = false;
        }

        if (success)
            cout << ans << endl;
        else
            cout << "ERROR" << endl;
    }
    return 0;
}
