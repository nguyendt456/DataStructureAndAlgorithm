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
    class node {
    public:
        int value;
        node* next;
        node(int Value) {
            value = Value;
            next = nullptr;
        }
    };
    class LinkedList {
    public:
        node* head;
        LinkedList() {
            head = nullptr;
        }
        ~LinkedList() {}

        void push(int value) {
            if(head == nullptr) {
                head = new node(value);
            }
            else {
                node* temporaryNode = head;
                while(temporaryNode->next != nullptr) {
                    temporaryNode = temporaryNode->next;
                }
                temporaryNode->next = new node(value);
            }
        }
        node gethead() {
            return head;
        }
    };

    void inFixTraverse(Node* root, LinkedList& data) {
        if(root != nullptr) {
            inFixTraverse(root->pLeft, data);
            data.push(root->value);
            inFixTraverse(root->pRight, data);
        }
    }
    bool increaseOrderCheck(LinkedList data) {
        node* virtualHead = data.head;
        while(virtualHead->next != nullptr) {
            if(virtualHead->value > virtualHead->next->value) {
                return 0;
            }
            virtualHead = virtualHead->next;
        }
        return 1;
    }
    bool isBST() {
        // TODO: return true if a tree is a BST; otherwise, return false.
        LinkedList data = LinkedList();
        inFixTraverse(this->root, data);
        return increaseOrderCheck(data);
    }
    // STUDENT ANSWER END
};

int main() {
    BinaryTree<int, int> binaryTree;
    binaryTree.addNode("", 2, 4); // Add to root
    binaryTree.addNode("L", 3, 2); // Add to root's left node
    binaryTree.addNode("R", 5, 5); // Add to root's right node
    binaryTree.addNode("RR", 4, 6);
    binaryTree.addNode("LL", 6, 1);
    binaryTree.addNode("LR", 5, 3);
    cout << binaryTree.isBST();
    return 0;
}