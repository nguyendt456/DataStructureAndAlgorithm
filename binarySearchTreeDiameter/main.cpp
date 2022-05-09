#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"
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
        int l = (int)posFromRoot.length();
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

    //Helping functions
    int max(int a, int b) {
        return (a < b ? b : a);
    }

    int height(Node* root) {
        if(root == nullptr) return 0;

        return 1 + max(height(root->pLeft), height(root->pRight));
    }
    int getDiameter(){
        //TODO
        if(this->root == nullptr) return 0;
        int rightSubTreeHeight = height(this->root->pRight);
        int leftSubTreeHeight = height(this->root->pLeft);

        return 1 + rightSubTreeHeight + leftSubTreeHeight;
    }
};

int main() {
    BinaryTree<int, int> binaryTree;
    binaryTree.addNode("",1, 4);
    cout << binaryTree.getDiameter();
}