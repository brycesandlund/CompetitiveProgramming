//============================================================================
// Name        :
// Author      : Bryce Sandlund
// Version     :
// Copyright   :
// Description : Code skeleton
//============================================================================

#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include <algorithm>
#include <cmath>
#include <complex>
#include <cstdlib>
#include <sstream>
#include <list>
#include <map>
#include <fstream>
#include <string>
#include <time.h>
#include <queue>
#include <tuple>
#include <functional>
#include <unordered_set>
#include <unordered_map>

#define INF 1000000000
#define all(c) (c).begin(),(c).end()
#define tr(c,i) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define EP .00001

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef long long LL;

int main() {
	int N;
	cin >> N;
	for (int caseNum = 1; caseNum <= N; ++caseNum)
	{
		int n, m;
		cin >> n >> m;
		vvi dist(n, vi(n, INF));
		vii edgeList;
		for (int i = 0; i < m; ++i)
		{
			int u, v;
			cin >> u >> v;
			edgeList.push_back(ii(u, v));
			dist[u][v] = dist[v][u] = 1;
		}

		for (int i = 0; i < n; ++i)
			dist[i][i] = 0;

		for (int k = 0; k < n; ++k)
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j)
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

		int maxRopes = -1;
		for (int i = 0; i < n; ++i)
		{
			for (int j = i+1; j < n; ++j)
			{
				int curRopes = 0;
				for (int k = 0; k < edgeList.size(); ++k)
				{
					int u = edgeList[k].first;
					int v = edgeList[k].second;

					if (dist[i][u]+1+dist[v][j] == dist[i][j] || dist[i][v]+1+dist[u][j] == dist[i][j])
					{
						++curRopes;
					}
				}

				maxRopes = max(maxRopes, curRopes);
			}
		}

		printf("Case #%d: %d\n", caseNum, maxRopes);
	}
	return 0;
}
