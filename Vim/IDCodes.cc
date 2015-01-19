#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

int main()
{
    for (ll caseNum = 1; true; ++caseNum)
    {
        string letters;
        cin >> letters;

        if (letters == "#")
            break;

        if (next_permutation(letters.begin(), letters.end()))
            cout << letters << endl;
        else
            cout << "No Successor" << endl;
    }
}
