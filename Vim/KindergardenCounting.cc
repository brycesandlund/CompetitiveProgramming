#include <iostream>
#include <string>

using namespace std;

typedef long long ll;

int main()
{
    string line;
    while (getline(cin, line))
    {
        ll count = 0;
        bool on = false;
        for (size_t i = 0; i < line.size(); ++i)
        {
            if ((line[i] >= 'A' && line[i] <= 'Z') || (line[i] >= 'a' && line[i] <= 'z'))
            {
                on = true;
            }
            else if (on)
            {
                ++count;
                on = false;
            }
        }

        cout << count << endl;
    }
}
