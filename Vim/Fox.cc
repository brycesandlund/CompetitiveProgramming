#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;

int main () {
    ll N;
    cin >> N;
    string phrase;
    getline(cin, phrase);
    for (ll i = 0; i < N; ++i) {
        getline(cin, phrase);

        vb letter(26, false);
        for (ll i = 0; i < phrase.size(); ++i) {
            phrase[i] = tolower(phrase[i]);
            if (phrase[i] >= 'a' && phrase[i] <= 'z') {
                letter[phrase[i] - 'a'] = true;
            }
        }
        bool success = true;
        for (ll i = 0; i < 26; ++i) {
            if (!letter[i]) {
                success = false;
            }
        }

        if (success)
            cout << "pangram" << endl;
        else {
            cout << "missing ";
            for (ll i = 0; i < 26; ++i) {
                if (!letter[i])
                    cout << (char)('a' + i);
            }
            cout << endl;
        }
    }
}
