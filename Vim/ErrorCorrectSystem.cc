#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;


int main() {
    ll n;
    cin >> n;
    string S, T;
    cin >> S >> T;

    vi has(26, -1);
    vvi hasAndWant(26, vi(26, -1));
    for (ll i = 0; i < n; ++i) {
        if (S[i] != T[i]) {
            has[T[i]-'a'] = i;
            hasAndWant[T[i]-'a'][S[i]-'a'] = i;
        }
    }

    ll best_i = -2, best_j = -2;
    for (ll i = 0; i < n; ++i) {
        if (S[i] != T[i]) {
            if (hasAndWant[S[i]-'a'][T[i]-'a'] != -1) {
                best_i = hasAndWant[S[i]-'a'][T[i]-'a'];
                best_j = i;
                break;
            }
            else if (has[S[i]-'a'] != -1) {
                best_i = has[S[i]-'a'];
                best_j = i;
            }
        }
    }

    if (best_i != -2 && best_j != -2)
        swap(T[best_i], T[best_j]);

    ll hamming = 0;
    for (ll i = 0; i < n; ++i) {
        if (S[i] != T[i])
            ++hamming;
    }

    cout << hamming << endl;
    cout << best_i+1 << " " << best_j+1 << endl;
}
