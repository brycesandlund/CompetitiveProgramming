#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;

ll charToInt(char c) {
    if (c == 'A')
        return 0;
    else if (c == 'C')
        return 1;
    else if (c == 'G')
        return 2;
    else
        return 3;
}

struct TrieNode {
    vector<TrieNode*> children;
    ll count;

    TrieNode() {
        children = vector<TrieNode*>(4);
        count = 0;
    }
};

ii add(TrieNode *root, string S) {
    TrieNode *cur = root;
    ll dupdepth = 0;
    ll occurrences;
    for (ll i = 0; i < S.size(); ++i) {
        if (cur->children[charToInt(S[i])] == NULL)
            cur->children[charToInt(S[i])] = new TrieNode;

        TrieNode *next = cur->children[charToInt(S[i])];
        next->count++;
        if (next->count > 1) {
            dupdepth = i+1;
            occurrences = next->count;
        }
        
        cur = next;
    }

    return ii(dupdepth, occurrences);
}

int main() {
    ll T;
    cin >> T;
    for (ll cs = 1; cs <= T; ++cs) {
        string S;
        cin >> S;

        TrieNode* root = new TrieNode;
        ll occurrences;
        string longest = "";
        for (ll i = 0; i < S.size(); ++i) {
            ii result = add(root, S.substr(i));
            string curbest = S.substr(i, result.first);
            if (result.first > longest.size() || (result.first == longest.size() && curbest < longest) || longest == curbest) {
                longest = S.substr(i, result.first);
                occurrences = result.second;
            }
        }
        if (longest == "") {
            cout << "No repetitions found!" << endl;
        }
        else {
            cout << longest << " " << occurrences << endl;
        }
    }
}
