#include <iostream>
#include <math.h>
#include <queue>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};

void printNSpace(int n)
{
    for (int i = 0; i < n - 1; i++)
        cout << " ";
}

void printInteger(int &n)
{
    cout << n << " ";
}

template<class T>
class AVLTree
{
public:
    class Node;
private:
    Node *root;
protected:
    int getHeightRec(Node *node)
    {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);
        return (lh > rh ? lh : rh) + 1;
    }
public:
    AVLTree() : root(nullptr) {}
    ~AVLTree(){}
    int getHeight()
    {
        return this->getHeightRec(this->root);
    }
    void printTreeStructure()
    {
        int height = this->getHeight();
        if (this->root == NULL)
        {
            cout << "NULL\n";
            return;
        }
        queue<Node *> q;
        q.push(root);
        Node *temp;
        int count = 0;
        int maxNode = 1;
        int level = 0;
        int space = pow(2, height);
        printNSpace(space / 2);
        while (!q.empty())
        {
            temp = q.front();
            q.pop();
            if (temp == NULL)
            {
                cout << " ";
                q.push(NULL);
                q.push(NULL);
            }
            else
            {
                cout << temp->data;
                q.push(temp->pLeft);
                q.push(temp->pRight);
            }
            printNSpace(space);
            count++;
            if (count == maxNode)
            {
                cout << endl;
                count = 0;
                maxNode *= 2;
                level++;
                space /= 2;
                printNSpace(space / 2);
            }
            if (level == height)
                return;
        }
    }

    Node* maxLeft(Node* current) {
        if(current->pRight == nullptr) return current;
        return maxLeft(current->pRight);
    }
    Node* remove(Node* current, const T &value) {
        if(current == nullptr) return current;

        if(value > current->data) {
            current->pRight = remove(current->pRight, value);
            current = reBalanceTree(current);
        }
        else {
            if(value < current->data) {
                current->pLeft = remove(current->pLeft, value);
                current = reBalanceTree(current);
            }
            else {
                if(current->pLeft == nullptr && current->pRight == nullptr) return nullptr;
                else {
                    if(current->pLeft == nullptr) {
                        Node* temporary = current->pRight;
                        return temporary;
                    }
                    if(current->pRight == nullptr) {
                        Node* temporary = current->pLeft;
                        return temporary;
                    }
                }
                Node* maxLeftNode = maxLeft(current->pLeft);

                current->data = maxLeftNode->data;

                current->pLeft = remove(current->pLeft, current->data);
                current = reBalanceTree(current);
            }
        }
        return current;
    }
    void remove(const T &value)
    {
        root = remove(root, value);
    }

    Node* recursiveInsert(Node* current, Node* nodeToAdd) {
        if(current == nullptr) {
            return nodeToAdd;
        }
        if(nodeToAdd->data >= current->data) {
            current->pRight = recursiveInsert(current->pRight, nodeToAdd);
        }
        else {
            current->pLeft = recursiveInsert(current->pLeft, nodeToAdd);     
        }

        return reBalanceTree(current);
    }
    Node* rightRotate(Node* current) {
        Node* leftSubtree = current->pLeft;
        current->pLeft = leftSubtree->pRight;
        leftSubtree->pRight = current;
        if(current == root) root = leftSubtree;
        return leftSubtree;
    }
    Node* leftRotate(Node* current) {
        Node* rightSubTree = current->pRight;
        current->pRight = rightSubTree->pLeft;
        rightSubTree->pLeft = current;
        if(current == root) root = rightSubTree;
        return rightSubTree;
    }

    Node* reBalanceTree(Node* current) {
        int balance = updatingBalance(current);
        if(balance == -1 || balance == 1 || balance == 0) {
            return current;
        }
        if(balance == -2) {
            if(updatingBalance(current->pLeft) > 0) {
                current->pLeft = leftRotate(current->pLeft);
                current = rightRotate(current);
            }
            else {
                current = rightRotate(current);
            }
        }
        if(balance == 2) {
            if(updatingBalance(current->pRight) < 0) {
                current->pRight = rightRotate(current->pRight);
                current = leftRotate(current);
            }
            else{
                current = leftRotate(current);
            }
        }
        return current;
    }
    int updatingBalance(Node* current) {
        int lh = 0;
        int rh = 0;
        if(current->pRight != nullptr) {
            rh = getHeightRec(current->pRight);
        }
        if(current->pLeft != nullptr) {
            lh = getHeightRec(current->pLeft);
        }
        return rh - lh;
    }

    void insert(const T &value) {
        if(root == nullptr) {
            Node* temp = new Node(value);
            root = temp;
        }
        else {
            Node* nodeToAdd = new Node(value);
            root = recursiveInsert(root, nodeToAdd);
        }
    }
    
    void inOrderTraverse(Node* current) {
        if(current == nullptr) return;
        inOrderTraverse(current->pLeft);
        cout << current->data << " ";
        inOrderTraverse(current->pRight);
    }
    void printInorder() {
        inOrderTraverse(root);
    }
    bool Search(Node* current, const T &value) {
        if(current == nullptr) return false;
        if(value > current->data) {
            return Search(current->pRight, value);
        }
        else {
            if(value == current->data) {
                return true;
            }
            return Search(current->pLeft, value);
        }
    }
    bool search(const T &value) {
        return Search(root, value);
    }
    void clear() {
        
    }
    class Node
    {
    private:
        T data;
        Node *pLeft, *pRight;
        int balance;
        friend class AVLTree<T>;

    public:
        Node(T value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
        ~Node() {}
    };
};

int main() {
   AVLTree<int> avl;
    int arr[] = {10,52,98,32,68,92,40,13,42,63,99,100};
    for (int i = 0; i < 12; i++){
        avl.insert(arr[i]);
    }
    avl.printTreeStructure();
    avl.printInorder();
    cout << avl.search(11);
    return 0;
}