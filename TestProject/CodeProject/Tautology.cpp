//============================================================================
// Name        : Tautology.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
using namespace std;


pair<bool, int> eval(bool p, bool q, bool r, bool s, bool t, string str, int place)
{
	switch (str[place])
	{
		case 'N':
		{
			pair<bool, int> result = eval(p, q, r, s, t, str, place+1);
			return make_pair(!result.first, result.second);
		}
		case 'p':
			return make_pair(p, place);
		case 'q':
			return make_pair(q, place);
		case 'r':
			return make_pair(r, place);
		case 's':
			return make_pair(s, place);
		case 't':
			return make_pair(t, place);
		case 'K':
		{
			pair<bool, int> LHS = eval(p, q, r, s, t, str, place+1);
			pair<bool, int> RHS = eval(p, q, r, s, t, str, LHS.second+1);
			return make_pair(LHS.first && RHS.first, RHS.second);
		}
		case 'A':
		{
			pair<bool, int> LHS = eval(p, q, r, s, t, str, place+1);
			pair<bool, int> RHS = eval(p, q, r, s, t, str, LHS.second+1);
			return make_pair(LHS.first || RHS.first, RHS.second);
		}
		case 'C':
		{
			pair<bool, int> LHS = eval(p, q, r, s, t, str, place+1);
			pair<bool, int> RHS = eval(p, q, r, s, t, str, LHS.second+1);
			return make_pair(LHS.first && RHS.first || !LHS.first, RHS.second);
		}
		case 'E':
		{
			pair<bool, int> LHS = eval(p, q, r, s, t, str, place+1);
			pair<bool, int> RHS = eval(p, q, r, s, t, str, LHS.second+1);
			return make_pair(LHS.first && RHS.first || !LHS.first && !RHS.first, RHS.second);
		}
	}
}

int main() {
	while (true)
	{
		string str;
		cin >> str;
		if (str == "0")
			break;

		bool success = true;
		for (int MASK = 0; MASK < (1 << 5); ++MASK)
		{
			pair<bool, int> result = eval(MASK & 1, MASK & (1 << 1), MASK & (1 << 2), MASK & (1 << 3), MASK & (1 << 4), str, 0);
			success &= result.first;
		}

		cout << (success ? "tautology" : "not") << endl;
	}
	return 0;
}
