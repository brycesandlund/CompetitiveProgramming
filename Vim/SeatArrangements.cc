#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<char> > room(n, vector<char>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> room[i][j];
        }
    }

    vector<vector<int> > left_c(n, vector<int>(m, 0));
    vector<vector<int> > up_c(n, vector<int>(m, 0));
    int total = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (room[i][j] == '.') {
                if (i-1 >= 0) {
                    up_c[i][j] = up_c[i-1][j]+1;
                }
                else {
                    up_c[i][j] = 1;
                }

                if (j-1 >= 0) {
                    left_c[i][j] = left_c[i][j-1]+1;
                }
                else {
                    left_c[i][j] = 1;
                }

                if (up_c[i][j] >= k) {
                    ++total;
                }
                if (left_c[i][j] >= k && k != 1) {
                    ++total;
                }
            }
        }
    }

    cout << total << endl;
}
