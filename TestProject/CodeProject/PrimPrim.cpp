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
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef vector<bool> vb;
typedef long long LL;

// generates a vector of subsets for the nCr subsets of n
void subsetsRec(vector<int> &subsets, int curSet, int n, int r)
{
	if (n == 0)
	{
		subsets.push_back(int(curSet));
	}
	else
	{
		if (r > 0)
		{
			curSet |= 1 << (n-1);
			subsetsRec(subsets, curSet, n-1, r-1);
			curSet ^= 1 << (n-1);
		}

		if (r < n)
		{
			subsetsRec(subsets, curSet, n-1, r);
		}
	}
}

bool visitedAll(vb &visited)
{
	for (int i = 0; i < visited.size(); ++i)
	{
		if (!visited[i]) return false;
	}
	return true;
}

void dfs(vvi &adjMatrix, vb &visited, int u, bool remove)
{
	visited[u] = true;
	for (int v = 0; v < adjMatrix.size(); ++v)
	{
		if (adjMatrix[u][v] && !visited[v])
		{
			if (remove)
			{
				--adjMatrix[u][v];
				--adjMatrix[v][u];
				vb dupV(visited);
				dfs(adjMatrix, dupV, v, false);
				if (!visitedAll(dupV))
				{
					++adjMatrix[u][v];
					++adjMatrix[v][u];
					continue;
				}
			}

			dfs(adjMatrix, visited, v, remove);
		}
	}
}

//Incorrect algorithm... Does not work.

int main() {

	for (int caseNum = 1; true; ++caseNum)
	{
		int n, m;
		cin >> n >> m;
		if (n == 0)
		{
			break;
		}

		vector<pair<int, ii> > EdgeList;
		for (int i = 0; i < m; ++i)
		{
			int u, v, w;
			cin >> u >> v >> w;
			EdgeList.push_back(make_pair(w, ii(u-1, v-1)));
		}

		vector<int> subsets;
		subsetsRec(subsets, 0, m, (n-1)*2);
		vii weightSet;
		for (int i = 0; i < subsets.size(); ++i)
		{
			vector<pair<int, ii> >::reverse_iterator iter = EdgeList.rbegin();
			int weight = 0;
			int mask = subsets[i];
			for (; mask != 0; mask >>= 1)
			{
				if (mask & 1)
					weight += iter->first;
				++iter;
			}

			weightSet.push_back(ii(weight, subsets[i]));
		}

		sort(weightSet.begin(), weightSet.end());

		int low = 0, high = weightSet.size();
		while (high - low > 1)
		{
			int mid = (high-low)/2 + low;
			bool success = false;
			for (multimap<int, int>::iterator iter = weightSet.equal_range(mid).first; iter != weightSet.equal_range(mid).second; ++iter)
			{
				vector<pair<int, ii> >::reverse_iterator edgeIter = EdgeList.rbegin();
				int weight;
				int mask = iter->second;
				vvi adjMatrix(n, vi(n, 0));
				for (; mask != 0; mask >>= 1)
				{
					if (mask & 1)
					{
						int u = edgeIter->second.first;
						int v = edgeIter->second.second;
						++adjMatrix[u][v];
						++adjMatrix[v][u];
					}

					++edgeIter;
				}

				vb visited(n, false);
				dfs(adjMatrix, visited, 0, true);
				if (visitedAll(visited))
				{
					success = true;
					break;
				}
			}

			if (success)
			{
				high = mid;
			}
			else
			{
				low = mid == low ? mid+1 : mid;
			}
		}

		if (low == -1)
			cout << "No way!" << endl;
		else
			cout << low << endl;
	}

	return 0;
}
