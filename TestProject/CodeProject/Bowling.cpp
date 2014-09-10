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
typedef long long LL;

int calcScore(vector<int> &newRolls)
{
	int score = 0;
	for (int m = 0; m < 20; ++m)
	{
		if (newRolls[m] == -1 || m == 19 && newRolls[m-1] == 10)
			continue;

		score += newRolls[m];

		if (m % 2 == 0)
		{
			if (newRolls[m] == 10)
			{
				for (int n = m+1, added = 0; added < 2; ++n)
				{
					if (newRolls[n] == -1)
						continue;
					score += newRolls[n];
					++added;
				}
			}
		}
		else
		{
			if (newRolls[m] + newRolls[m-1] == 10 && !(m == 19 && newRolls[m-1] == 10))
			{
				score += newRolls[m+1];
			}
		}
	}

	return score;
}

int main() {
	for (int caseNum = 1; true; ++caseNum)
	{
		int oppScore;
		cin >> oppScore;

		if (oppScore == -1)
			break;

		vi rolls, winningRolls;
		for (int i = 0; i < 16; ++i)
		{
			int roll;
			cin >> roll;
			rolls.push_back(roll);
			if (roll == 10 && i % 2 == 0)
			{
				rolls.push_back(-1);
				++i;
			}
		}

		bool success = false;
		for (int i = 0; i <= 10; ++i)
		{
			for (int j = 0; j <= 10-i; ++j)
			{
				for (int k = 0; k <= 10; ++k)
				{
					for (int l = 0; l <= (k == 10 ? 10 : 10-k); ++l)
					{
						vi newRolls(rolls);
						newRolls.push_back(i);
						if (i != 10)
							newRolls.push_back(j);
						else
							newRolls.push_back(-1);
						newRolls.push_back(k);
						newRolls.push_back(l);

						if (k + l == 10 || k == 10)
						{
							int maxm = 10;
							if (k == 10 && l != 10)
								maxm = 10-l;

							for (int m = 0; m <= maxm; ++m)
							{
								newRolls.push_back(m);

								int score = calcScore(newRolls);

								if (score > oppScore)
								{
									success = true;
									winningRolls = newRolls;
									goto END;
								}

								newRolls.pop_back();
							}

							continue;
						}

						int score = calcScore(newRolls);

						if (score > oppScore)
						{
							success = true;
							winningRolls = newRolls;
							goto END;
						}
					}
				}
			}
		}

END:
		cout << "Case " << caseNum << ":";

		if (success)
		{
			for (int i = 16; i < winningRolls.size(); ++i)
			{
				if (winningRolls[i] == -1)
					continue;
				cout << " " << winningRolls[i];
			}
		}
		else
		{
			cout << " impossible";
		}

		cout << endl;
	}
	return 0;
}
