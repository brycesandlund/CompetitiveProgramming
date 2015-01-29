#include <iostream>
#include <cstdio>
#include <vector>

#define INF 1000000000000000000LL

using namespace std;

typedef long long ll;
typedef vector<string> vs;
typedef vector<ll> vi;

struct TrieNode
{
    ll wordCount;
    vector<TrieNode*> children;
    vi best;
    bool last;

    TrieNode()
    {
        last = false;
        wordCount = 0;
        children = vector<TrieNode*>(26, NULL);
    }

    void solve(ll K)
    {
        best = vi(min(wordCount+1, K+1), INF);
        best[0] = 0;

        for (ll i = 0; i < 26; ++i)
        {
            if (children[i] != NULL)
            {
                vi bestOld(best);

                for (ll j = 0; j < children[i]->best.size(); ++j)
                {
                    for (ll k = 0; j+k < best.size(); ++k)
                    {
                        best[j+k] = min(best[j+k], bestOld[k] + children[i]->best[j] + j);
                    }
                }
            }
        }

        if (last)
        {
            for (ll i = best.size()-1; i >= 1; --i)
            {
                best[i] = best[i-1];
            }
        }

        best[1] = 0;
    }
};

void solveAll(TrieNode *root, ll K)
{
    vector<TrieNode*> q;

    q.push_back(root);

    for (ll i = 0; i < q.size(); ++i)
    {
        for (ll j = 0; j < 26; ++j)
        {
            if (q[i]->children[j] != NULL)
                q.push_back(q[i]->children[j]);
        }
    }

    for (ll i = q.size()-1; i >= 0; --i)
    {
        q[i]->solve(K);
    }
}

void add(TrieNode *root, string &word)
{
    TrieNode *cur = root;

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

        TrieNode *root = new TrieNode;

        for (ll i = 0; i < N; ++i)
        {
            string word;
            cin >> word;
            add(root, word);
        }

        solveAll(root, K);

        printf("Case #%lld: %lld\n", caseNum, K == 1 ? 1 : root->best[K]);
    }
}
