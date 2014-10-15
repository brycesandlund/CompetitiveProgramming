#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;


int main()
{
	vector<long long> tree(1430);
	tree[0] = 1;
	for (int i = 1; i < tree.size(); ++i)
	{
		if (i % 2 == 0)
		{
			tree[i] = (tree[i/2] * tree[i/2 - 1] * 2) % 1000000000;
		}
		else
		{
			tree[i] = (tree[(i-1)/2] * tree[(i-1)/2]) % 1000000000;
		}
	}

	int N;
	while (cin >> N)
	{
		printf("%9d\n", tree[N]);
	}
}