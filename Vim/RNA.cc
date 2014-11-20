#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdio>

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;

int getN(stringstream ss, int start, int &N)
{
    string s;
    ss >> s;
    N = 0;
    for (int i = start, power = 1; i < s.size(); ++i, power *= 10)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            N *= power;
            N += s[i];
        }
        else
            return i;
    }
    
    return s.size();
}

int main()
{
    int T;
    cin >> T;
    for (int caseNum = 1; caseNum <= T; ++caseNum)
    {
        string RNA;
        int K;
        cin >> RNA >> k;

        stringstream ss(RNA);
        char first, last;
        int firstN, lastN;

        ss >> first;
        int cur = getN(ss, 1, firstN);


        while (cur != s.size())
        {
            int N;
            cur = getN(ss, cur+1, N);
        }
    }
}
