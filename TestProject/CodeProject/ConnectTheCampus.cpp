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

vii loc;

double dist(int i, int j)
{
	return hypot(loc[j].first - loc[i].first, loc[j].second - loc[i].second);
}

//union-find set: the vector/array contains the parent of each node - lightweight version only implementing path compression from Stanford ACM
int find(vector<int>& C, int x){return (C[x]==x) ? x : C[x]=find(C, C[x]);} //C++

double kruskal(vector<pair<double, ii> > &EdgeList, int n)
{
		sort(EdgeList.begin(), EdgeList.end()); // sort by edge weight O(E log E)
                      // note: pair object has built-in comparison function

		double mst_cost = 0;
		vector<int> UF(n);
		for (int i = 0; i < n; ++i)
		{
			UF[i] = i;
		}

		int matched = 0;
		for (vector<pair<double, ii> >::iterator iter = EdgeList.begin(); iter != EdgeList.end() && matched < n-1; ) {                      // for each edge, O(E)
			pair<double, ii> front = *iter;
			int x = find(UF, front.second.first), y = find(UF, front.second.second);
			if (x != y) {  // check
				mst_cost += front.first;                // add the weight of e to MST
				UF[x] = UF[y];    // link them
				++matched;
			}        // note: the runtime cost of UFDS is very light
			++iter;
		}

		return matched == n-1 ? mst_cost : -1;
}



int main() {
	int N;
	while (cin >> N)
	{
		vvd adjMatrix(N, vd(N, INF));
		loc.clear();
		for (int i = 0; i < N; ++i)
		{
			int x, y;
			cin >> x >> y;
			loc.push_back(ii(x, y));
		}

		int M;
		cin >> M;
		for (int i = 0; i < M; ++i)
		{
			int u, v;
			cin >> u >> v;
			adjMatrix[u-1][v-1] = 0;
			adjMatrix[v-1][u-1] = 0;
		}

		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				adjMatrix[i][j] = min(adjMatrix[i][j], dist(i, j));
			}
		}

		vector<pair<double, ii> > edgeList;
		for (int i = 0; i < N; ++i)
		{
			for (int j = i+1; j < N; ++j)
			{
				edgeList.push_back(make_pair(adjMatrix[i][j], ii(i, j)));
			}
		}

		printf("%.2lf\n", kruskal(edgeList, N));
	}
	return 0;
}
