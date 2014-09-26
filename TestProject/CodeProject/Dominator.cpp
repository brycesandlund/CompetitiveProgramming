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

vvi dom;
vvb adjMatrix;

vi findDom(int v)
{
	if (dom[v].size() != 0)
		return dom[v];

	vi curd;
	for (int i = 0; i < dom.size(); ++i)
	{
		curd.push_back(i);
	}

	dom[v] = curd;

	bool hasP = false;
	for (int i = 0; i < dom.size(); ++i)
	{
		if (adjMatrix[i][v])
		{
			hasP = true;
			vi parentD = findDom(i);
			vi::iterator iter = set_intersection(all(curd), all(parentD), curd.begin());
			curd.resize(iter-curd.begin());
		}
	}

	if (!hasP)
		curd.clear();

	curd.insert(lower_bound(all(curd), v), v);

	return dom[v] = curd;
}

void printBarrier(int n)
{
	cout << "+";

	for (int i = 0; i < n*2-1; ++i)
		cout << "-";

	cout << "+" << endl;
}

int main() {
	int T;
	cin >> T;
	for (int caseNum = 1; caseNum <= T; ++caseNum)
	{
		int N;
		cin >> N;
		dom = vvi(N);
		adjMatrix = vvb(N, vb(N, false));
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				int bit;
				cin >> bit;
				adjMatrix[i][j] = bit == 1;
			}

			adjMatrix[i][i] = false;
		}

		vvb domMatrix(N, vb(N, false));

		for (int i = 0; i < N; ++i)
		{
			vi curdom = findDom(i);
			
			for (int j = 0; j < N; ++j)
			{
				if (binary_search(all(curdom), j))
				{
					domMatrix[j][i] = true;
				}
			}
		}

		printf("Case %d:\n", caseNum);
		for (int i = 0; i < N; ++i)
		{
			printBarrier(N);
			for (int j = 0; j < N; ++j)
			{
				cout << "|" << (domMatrix[i][j] ? "Y" : "N");
			}
			cout << "|" << endl;
		}
		printBarrier(N);
	}
	return 0;
}
