#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"
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

    //Helping function
    void traverseAdd(Node* root,T value) {
        if(this->root == nullptr) {
            this->root = new Node(value);
            return;
        }
        if(root != nullptr) {
            if(root->value >= value) {
                if(root->pLeft == nullptr) {
                    root->pLeft = new Node(value);
                    return;
                }
                traverseAdd(root->pLeft, value);
            }
            else {
                if(root->pRight == nullptr) {
                    root->pRight = new Node(value);
                    return;
                }
                traverseAdd(root->pRight, value);
            }
        }
    }

    void add(T value){
        //TODO   
        traverseAdd(this->root, value);
    }
    
    Node* minRightSubtree(Node* subNode) {
        Node* subNodeOrigin = subNode;
        while(subNode->pLeft != nullptr) {
            subNode = subNode->pLeft;
        }
        return subNode;
    }
    Node* traverseToFind(Node* root, T value) {
        if(root == nullptr) return root;
        if(root != nullptr) {
            if(value < root->value)
                root->pLeft = traverseToFind(root->pLeft, value);
            if(value > root->value)
                root->pRight = traverseToFind(root->pRight, value);
            if(value == root->value) {
                if (root->pLeft == nullptr and root->pRight == nullptr)
                    return nullptr;
                if(root->pRight == nullptr) {
                    root = root->pLeft;
                    return root;
                }
                if(root->pLeft == nullptr) {
                    root = root->pRight;
                    return root;
                }
                if(root->pLeft != nullptr && root->pRight != nullptr) {
                    Node* smallestRightSub = minRightSubtree(root->pRight);

                    root->value = smallestRightSub->value;

                    root->pRight = traverseToFind(root->pRight, smallestRightSub->value);
                }
            }
        }
        return root;
    }
    void deleteNode(T value){
        //TODO
        this->root = traverseToFind(this->root, value);
    }
    string inOrderRec(Node* root) {
        stringstream ss;
        if (root != nullptr) {
            ss << inOrderRec(root->pLeft);
            ss << root->value << " ";
            ss << inOrderRec(root->pRight);
        }
        return ss.str();
    }
    
    string inOrder(){
        return inOrderRec(this->root);
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
};

int main() {
    BinarySearchTree<int> bst;
    bst.add(9);
    bst.add(2);
    bst.add(10);
    bst.add(8);
    cout << bst.inOrder()<<endl;
    bst.add(11);
    bst.deleteNode(9);
    cout << bst.inOrder();
    return 0;
}