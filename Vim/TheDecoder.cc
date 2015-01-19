#include <iostream>
#include <string>

using namespace std;

typedef long long ll;

int main()
{
    string line;

    while (getline(cin, line))
    {
        for (size_t i = 0; i < line.size(); ++i)
        {
            cout << (char)(line[i] - 7);
        }

        cout << endl;
    }
}
