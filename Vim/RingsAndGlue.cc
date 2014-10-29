#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>

#define EP 1e-10

using namespace std;

typedef vector<double> vd;
typedef vector<bool> vb;
typedef vector<vb> vvb;

int n;
vvb adjMatrix;

int dfs(int u, vb &visited)
{
    if (visited[u])
        return 0;

    visited[u] = true;

    int children = 0;
    for (int v = 0; v < n; ++v)
       if (adjMatrix[u][v])
           children += dfs(v, visited);
    
    return children + 1;
}

int main()
{
    while (1)
    {
        cin >> n;
        if (n == -1)
            break;

        vd x(n);
        vd y(n);
        vd r(n);

        for (int i = 0; i < n; ++i)
        {
            cin >> x[i] >> y[i] >> r[i];
        }

        adjMatrix = vvb(n, vb(n, false));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
            {
                double dist = sqrt(pow(x[i]-x[j], 2) + pow(y[i]-y[j], 2));
                adjMatrix[i][j] = dist <= r[i] + r[j] + EP && dist + min(r[i], r[j]) >= max(r[i], r[j]) - EP;
                //cout << i << ", " << j << ", " << adjMatrix[i][j] << endl;
            }

        vb visited(n, false);
        int maxC = 0;
        for (int i = 0; i < n; ++i)
        {
            maxC = max(maxC, dfs(i, visited));
        }

        printf("The largest component contains %d ring%s.\n", maxC, maxC == 1 ? "" : "s");
    }
}
