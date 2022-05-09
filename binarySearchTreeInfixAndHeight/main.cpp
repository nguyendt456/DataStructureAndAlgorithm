#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

template<class K, class V>
class BinaryTree
{
public:
    class Node;
private:
    Node* root;
public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }
    class Node
    {
    private:
        K key;
        V value;
        Node* pLeft, * pRight;
        friend class BinaryTree<K, V>;
    public:
        Node(K key, V value) : key(key), value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
    void addNode(string posFromRoot, K key, V value)
    {
        if (posFromRoot == "")
        {
            this->root = new Node(key, value);
            return;
        }
        Node* walker = this->root;
        int l = posFromRoot.length();
        for (int i = 0; i < l - 1; i++)
        {
            if (!walker)
                return;
            if (posFromRoot[i] == 'L')
                walker = walker->pLeft;
            if (posFromRoot[i] == 'R')
                walker = walker->pRight;
        }
        if (posFromRoot[l - 1] == 'L')
            walker->pLeft = new Node(key, value);
        if (posFromRoot[l - 1] == 'R')
            walker->pRight = new Node(key, value);
    }
    // STUDENT ANSWER BEGIN 

    int max(int a, int b) {
        return (a < b ? b : a);
    }
    int height(Node* root) {
        if(root == nullptr) return 0;

        return 1 + max(height(root->pLeft), height(root->pRight));
    }
    int getHeight() {
    // TODO: return height of the binary tree.
        int result = height(this->root);
        return result;
    }

    void traversePreOrder(Node* root, string& result) {
        if(root != nullptr) {
            result += to_string(root->value);
            result += " ";
            traversePreOrder(root->pLeft, result);
            traversePreOrder(root->pRight, result);
        }
    }
    string preOrder() {
        // TODO: return the sequence of values of nodes in pre-order.
        string result = "";
        traversePreOrder(this->root, result);
        result.pop_back();
        return result; 
    }

    void traverseInOrder(Node* root, string& result) {
        if(root != nullptr) {
            traverseInOrder(root->pLeft, result);
            result += to_string(root->value);
            result += " ";
            traverseInOrder(root->pRight, result);
        }
    }
    string inOrder() {
        // TODO: return the sequence of values of nodes in in-order.
        string result = "";
        traverseInOrder(this->root, result);
        result.pop_back();
        return result;
    }

    void traversePostOrder(Node* root, string& result) {
        if(root != nullptr) {
            traversePostOrder(root->pLeft, result);
            traversePostOrder(root->pRight, result);
            result += to_string(root->value);
            result += " ";
        }
    }
    string postOrder() {
        // TODO: return the sequence of values of nodes in post-order.
        string result = "";
        traversePostOrder(this->root, result);
        result.pop_back();
        return result;
    }
    // STUDENT ANSWER END
};

int main() {
    BinaryTree<int, int> binaryTree;
    binaryTree.addNode("", 2, 4); // Add to root
    binaryTree.addNode("L", 3, 6); // Add to root's left node
    binaryTree.addNode("R", 5, 9); // Add to root's right node

    cout << binaryTree.getHeight() << endl;
    cout << binaryTree.preOrder() << endl;
    cout << binaryTree.inOrder() << endl;
    cout << binaryTree.postOrder() << endl;
    return 0;
}