#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <cmath>
#include <map>
#include <set>
#include <cstdio>

#define INF 10000000000000LL
#define EP 1e-10

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<string> vs;
typedef pair<ll, ll> ii;
typedef pair<ll, ii> iii;
typedef vector<iii> viii;
typedef vector<viii> vviii;
typedef vector<vviii> vvviii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<vvii> vvvii;

ll convertFrom(char c) {
    if (c == ' ')
        return 0;
    else
        return c - '`';
}

char convertTo(ll c) {
    if (c == 0)
        return ' ';
    else
        return c + '`';
}

int main() {
    ll n;
    cin >> n;
    string line;
    getline(cin, line);

    for (ll i = 0; i < n; ++i) {
        char c;
        cin >> c;

        char blah;
        cin.get(blah);
        vi line_number;
        while (true) {
            char cur;
            cin.get(cur);

            if (cur == '\n')
                break;

            line_number.push_back(convertFrom(cur));
        }

        ll length = line_number.size();

        vi result(line_number);
        if (c == 'e') {
            for (ll i = 1; i < length; ++i) {
                result[i] += result[i-1];
                result[i] %= 27;
            }
        }
        else {
            for (ll i = 1; i < length; ++i) {
                while (result[i] < result[i-1])
                    result[i] += 27;
            }
            
            for (ll i = length-1; i >= 1; --i) {
                result[i] -= result[i-1];
            }
        }

        for (ll i = 0; i < length; ++i) {
            cout << convertTo(result[i]);
        }
        cout << endl;
    }
}
