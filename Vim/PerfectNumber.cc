#include <iostream>

using namespace std;

int SumOfDigits(int x) {
    int sum = 0;
    while (x) {
        sum += x % 10;
        x /= 10;
    }
    return sum;
}

int main() {
    int k;
    cin >> k;

    int num_perfect = 0;
    int cur_number = 0;
    while (num_perfect < k) {
        ++cur_number;
        if (SumOfDigits(cur_number) == 10) {
            ++num_perfect;
        }
    }
    
    cout << cur_number << endl;
}
