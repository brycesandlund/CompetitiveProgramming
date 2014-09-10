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

vvi adjList;
unordered_map<string, int> targs;

int add(string &s)
{
	if (targs.count(s))
		return targs[s];
	
	int si = targs.size();
	targs[s] = si;
	adjList.push_back(vi());
	return si;
}

void connect(int si, int ti)
{
	if (si == ti)
		return;

	for (int i = 0; i < adjList[si].size(); ++i)
	{
		if (adjList[si][i] == ti)
			return;
	}

	adjList[si].push_back(ti);
}

vi bfs(int s)
{
	queue<ii> q;
	q.push(ii(s, -1));
	
	vi dist(adjList.size(), INF);

	while (!q.empty())
	{
		int top = q.front().first;
		int hops = q.front().second;
		q.pop();
		if (dist[top] != INF)
			continue;

		dist[top] = hops;
		for (int i = 0; i < adjList[top].size(); ++i)
		{
			q.push(ii(adjList[top][i], hops+1));
		}
	}

	return dist;
}

int main() {
	int caseNum = 1;
	cout << "Case " << caseNum << ":" << endl;
	string line;
	while (getline(cin, line))
	{
		stringstream ss(line);
		
		string command;
		ss >> command;
		if (command == "add")
		{
			string s, t;
			ss >> s;

			int si = add(s);
			if (ss >> t)
			{
				int ti = add(t);

				connect(si, ti);
				connect(ti, si);
			}
		}
		else if (command == "connections")
		{
			string s;
			ss >> s;

			if (!targs.count(s))
			{
				cout << "target does not exist" << endl;
				continue;
			}
			
			int si = targs[s];
			if (adjList[si].empty())
			{
				cout << "no connections" << endl;
			}
			else
			{
				vi dist = bfs(si);

				vi away(adjList.size(), 0);
				int maxd = -1;
				for (int i = 0; i < dist.size(); ++i)
				{
					if (dist[i] == INF || dist[i] == -1)
						continue;

					++away[dist[i]];
					maxd = max(maxd, dist[i]);
				}

				for (int i = 0; i <= maxd; ++i)
				{
					cout << i << ": " << away[i] << endl;
				}
			}
		}
		else if (command == "associated")
		{
			string s, t;
			ss >> s >> t;

			if (!targs.count(s) || !targs.count(t))
			{
				cout << "target does not exist" << endl;
				continue;
			}

			if (s == t)
			{
				cout << "yes: 0" << endl;
				continue;
			}

			int si = targs[s], ti = targs[t];
			vi dist = bfs(si);

			if (dist[ti] == INF)
			{
				cout << "no" << endl;
			}
			else
			{
				cout << "yes: " << dist[ti] << endl;
			}
		}
		else
		{
			adjList.clear();
			targs.clear();
			cout << "----------" << endl;
			cout << "Case " << ++caseNum << ":" << endl;
		}
	}

	cout << "----------" << endl;
	return 0;
}
