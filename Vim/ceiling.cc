#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<bool> vb;

struct tree {
    tree* left;
    tree* right;
    ll val;

    tree() {
        left = NULL;
        right = NULL;
        val = -1;
    }

    bool compare(tree* other) {
        if (left == NULL && right == NULL && other->left == NULL && other->right == NULL)
            return true;
        
        bool result = true;
        if (left != NULL && other->left != NULL) {
            result = result && left->compare(other->left);
        }
        else if (left != NULL || other->left != NULL)
            result = false;

        if (right != NULL && other->right != NULL) {
            result = result && right->compare(other->right);
        }
        else if (right != NULL || other->right != NULL)    
            result = false;

        return result;
    }

    void add(ll num) {
        if (val == -1) {
            val = num;
        }
        else {
            if (num < val) {
                if (left == NULL)
                    left = new tree;

                left->add(num);
            }
            else {
                if (right == NULL)
                    right = new tree;

                right->add(num);
            }
        }
    }
};

int main() {
    ll n, k;
    cin >> n >> k;
    
    vector<tree*> trees(n);
    for (ll i = 0; i < n; ++i)
        trees[i] = new tree;

    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < k; ++j) {
            ll num;
            cin >> num;
            trees[i]->add(num);
        }
    }

    vb seen(n, false);
    ll types = 0;
    for (ll i = 0; i < n; ++i) {
        if (seen[i])
            continue;

        ++types;
        
        for (ll j = 0; j < n; ++j) {
            if (trees[i]->compare(trees[j])) {
                seen[j] = true;
            }
        }
    }

    cout << types << endl;
    
    return 0;
}
