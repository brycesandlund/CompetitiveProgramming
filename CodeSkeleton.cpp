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
#include <cstdlib>
#include <sstream>
#include <list>
#include <map>
#include <fstream>
#include <string>
#include <time.h>
#include <queue>
#include <tuple>
//#include <unordered_set>
//#include <unordered_map>
//#include <ctgmath>

#define INF 1000000000000000000LL

using namespace std;

typedef pair<int, pair<int, int> > iii;

int main() {
	ofstream out;
	out.open("coins_game_out.txt");
	ifstream in("coins_game.txt");
	int T;
	in >> T;
	for (int caseNum = 1; caseNum <= T; ++caseNum)
	{
		out << "Case #" << caseNum << ": ";
	}
	out.close();
	return 0;
}
