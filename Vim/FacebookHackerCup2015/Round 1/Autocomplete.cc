#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

typedef long long ll;

struct TrieNode
{
    ll wordCount;
    vector<TrieNode*> children;

    TrieNode()
    {
        wordCount = 0;
        children = vector<TrieNode*>(26, NULL);
    }
};

ll query(TrieNode* root, string &word)
{
    TrieNode* cur = root;

    for (ll i = 0; i < word.size(); ++i)
    {
        if (cur->wordCount == 1 && cur != root)
            return i;

        ll idx = word[i]-'a';

        cur = cur->children[idx];
    }

    return word.size();
}

void add(TrieNode* root, string &word)
{
    TrieNode* cur = root;

    for (ll i = 0; i <= word.size(); ++i)
    {
        cur->wordCount++;

        if (i == word.size())
            return;

        ll idx = word[i]-'a';
        
        if (cur->children[idx] == NULL)
            cur->children[idx] = new TrieNode;

        cur = cur->children[idx];
    }
}

int main()
{
    ll T;
    cin >> T;

    for (ll caseNum = 1; caseNum <= T; ++caseNum)
    {
        ll N;
        cin >> N;

        TrieNode* root = new TrieNode;

        ll count = 0;
        for (ll i = 0; i < N; ++i)
        {
            string word;
            cin >> word;

            add(root, word);
            count += query(root, word);
        }

        printf("Case #%lld: %lld\n", caseNum, count);
    }
}
