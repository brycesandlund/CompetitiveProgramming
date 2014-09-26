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

int main() {
	int caseNum = 1;
	while (true)
	{
		vvi dist(20, vi(20, INF));

		for (int i = 0; i < 19; ++i)
		{
			int vn;
			if (cin >> vn)
			{
				for (int j = 0; j < vn; ++j)
				{
					int v;
					cin >> v;
					dist[i][v-1] = 1;
					dist[v-1][i] = 1;
				}
			}
			else
				goto END;
		}

		for (int k = 0; k < 20; ++k)
			for (int i = 0; i < 20; ++i)
				for (int j = 0; j < 20; ++j)
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

		printf("Test Set #%d\n", caseNum++);
		int N;
		cin >> N;
		for (int i = 0; i < N; ++i)
		{
			int u, v;
			cin >> u >> v;
			printf("%2d to %2d: %d\n", u, v, dist[u-1][v-1]);
		}
		cout << endl;
	}

	END:
	return 0;
}
