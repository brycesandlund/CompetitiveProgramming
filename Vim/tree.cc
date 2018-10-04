#include <iostream>

using namespace std;

struct Node {
    Node* left = NULL;
    Node* right = NULL;
    int value;

    Node(int in_value) : value(in_value) {}

    void insert(int new_value) {
        if (new_value > value) {
            if (right == NULL) {
                right = new Node(new_value);
            }
            else {
                right->insert(new_value);
            }
        }
        else {
            if (left == NULL) {
                left = new Node(new_value);
            }
            else {
                left->insert(new_value);
            }
        }
    }

    ~Node() {
        delete left;
        delete right;
    }
};

class NodeC {
    private:
        NodeC* left_ = NULL;
        NodeC* right_ = NULL;
        int value;

    public:
        NodeC(int in_value) : value(in_value) {}

        void insert(int new_value) {
            if (new_value > value) {
                if (right_ == NULL) {
                    right_ = new NodeC(new_value);
                }
                else {
                    right_->insert(new_value);
                }
            }
            else {
                if (left_ == NULL) {
                    left_ = new NodeC(new_value);
                }
                else {
                    left_->insert(new_value);
                }
            }
        }

        ~NodeC() {
            delete left_;
            delete right_;
        }
};

int main() {
    Node* root = new Node(5);
    root->insert(3);
    root->insert(7);
    return 0;
}
