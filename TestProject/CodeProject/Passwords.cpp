#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<string> words;

void backtrack(string rule, int place, vector<string> &str)
{
	if (place == rule.size())
	{
		for (int i = 0; i < str.size(); ++i)
		{
			cout << str[i];
		}
		cout << endl;
	}
	else if (rule[place] == '0')
	{
		for (int i = 0; i < 10; ++i)
		{

			str.push_back(to_string(i));
			backtrack(rule, place+1, str);
			str.pop_back();
		}
	}
	else
	{
		for (int i = 0; i < words.size(); ++i)
		{
			str.push_back(words[i]);
			backtrack(rule, place+1, str);
			str.pop_back();
		}
	}
}

int main()
{
	int n;
	while (cin >> n)
	{
		words = vector<string>(n);
		for (int i = 0; i < n; ++i)
		{
			cin >> words[i];
		}

		int m;
		cin >> m;

		cout << "--" << endl;

		for (int i = 0; i < m; ++i)
		{
			string rule;
			cin >> rule;

			vector<string> str;
			backtrack(rule, 0, str);
		}
	}
}