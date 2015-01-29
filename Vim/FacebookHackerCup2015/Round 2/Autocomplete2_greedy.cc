#include <iostream>
#include <cstdio>
#include <vector>

#define INF 1000000000000000000LL

using namespace std;

typedef long long ll;
typedef vector<string> vs;

struct TrieNode
{
    ll wordCount;
    vector<TrieNode*> children;
    bool last;

    TrieNode()
    {
        last = false;
        wordCount = 0;
        children = vector<TrieNode*>(26, NULL);
    }
};

ll query(TrieNode* root, string &word)
{
    TrieNode* cur = root;

    ll cost = 0;
    for (ll i = 0; i < word.size(); ++i)
    {
        ll idx = word[i]-'a';
        cur = cur->children[idx];

        ++cost;
        if (cur == NULL)
            return cost;

        if (cur->wordCount == 1 && !cur->last)
        {
            ++cost;
        }
    }

    return cost;
}

void add(TrieNode* root, string &word)
{
    TrieNode* cur = root;

    for (ll i = 0; i <= word.size(); ++i)
    {
        cur->wordCount++;

        if (i == word.size())
        {
            cur->last = true;
            return;
        }

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
        ll N, K;
        cin >> N >> K;

        vs words(N);
        for (ll i = 0; i < N; ++i)
        {
            cin >> words[i];
        }

        TrieNode* root = new TrieNode;

        ll totalCost = 0;
        for (ll i = 0; i < K; ++i)
        {
            ll minCost = INF;
            ll minIdx;
            for (ll j = 0; j < words.size(); ++j)
            {
                ll curCost = query(root, words[j]);

                if (curCost < minCost)
                {
                    minCost = curCost;
                    minIdx = j;
                } 
            }

            totalCost += minCost;
            add(root, words[minIdx]);
            words.erase(words.begin()+minIdx);
        }

        printf("Case #%lld: %lld\n", caseNum, totalCost);
    }
}
