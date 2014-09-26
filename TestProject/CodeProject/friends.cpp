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

int dfs(vb &visited, vvi &adjList, int u)
{
	if (visited[u])
		return 0;

	visited[u] = true;
	int count = 1;
	for (int i = 0; i < adjList[u].size(); ++i)
	{
		count += dfs(visited, adjList, adjList[u][i]);
	}

	return count;
}

int main() {
	int T;
	cin >> T;
	for (int caseNum = 1; caseNum <= T; ++caseNum)
	{
		int N, M;
		cin >> N >> M;
		set<ii> friends;
		vvi adjList(N, vi());
		
		for (int i = 0; i < M; ++i)
		{
			int u, v;
			cin >> u >> v;
			--u, --v;
			if (!friends.count(ii(u, v)) && !friends.count(ii(v, u)))
			{
				adjList[u].push_back(v);
				adjList[v].push_back(u);
				friends.insert(ii(u, v));
			}
		}

		vb visited(N, false);
		int maxC = -1;
		for (int i = 0; i < N; ++i)
		{
			if (!visited[i])
			{
				maxC = max(maxC, dfs(visited, adjList, i));
			}
		}

		cout << maxC << endl;
	}
	return 0;
}
