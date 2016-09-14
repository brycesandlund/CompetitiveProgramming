#include <iostream>

using namespace std;

typedef long long ll;

int main() {

    string S;
    getline(cin, S);

    for (ll i = 0; i < S.size(); ++i) {
        cout << S[i];
        if (S[i] == 'a' || S[i] == 'e' || S[i] == 'i' || S[i] == 'o' || S[i] == 'u') {
            i += 2;
        }
    }
    cout << endl;

    return 0;
}
