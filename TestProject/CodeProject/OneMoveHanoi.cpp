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

int caseNum = 1;

LL nmoves(LL n)
{
	return (1LL << n) -1;
}

void move(LL n, char from, char spare, char to, LL moves)
{
	LL submoves = nmoves(n-1);
	if (moves-submoves <= 0)
	{
		move(n-1, from, to, spare, moves);
	}
	else if (moves-submoves == 1)
	{
		printf("Case %d: %lld %c %c\n", caseNum, n, from, to);
	}
	else
	{
		move(n-1, spare, from, to, moves-submoves-1);
	}
}

int main() {
	for (; ; ++caseNum)
	{
		LL k, n;
		cin >> k >> n;

		if (k == 0 && n == 0)
		{
			break;
		}

		move(n, 'A', 'B', 'C', k);
	}
	return 0;
}
