#include <iostream>
#include <vector>

#define INF 1000000000
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

using namespace std;

vvi rotate(vvi &grid)
{
    int n = grid.size();
    int m = grid[0].size();
    vvi result(m, vi(n));
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
        {
            result[i][j] = grid[n-j-1][i];
        }

    return result;
}

vvi vert_flip(vvi &grid)
{
    int n = grid.size();
    int m = grid[0].size();

    vvi result(n, vi(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
        {
            result[i][j] = grid[i][m-j-1];
        }

    return result;
}

int main()
{
    while (true)
    {
        int n, m;
        cin >> n >> m;

        if (n == 0 && m == 0)
            break;

        vvi grid(n, vi(m));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
            {
                char c;
                cin >> c;

                grid[i][j] = c == '.' ? 1 : -INF;
            }
        
        
    }
}
