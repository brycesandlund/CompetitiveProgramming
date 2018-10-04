#include <iostream>

// assume this returns result of formula with given input
bool test_formula(bool x1, bool x2, bool x3, bool x4) {
    
}

bool backtrack(int var) {
    if (base case = true) {
        test_formula(...);
    }

    if (var % 2 == 0) {
        x_var = true;
        if (backtrack(var+1)) return true;
        x_var = false;
        if (backtrack(var+1)) return true;
    }
    else {
        x_var = true;
        bool first = backtrack(var+1);
        x_var = false;
        bool second = backtrack(var+1);
        return first && second;
    }
}

bool yes_instance() {
    return backtrack(0);
}

int main() {
}
