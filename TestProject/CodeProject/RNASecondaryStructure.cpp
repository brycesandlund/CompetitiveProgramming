#include <iostream>
#include <vector>
#include <cstdio>
#include <sstream>
#include <algorithm>
#include <string>

using namespace std;

typedef vector<int> vi;
typedef vector<char> vc;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;

vc letters;
int K;
vvvi MEMO;

void match(char a, char b, bool &matchAU, bool& matchCG)
{
	matchAU = a == 'A' && b == 'U' || a == 'U' && b == 'A';
	matchCG = a == 'C' && b == 'G' || a == 'G' && b == 'C';
}

vi solve(int start, int end)
{
	if (start >= end)
		return vi(1, 0);

	if (!MEMO[start][end].empty())
		return MEMO[start][end];

	bool matchAU, matchCG;
	match(letters[start], letters[end], matchAU, matchCG);

	vi best;
	if (matchAU)
	{
		best = solve(start+1, end-1);
		for (int i = 0; i < best.size(); ++i)
		{
			++best[i];
		}
	}
	else if (matchCG)
	{
		best = solve(start+1, end-1);
		if (best.size() <= K)
		{
			best.push_back(best.back()+1);
		}
	}
	else
	{
		for (int i = start; i < end; ++i)
		{
			vi left = solve(start, i);
			vi right = solve(i+1, end);

			vi curBest(min(K+1, (int)(left.size() + right.size() - 1)), -1);
			
			for (int j = 0; j < left.size(); ++j)
			{
				for (int k = 0; k < min(K-j+1, (int)right.size()); ++k)
				{
					curBest[j+k] = max(curBest[j+k], left[j]+right[k]);
				}
			}

			for (int j = 0; j < curBest.size(); ++j)
			{
				if (j == best.size())
				{
					best.push_back(curBest[j]);
				}
				else
				{
					best[j] = max(best[j], curBest[j]);
				}
			}
		}
	}

	return MEMO[start][end] = best;
}

int main()
{
	int T;
	cin >> T;
	for (int caseNum = 1; caseNum <= T; ++caseNum)
	{
		string s;
		cin >> s;

		vi counts;
		vc lettersRL;

		stringstream ss;
		for (int i = 0; i <= s.size(); ++i)
		{
			if (i == s.size() || s[i] <= 'Z' && s[i] >= 'A')
			{
				if (i != 0)
				{
					int count;
					ss >> count;
					counts.push_back(count);
					ss.clear();
				}

				if (i != s.size())
					lettersRL.push_back(s[i]);
			}
			else
			{
				ss << s[i];
			}
		}

		cin >> K;

		bool matchAU, matchCG;
		match(lettersRL.front(), lettersRL.back(), matchAU, matchCG);
		int nMatches = 0;

		if (matchAU)
		{
			int nMatch = min(counts[0], counts[counts.size()-1]);

			counts[0] -= nMatch;
			counts[counts.size()-1] -= nMatch;
			nMatches += nMatch;
		}
		else if (matchCG)
		{
			int nMatch = min(K, min(counts[0], counts[counts.size()-1]));

			counts[0] -= nMatch;
			counts[counts.size()-1] -= nMatch;
			nMatches += nMatch;
			K -= nMatch;
		}

		counts[0] = min(counts[0], 26);
		counts[counts.size()-1] = min(counts[counts.size()-1], 26);

		letters.clear();
		for (int i = 0; i < lettersRL.size(); ++i)
		{
			for (int j = 0; j < counts[i]; ++j)
			{
				letters.push_back(lettersRL[i]);
			}
		}

		MEMO = vvvi(letters.size(), vvi(letters.size()));
		vi sol = solve(0, letters.size()-1);
		nMatches += *max_element(sol.begin(), sol.end());
		printf("Case %d: %d\n", caseNum, nMatches);
	}
}