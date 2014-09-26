#include <vector>
#include <iostream>
#include <cmath>
#include <unordered_set>

using namespace std;

typedef pair<int, int> ii;

vector<vector<ii> > adjList;
vector<vector<int> > dist;
vector<bool> highway;
vector<double> memo;
int b, p;
int n, m, e;
double mespeed;

#define INF 1000000000
#define EP .000000000001

/*double maxt(int cur)
{
	if (maxdmemo[cur] == -2)
		return -1;

	if (maxdmemo[cur] != -3)
		return maxdmemo[cur];

	if (highway[cur])
		return (dist[p][cur] * 100) / 160.0;

	maxdmemo[cur] = -2;

	double minT = -1;
	for (int i = 0; i < adjList[cur].size(); ++i)
	{
		double childT = maxt(adjList[cur][i].first);
		if (childT == -1)
			continue;
		childT -= (adjList[cur][i].second * 100) / mespeed;
		minT = min(minT, childT);
	}

	minT = min(minT, 
}*/

double mint(int cur)
{
	if (cur == b)
		return 0;

	if (memo[cur] == -2)
		return -1;

	if (memo[cur] != -3)
		return memo[cur];

	memo[cur] = -2;

	double pT = dist[p][cur] * 100 / 160.0;

	double minTC = INF;
	for (int i = 0; i < adjList[cur].size(); ++i)
	{
		double childT = mint(adjList[cur][i].first);
		if (childT == -1)
			continue;
		childT += (adjList[cur][i].second * 100) / mespeed;
		minTC = min(minTC, childT);
	}

	if (minTC < pT + EP)
		return memo[cur] = minTC;
	else
		return memo[cur] = -1;
}

int main() {
	cout.precision(12);
	int N;
	cin >> N;
	for (int caseNum = 1; caseNum <= N; ++caseNum)
	{
		cin >> n >> m >> e;
		adjList = vector<vector<ii> >(n);

		for (int i = 0; i < m; ++i)
		{
			int a, b, l;
			cin >> a >> b >> l;
			adjList[a-1].push_back(ii(b-1, l));
			adjList[b-1].push_back(ii(a-1, l));
		}

		highway = vector<bool>(n, false);
		for (int i = 0; i < e; ++i)
		{
			int exit;
			cin >> exit;
			highway[exit-1] = true;
		}
		cin >> b >> p;
		--b, --p;

		dist = vector<vector<int> >(n, vector<int>(n, INF));
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < adjList[i].size(); ++j)
			{
				dist[i][adjList[i][j].first] = adjList[i][j].second;
			}
			dist[i][i] = 0;
		}

		for (int k = 0; k < n; ++k)
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j)
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

		double low = 0, high = INF;
		while (fabs(high - low) > .00000000000001)
		{
			mespeed = (high - low) / 2 + low;
			memo = vector<double>(n, -3);
			bool worked = false;
			for (int i = 0; i < n; ++i)
			{
				if (mint(i) != -1 && highway[i])
				{
					worked = true;
				}
			}

			if (worked)
				high = mespeed;
			else
				low = mespeed;
		}

		if (mespeed > INF - 1)
		{
			cout << "IMPOSSIBLE" << endl;
		}
		else
		{
			printf("%.10f\n", mespeed);
		}
	}
}