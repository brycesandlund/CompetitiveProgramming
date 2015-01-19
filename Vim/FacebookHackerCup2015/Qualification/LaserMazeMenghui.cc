#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

#define N (110)

using namespace std;

int dy[] = {1, 0, -1, 0}, dx[] = {0, 1, 0, -1};

int get_dir(char c) {
    if (c == '>')
        return 0;
    else if (c == 'v')
        return 1;
    else if (c == '<')
        return 2;
    else if (c == '^')
        return 3;
    else
        return -1;
}

int m, n;
char map[N][N], a[4][N][N];
bool visited[4][N][N];

bool in_range(int i, int j) {
    return i >= 0 && i < m && j >= 0 && j < n;
}

class state {
public:
    int i;
    int j;
    int steps;

    state(int x, int y, int t)
        : i(x), j(y), steps(t) {}
};

int main() {
    int T;
    cin >> T;
    for (int cs = 1; cs <= T; ++cs) {
        cin >> m >> n;
        for (int i = 0; i < m; ++i)
            cin >> map[i];
        for (int r = 0; r < 4; ++r) {
            for (int i = 0; i < m; ++i)
                for (int j = 0; j < n; ++j) {
                    a[r][i][j] = map[i][j];
                    int dir = get_dir(map[i][j]);
                    if (dir >= 0)
                        a[r][i][j] = '#';
                }
        }
        for (int r = 0; r < 4; ++r) {
            for (int i = 0; i < m; ++i)
                for (int j = 0; j < n; ++j) {
                    int dir = get_dir(map[i][j]);
                    if (dir >= 0) {
                        dir = (dir + 1 + r) % 4;
                        int ox = i, oy = j;
                        while (true) {
                            ox += dx[dir];
                            oy += dy[dir];
                            if (!in_range(ox, oy))
                                break;
                            int next_dir = get_dir(map[ox][oy]);
                            if (map[ox][oy] == '#' || next_dir >= 0)
                                break;
                            a[r][ox][oy] = '#';
                        }
                    }
                }
        }
        memset(visited, 0, sizeof(visited));
        queue<state> q;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (map[i][j] == 'S') {
                    q.push(state(i, j, 0));
                    visited[0][i][j] = true;
                }
        int ans = -1;
        while (!q.empty()) {
            state curr = q.front();
            q.pop();
            int index = curr.steps % 4;
            if (map[curr.i][curr.j] == 'G') {
                ans = curr.steps;
                break;
            }
            for (int r = 0; r < 4; ++r) {
                int ni = curr.i + dx[r], nj = curr.j + dy[r];
                if (in_range(ni, nj) && a[index][ni][nj] != '#' && !visited[(index + 1) % 4][ni][nj]) {
                    state n(ni, nj, curr.steps + 1);
                    q.push(n);
                    visited[(index + 1) % 4][ni][nj] = true;
                }
            }
        }
        if (ans == -1)
            cout << "Case #" << cs << ": impossible" << endl;
        else
            cout << "Case #" << cs << ": " << ans << endl;
    }
    return 0;
}