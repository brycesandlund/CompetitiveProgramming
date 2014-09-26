#include <vector>
#include <iostream>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

typedef struct node
{
	node *left;
	node *right;
	char letter;
} node;

void postOrder(node *cur, string &result)
{
	if (cur->left != NULL)
		postOrder(cur->left, result);

	if (cur->right != NULL)
		postOrder(cur->right, result);

	result += cur->letter;
}

int main()
{
	string PRE, IN;
	while (cin >> PRE >> IN)
	{
		int n = PRE.size();
		node root;
		root.letter = PRE[0];
		unordered_map<char, node*> Node;
		unordered_set<char> visitedIN;
		node* cur = &root;
		Node[PRE[0]] = &root;

		int i = 1, j = 0;
		while (j < n)
		{
			while (!Node.count(IN[j]))
			{
				if (!visitedIN.count(PRE[i-1]))
				{
					cur->left = new node();
					cur = cur->left;
				}
				else
				{
					cur->right = new node();
					cur = cur->right;
				}

				cur->letter = PRE[i];
				Node[PRE[i]] = cur;
				++i;
			}
			visitedIN.insert(IN[j]);
			cur = Node[IN[j]];
			++j;
		}

		string result;
		postOrder(&root, result);

		cout << result << endl;
	}
}