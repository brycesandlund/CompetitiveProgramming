#include <iostream>
#include <vector>
#include <climits>

using namespace std;



int Dfs(vector<vector<int> > &graph, vector<int> &state, int u, char l, string &s, vector<int> &ans) {
    if (state[u] == 0) { // cycle found!
        return INT_MAX;
    }
    else if (state[u] == 1) { // visited already
        return ans[u];
    }
    else {  // unvisited
        int best = 0;
        state[u] = 0;

        for (int i = 0; i < graph[u].size(); ++i) {
            int v = graph[u][i];

            best = max(best, Dfs(graph, state, v, l, s, ans));
        }
        
        state[u] = 1;
        if (s[u] == l) {
            ++best;
        }

        ans[u] = best;
        return ans[u];
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int> > graph(n);

    string s;
    cin >> s;

    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;

        --x;
        --y;

        graph[x].push_back(y);
    }

    int best = 0;
    for (char l = 'a'; l <= 'z'; ++l) {
        vector<int> state(n, -1);   //-1 -> unvisited
                                    //0 -> visited but not processed
                                    //1 -> visited and processed
    
        vector<int> ans(n);
        for (int i = 0; i < n; ++i) {
            if (state[i] == -1) {
                best = max(best, Dfs(graph, state, i, l, s, ans));
            }
        }
    }

    if (best == INT_MAX) {
        cout << -1 << endl;
    }
    else {
        cout << best << endl;
    }
}
