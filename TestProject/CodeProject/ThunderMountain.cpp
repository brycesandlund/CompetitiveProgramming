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
#define EP .000000001

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
	int N;
	cin >> N;
	for (int caseNum = 1; caseNum <= N; ++caseNum)
	{
		int n;
		cin >> n;
		vvd dist(n, vd(n, INF));
		vii towns;
		for (int i = 0; i < n; ++i)
		{
			int x, y;
			cin >> x >> y;
			towns.push_back(ii(x, y));
		}

		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				double curd = hypot(towns[i].first - towns[j].first, towns[i].second - towns[j].second);
				if (curd < 10 + EP)
				{
					dist[i][j] = curd;
				}
			}
			dist[i][i] = 0;
		}

		for (int k = 0; k < n; ++k)
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j)
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

		double maxd = -1;
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				maxd = max(maxd, dist[i][j]);
			}
		}

		printf("Case #%d:\n", caseNum);
		if (maxd == INF)
		{
			cout << "Send Kurdy" << endl;
		}
		else
		{
			printf("%.4f\n", maxd);
		}
		cout << endl;
	}
	return 0;
}
