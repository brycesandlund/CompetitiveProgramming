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
		int C, S, Q;
		cin >> C >> S >> Q;
		if (C == 0 && S == 0 && Q == 0)
			break;

		if (caseNum > 1)
			cout << endl;

		vvi decibal(C, vi(C, INF));
		for (int i = 0; i < S; ++i)
		{
			int c1, c2, d;
			cin >> c1 >> c2 >> d;
			decibal[c1-1][c2-1] = d;
			decibal[c2-1][c1-1] = d;
		}

		for (int i = 0; i < C; ++i)
			decibal[i][i] = 0;

		for (int k = 0; k < C; ++k)
			for (int i = 0; i < C; ++i)
				for (int j = 0; j < C; ++j)
					decibal[i][j] = min(decibal[i][j], max(decibal[i][k], decibal[k][j]));

		printf("Case #%d\n", caseNum++);
		for (int i = 0; i < Q; ++i)
		{
			int u, v;
			cin >> u >> v;
			if (decibal[u-1][v-1] == INF)
				cout << "no path" << endl;
			else
				cout << decibal[u-1][v-1] << endl;
		}
	}
	return 0;
}
