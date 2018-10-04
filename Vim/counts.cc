#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long ll;
typedef vector<ll> vi;

map<ll, ll> count_it(vi array) {
    map<ll, ll> counts;
    for (ll i = 0; i < array.size(); ++i) {
        if (!counts.count(array[i])) {
            counts[array[i]] = 0;
        }
        ++counts[array[i]];
    }
    return counts;
}

vi missingNumbers(vi arr, vi brr) {
    map<ll, ll> counts_A = count_it(arr);
    map<ll, ll> counts_B = count_it(brr);
   
    vi ans;
    for (auto it = counts_B.begin(); it != counts_B.end(); ++it) {
        if (!counts_A.count(it->first) || counts_A[it->first] < it->second) {
            ans.push_back(it->first);
        }
    }
    
    sort(ans.begin(), ans.end());
    return ans;
}

int main() {
    int n;
    cin >> n;
    vi arr(n);
    for(int arr_i = 0; arr_i < n; arr_i++){
       cin >> arr[arr_i];
    }
    int m;
    cin >> m;
    vi brr(m);
    for(int brr_i = 0; brr_i < m; brr_i++){
       cin >> brr[brr_i];
    }
    vi result = missingNumbers(arr, brr);
    for (ssize_t i = 0; i < result.size(); i++) {
        cout << result[i] << (i != result.size() - 1 ? " " : "");
    }
    cout << endl;
    
    return 0;
}
