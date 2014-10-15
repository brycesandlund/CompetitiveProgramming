#include <iostream>
#include <vector>
#include <cstdio>
#include <sstream>
#include <string>

using namespace std;

typedef vector<int> vi;
typedef vector<char> vc;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;

int K;
vvvi MEMO;

void match(char a, char b, bool &matchAU, bool& matchCG)
{
	matchAU = a == 'A' && b == 'U' || a == 'U' && b == 'A';
	matchCG = a == 'C' && b == 'G' || a == 'G' && b == 'C';
}

int solve(int start, int end, int k, vc &letters)
{
	if (start >= end)
		return 0;

	if (MEMO[start][end][k] != -1)
		return MEMO[start][end][k];

	bool matchAU, matchCG;
	match(letters[start], letters[end], matchAU, matchCG);

	int best = 0;
	if (matchAU)
	{
		best = 1 + solve(start+1, end-1, k, letters);
	}
	else if (matchCG)
	{
		best = min(k, 1) + solve(start+1, end-1, max(k-1, 0), letters);
	}
	else
	{
		for (int i = start; i < end; ++i)
		{
			for (int j = 0; j <= k; ++j)
			{
				best = max(best, solve(start, i, j, letters) + solve(i+1, end, k-j, letters));
			}
		}
	}

	return MEMO[start][end][k] = best;
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

		vc lettersMid;
		for (int i = 1; i < lettersRL.size()-1; ++i)
		{
			for (int j = 0; j < counts[i]; ++j)
			{
				lettersMid.push_back(lettersRL[i]);
			}
		}

		int intervalM = 0;
		vc letters(lettersMid);
		for (int j = 0; j < counts[0]; ++j)
		{
			letters.insert(letters.begin(), lettersRL[0]);
		}
		MEMO = vvvi(letters.size(), vvi(letters.size(), vi(K+1, -1)));
		intervalM = solve(0, letters.size()-1, K, letters);

		letters = vc(lettersMid);
		for (int j = 0; j < counts.back(); ++j)
		{
			letters.push_back(lettersRL.back());
		}
		MEMO = vvvi(letters.size(), vvi(letters.size(), vi(K+1, -1)));
		intervalM = max(intervalM, solve(0, letters.size()-1, K, letters));

		nMatches += intervalM;
		printf("Case %d: %d\n", caseNum, nMatches);
	}
}