#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <memory.h>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

const int inf = (int)1e8;
const int ALPHA = 26;

char word[12345678];

int main() {
  freopen("in", "r", stdin);
  freopen("out", "w", stdout);
  int tt;
  scanf("%d", &tt);
  for (int qq = 1; qq <= tt; qq++) {
    printf("Case #%d: ", qq);
    int cnt, k;
    scanf("%d %d", &cnt, &k);
    vector < vector <int> > trie;
    vector <int> end;
    trie.push_back(vector <int>(ALPHA, -1));
    end.push_back(0);
    int ans = 0;
    for (int i = 0; i < cnt; i++) {
      scanf("%s", word);
      int t = 0;
      for (int j = 0; word[j]; j++) {
        int c = word[j] - 'a';
        if (trie[t][c] == -1) {
          trie[t][c] = trie.size();
          trie.push_back(vector <int>(ALPHA, -1));
          end.push_back(0);
        }
        t = trie[t][c];
      }
      end[t] = 1;
    }
    int n = trie.size();
    vector < vector <int> > f(n, vector <int>(k + 1, inf));
    vector <int> g(k + 1);
    vector <int> ng(k + 1);
    for (int i = n - 1; i >= 0; i--) {
      for (int j = 0; j <= k; j++) {
        g[j] = inf;
      }
      g[0] = 0;
      if (end[i]) {
        g[1] = 0;
      }
      for (int c = 0; c < ALPHA; c++) {
        int u = trie[i][c];
        if (u == -1) {
          continue;
        }
        for (int x = 0; x <= k; x++) {
          ng[x] = inf;
        }
        for (int x = 0; x <= k; x++) {
          for (int y = 0; x + y <= k; y++) {
            int ft = g[x] + f[u][y] + y;
            if (ft < ng[x + y]) {
              ng[x + y] = ft;
            }
          }
        }
        for (int x = 0; x <= k; x++) {
          g[x] = ng[x];
        }
      }
      for (int x = 0; x <= k; x++) {
        f[i][x] = g[x];
      }
      f[i][1] = 0;
    }
    printf("%d\n", (k == 1 ? 1 : f[0][k]));
  }
  return 0;
}
