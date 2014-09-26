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
typedef vector<vb> vvb;
typedef vector<ii> vii;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef long long LL;


int numPaths(int v, vvi &adjList, int cur, vector<LL> &npaths, vvi &dist)
{
	if (dist[cur][v] == INF)
		return 0;

	if (npaths[cur] == -2)
	{
		return -1;
	}

	if (npaths[cur] != -3)
		return npaths[cur];

	npaths[cur] = -2;

	LL curpathc = 0;
	for (int i = 0; i < adjList[cur].size(); ++i)
	{
		LL cp = numPaths(v, adjList, adjList[cur][i], npaths, dist);
		if (cp == -1)
		{
			curpathc = -1;
			break;
		}
		else
		{
			curpathc += cp;
		}
	}

	if (cur == v)
	{
		return npaths[cur] = curpathc == -1 ? -1 : 1;
	}

	return npaths[cur] = curpathc;
}

int main() {
	int caseNum = 0;
	int n;
	while (cin >> n)
	{
		vvi adjList(30);
		int maxn = -1;
		for (int i = 0; i < n; ++i)
		{
			int u, v;
			cin >> u >> v;
			adjList[u].push_back(v);
			maxn = max(maxn, max(u, v));
		}

		vvi dist(30, vi(30, INF));
		for (int i = 0; i < 30; ++i)
		{
			for (int j = 0; j < adjList[i].size(); ++j)
			{
				dist[i][adjList[i][j]] = 1;
			}
			dist[i][i] = 0;
		}

		for (int k = 0; k < 30; ++k)
			for (int i = 0; i < 30; ++i)
				for (int j = 0; j < 30; ++j)
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

		vector<vector<LL> > numpaths(maxn+1, vector<LL>(maxn+1, 0));
		for (int i = 0; i <= maxn; ++i)
		{
			for (int j = 0; j <= maxn; ++j)
			{
				vector<LL> paths(maxn+1, -3);
				numpaths[i][j] = numPaths(j, adjList, i, paths, dist);
				if (i == j && numpaths[i][j] > 0)
					numpaths[i][j] = 0;
			}
		}

		printf("matrix for city %d\n", caseNum++);
		for (int i = 0; i <= maxn; ++i)
		{
			cout << numpaths[i][0];
			for (int j = 1; j <= maxn; ++j)
			{
				cout << " " << numpaths[i][j];
			}
			cout << endl;
		}
	}
	return 0;
}
