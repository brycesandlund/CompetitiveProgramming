#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

typedef long long ll;
typedef vector<string> vs;

bool subseq(string a, string p) {
    ll j = 0;
    for (ll i = 0; i < p.size(); ++i) {
        if (p[i] == a[j]) {
            ++j;
            if (j == a.size()) {
                break;
            }
        }
    }
    return j == a.size();
}

bool lencompare(string a, string b) {
    return a.size() < b.size();
}

ll deep_recursion(ll n) {
    if (n > 0)
        return deep_recursion(n-1)+1;
    else
        return 0;
}

int main() {
//    ll test = deep_recursion(1000000000000000LL);
//    cout << test << endl;
    
    
    ll n;
    for (ll cs = 1; cin >> n; ++cs) {
        string final;
        cin >> final;
        vs DNA(n);
        for (ll i = 0; i < DNA.size(); ++i)
            cin >> DNA[i];

        sort(DNA.begin(), DNA.end(), lencompare);

        vs P1, P2, delayed;
        P1.push_back(DNA[0]);
        ll i;
        for (i = 1; i < n; ++i) {
            if (subseq(P1.back(), DNA[i]))
                P1.push_back(DNA[i]);
            else {
                P2.push_back(DNA[i]);
                break;
            }
        }

        // GReeDY :D
        bool success = true;
        ++i;
        for (; i < n; ++i) {
            if (delayed.empty() && subseq(P1.back(), DNA[i]) && subseq(P2.back(), DNA[i])) {
                delayed.push_back(DNA[i]);
            }
            else if (!delayed.empty() && subseq(delayed.back(), DNA[i])) {
                delayed.push_back(DNA[i]);
            }
            else if (subseq(P1.back(), DNA[i])) {
                P2.insert(P2.end(), delayed.begin(), delayed.end());
                delayed.clear();
                P1.push_back(DNA[i]);
                P1.back() = DNA[i];
            }
            else if (subseq(P2.back(), DNA[i])) {
                P1.insert(P1.end(), delayed.begin(), delayed.end());
                delayed.clear();
                P2.push_back(DNA[i]);
            }
            else {
                success = false;
                break;
            }
        }
        if (success) {
            if (!delayed.empty()) {
                P1.insert(P1.end(), delayed.begin(), delayed.end());
                delayed.clear();
            }
            if (!P1.empty() && !subseq(P1.back(), final))
                success = false;
            if (!P2.empty() && !subseq(P2.back(), final))
                success = false;
        }

        if (success) {
            cout << P2.size() << " " << P1.size() << endl;
            for (ll j = 0; j < P2.size(); ++j) {
                cout << P2[j] << endl;
            }
            for (ll j = 0; j < P1.size(); ++j) {
                cout << P1[j] << endl;
            }
        }
        else {
            cout << "impossible" << endl;
        }
    }
    return 0;
}
