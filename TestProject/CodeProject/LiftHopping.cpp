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

#define MAXS 105

int main() {
	int n, k;
	while (cin >> n >> k)
	{
		vi timePerFloor(n);
		for (int i = 0; i < n; ++i)
			scanf("%d", &timePerFloor[i]);

		vvi adjMatrix(MAXS, vi(MAXS, INF));
		string s;
		getline(cin, s);
		for (int i = 0; i < n; ++i)
		{
			string s;
			getline(cin, s);
			stringstream ss(s);

			int j;
			vi floors;

			while (ss >> j)
			{
				floors.push_back(j);
			}

			for (int j = 0; j < floors.size(); ++j)
			{
				for (int l = 0; l < floors.size(); ++l)
				{
					int u = floors[j], v = floors[l];
					adjMatrix[u][v] = min(adjMatrix[u][v], abs(u-v) * timePerFloor[i] + 60);
				}
			}
		}

		for (int l = 0; l < MAXS; ++l)
			for (int i = 0; i < MAXS; ++i)
				for (int j = 0; j < MAXS; ++j)
					adjMatrix[i][j] = min(adjMatrix[i][j], adjMatrix[i][l]+adjMatrix[l][j]);

		if (adjMatrix[0][k] == INF)
			cout << "IMPOSSIBLE" << endl;
		else
			cout << (adjMatrix[0][k]-60) << endl;
	}
	return 0;
}
