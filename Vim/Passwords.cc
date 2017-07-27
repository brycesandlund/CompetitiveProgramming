#include <vector>
#include <string>
#include <cstring>
#include <queue>
#include <unordered_map>
#include <cctype>
#include <iostream>

#define MOD 1000003

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<string> vs;


struct node {
    unordered_map<char, node*> g;
    node* f;
    node* output = NULL;
    bool isWord = false;
    ll num;

    node(ll num, vector<node*> &automaton) : num(num) {
        automaton.push_back(this);
    }
};

vector<node*> automaton;

void enter(string S, node *root, ll &n) {
    node *state = root;
    ll j = 0;
    while (state->g.count(S[j]) != 0) {
        state = state->g[S[j]];
        ++j;
    }
    for (; j < S.size(); ++j) {
        state->g[S[j]] = new node(n++, automaton);
        state = state->g[S[j]];
    }
    state->isWord = true;
}

void construct_f(node* root) {
    queue<node*> q;
    for (auto it = root->g.begin(); it != root->g.end(); ++it) {
        q.push(it->second);
        it->second->f = root;
    }
    while (!q.empty()) {
        node *r = q.front(); q.pop();
        for (auto it = r->g.begin(); it != r->g.end(); ++it) {
            q.push(it->second);
            node *state = r->f;
            while(state->g.count(it->first) == 0 && state->num != 0)
                state = state->f;
            if (state->g.count(it->first) != 0)
                it->second->f = state->g[it->first];
            else
                it->second->f = root;
            if (it->second->f->isWord)
                it->second->output = it->second->f;
            else
                it->second->output = it->second->f->output;
        }
    }
}

node* ConstructAutomaton(vs &dictionary) {
    ll n = 0;
    node *root = new node(n++, automaton);
    for (ll i = 0; i < dictionary.size(); ++i) {
        enter(dictionary[i], root, n);
    }
    construct_f(root);
    return root;
}

node* advance(node *state, char c) {
    while (state->g.count(c) == 0 && state->num != 0) state = state->f;
    if (state->g.count(c) != 0)
        state = state->g[c];
    return state;
}

bool isWord(node *state) {
    if (state->isWord)
        return true;
    if (state->output != NULL)
        return true;
    return false;
}

char leet(char c) {
    switch (c) {
        case '0': return 'o';
        case '1': return 'i';
        case '3': return 'e';
        case '5': return 's';
        case '7': return 't';
        default: return c;
    }
}

ll dp[22][2][2][2][1000];
// dp[S][L][U][D][N] = number of passwords of length S with L = lower?,
// U = upper?, D = digit?, ending with node N in automaton

int main() {
    ll A, B, N;
    cin >> A >> B >> N;

    vs W(N);
    for (ll i = 0; i < N; ++i) {
        cin >> W[i];
    }

    node* root = ConstructAutomaton(W);

    memset(dp, 0, sizeof(dp));
    dp[0][0][0][0][0] = 1;

    for (ll i = 0; i <= B; ++i) {
        for (ll j = 0; j < 2; ++j) {
            for (ll k = 0; k < 2; ++k) {
                for (ll l = 0; l < 2; ++l) {
                    for (ll m = 0; m < automaton.size(); ++m) {
                        if (isWord(automaton[m])) {
                            dp[i][j][k][l][m] = 0;
                        }
                        if (dp[i][j][k][l][m] != 0) {
                            for (char c = 'a'; c <= 'z'; ++c) {
                                node* next = advance(automaton[m], c);
                                dp[i+1][1][k][l][next->num] = (dp[i+1][1][k][l][next->num] + dp[i][j][k][l][m]) % MOD;
                            }
                            for (char c = 'A'; c <= 'Z'; ++c) {
                                node* next = advance(automaton[m], (char)tolower(c));
                                dp[i+1][j][1][l][next->num] = (dp[i+1][j][1][l][next->num] + dp[i][j][k][l][m]) % MOD;
                            }
                            for (char c = '0'; c <= '9'; ++c) {
                                node* next = advance(automaton[m], leet(c));
                                dp[i+1][j][k][1][next->num] = (dp[i+1][j][k][1][next->num] + dp[i][j][k][l][m]) % MOD;
                            }
                        }
                    }
                }
            }
        }
    }

    ll ans = 0;
    for (ll i = A; i <= B; ++i) {
        for (ll m = 0; m < automaton.size(); ++m) {
            ans = (ans + dp[i][1][1][1][m]) % MOD;
        }
    }

    cout << ans << endl;
}
