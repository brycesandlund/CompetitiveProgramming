#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <functional>
#include <set>

#define INF 1000000000

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

class node
{
public:
	int V;
	int d;
	double s;

	bool operator>(const node &rhs) const
	{
		return s > rhs.s;
	}

	node(int V, int d, double s):V(V), d(d), s(s){}

	node(){}
};

int main()
{
	cout.precision(12);
	int N;
	cin >> N;
	for (int caseNum = 1; caseNum <= N; ++caseNum)
	{
		int n, m, e;
		cin >> n >> m >> e;
		vvi adjMatrix(n, vi(n, INF));
		vector<bool> exit(n, false);

		for (int i = 0; i < m; ++i)
		{
			int a, b, l;
			cin >> a >> b >> l;
			adjMatrix[a-1][b-1] = l;
			adjMatrix[b-1][a-1] = l;
		}

		for (int i = 0; i < e; ++i)
		{
			int exitNum;
			cin >> exitNum;
			exit[exitNum-1] = true;
		}

		int b, p;
		cin >> b >> p;
		--b, --p;

		vvi APSP = adjMatrix;
		for (int i = 0; i < n; ++i)
			APSP[i][i] = 0;

		for (int k = 0; k < n; ++k)
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j)
					APSP[i][j] = min(APSP[i][j], APSP[i][k] + APSP[k][j]);

		priority_queue<node, vector<node>, greater<node> > pq;
		pq.push(node(b, 0, 0));
		vector<double> speed(n, INF);
		speed[b] = 0;

		double minSpeed = INF;
		while (!pq.empty())
		{
			node front = pq.top();
			pq.pop();
			if (front.s > speed[front.V])
				continue;

			if (exit[front.V])
			{
				minSpeed = front.s;
				break;
			}

			for (int j = 0; j < n; ++j)
			{
				if (adjMatrix[front.V][j] != INF)
				{
					double minTime = APSP[p][j] / 1.6;
					if (minTime == 0)
						continue;
					
					node endpt;
					endpt.V = j;
					endpt.d = front.d + adjMatrix[front.V][j];
					double curTime = endpt.d / front.s;
					if (curTime < minTime)
					{
						endpt.s = front.s;
					}
					else
					{
						endpt.s = endpt.d / minTime;
					}

					if (endpt.s < speed[j])
					{
						speed[j] = endpt.s;
						pq.push(endpt);
					}
				}
			}
		}

		if (minSpeed == INF)
			cout << "IMPOSSIBLE" << endl;
		else
			printf("%.7f\n", minSpeed*100);
	}
}