#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template<class T>
class BinarySearchTree
{
public:
    class Node;

private:
    Node* root;

public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }

    class Node
    {
    private:
        T value;
        Node* pLeft, * pRight;
        friend class BinarySearchTree<T>;

    public:
        Node(T value) : value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
    Node* addRec(Node* root, T value);
    void add(T value) ;
    // STUDENT ANSWER BEGIN
    void traverseInfix(Node* root, T i, bool &check) {
        if(root != nullptr) {
            traverseInfix(root->pLeft, i, check);
            if(root->value == i) check = 1;
            traverseInfix(root->pRight, i, check);
        }
    }

    bool find(T i) {
        bool check = 0;
        traverseInfix(this->root, i, check);
        if(check == 0) {
            return 0;
        }
        else return 1;
    }
    void traverseInfix(Node* root, T l, T r, int &result) {
        if(root != nullptr) {
            traverseInfix(root->pLeft, l, r, result);
            if(root->value >= l && root->value <= r) {
                result += root->value;
            }
            traverseInfix(root->pRight, l, r, result);
        }
    }
    T sum(T l, T r) {
        int result = 0;
        traverseInfix(this->root, l, r, result);
        return result;
    }
    // STUDENT ANSWER END
};
int main() {
    BinarySearchTree<int> bst;
    for (int i = 0; i < 10; ++i) {
        bst.add(i);
    }
    cout << bst.find(7) << endl;
    cout << bst.sum(0, 4) << endl;
    return 0;
}