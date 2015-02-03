#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

ll readInt(string &str, ll spot) {
    ll lo = spot, hi = spot;
    while (lo >= 0 && isDigit(str[lo])) --lo;
    while (hi < str.size() && isDigit(str[hi])) ++hi;

    string num = str.substr(lo+1, hi-lo-1);
    return atoi(num.c_str());
}

void readNum(string &eq, ll spot, vi &result) {
    ll E = 1, C = 1;
    if (eq[spot+1] == '^') {
        E = readInt(eq, spot+2);
    }

    if (isDigit(eq[spot-1])) {
        C = readInt(eq, spot-1);
    }

    for (ll i = spot; i >= 0; --i) {
        if (eq[i] == '+' || eq[i] == '(')
            break;
        else if (eq[i] == '-') {
            C *= -1;
            break;
        }
    }

    result[E] = C;
}

ll powMod(ll n, ll e, ll m) {
    if (e == 0)
        return 1;
    else if (e % 2 == 0) {
        ll small = powMod(n, e/2, m);
        return (small * small) % m;
    }
    else
        return (n * powMod(n, e-1, m)) % m;
}

int main() {
    for (ll caseNum = 1; true; ++caseNum) {
        string eq;
        cin >> eq;

        if (eq == ".")
            break;

        ll D = readInt(eq, eq.size()-1);
        vi result(101, 0);
      
        for (ll i = eq.size()-1; i >= 0; --i) {
            if (eq[i] == ')') {
                if (isDigit(eq[i-1])) {
                    for (ll j = i-1; j >= 0; --j) {
                        if (!isDigit(eq[j])) {
                            if (eq[j] != '^') {
                                result[0] = readInt(eq, j+1);
                                
                                if (eq[j] == '-') {
                                    result[0] *= -1;
                                }
                            }

                            break;
                        }
                    }
                }
            }
        }

        for (ll i = 0; i < eq.size(); ++i) {
            if (eq[i] == 'n') {
                readNum(eq, i, result);
            }
        }

        /*for (ll i = 0; i < 101; ++i) {
            cerr << i << ": " << result[i] << endl;
        }*/

        bool success = true;
        for (ll num = 1; num <= 101; ++num) {
            ll total = 0;

            for (ll i = 0; i < result.size(); ++i) {
                total = (total + (powMod(num, i, D) * result[i])%D) % D;
            }

            if (total != 0) {
                success = false;
                break;
            }
        }

        if (success)
            printf("Case %lld: Always an integer\n", caseNum);
        else
            printf("Case %lld: Not always an integer\n", caseNum);
    }

    return 0;
}
