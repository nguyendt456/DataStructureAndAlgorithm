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
    T min(T a, T b) {
        return a > b ? b : a;
    }
    T max(T a, T b) {
        return a > b ? a : b;
    }
    void traverseInfixMin(Node* root, T &result) {
        if(root != nullptr) {
            traverseInfixMin(root->pLeft, result);
            result = min(result, root->value);
            traverseInfixMin(root->pRight, result);
        }
    }
    void traverseInfixMax(Node* root, T &result) {
        if(root != nullptr) {
            traverseInfixMax(root->pLeft, result);
            result = max(result, root->value);
            traverseInfixMax(root->pRight, result);
        }
    }
    T getMin() {
        //TODO: return the minimum values of nodes in the tree.
        int result = INT_MAX;
        traverseInfixMin(this->root, result);
        return result;
    }

    T getMax() {
        //TODO: return the maximum values of nodes in the tree.
        int result = 0;
        traverseInfixMax(this->root, result);
        return result;
    }
    // STUDENT ANSWER END
};