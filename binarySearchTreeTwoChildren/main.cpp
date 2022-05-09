#include<iostream>
#include<string>
using namespace std;

template<class K, class V>
class BinaryTree
{
public:
    class Node;

private:
    Node *root;

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
        Node *pLeft, *pRight;
        friend class BinaryTree<K, V>;

    public:
        Node(K key, V value) : key(key), value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };

    void addNode(string posFromRoot, K key, V value)
    {
        if(posFromRoot == "")
        {
            this->root = new Node(key, value);
            return;
        }

        Node* walker = this->root;
        int l = posFromRoot.length();
        for (int i = 0; i < l-1; i++)
        {
            if (!walker)
                return;
            if (posFromRoot[i] == 'L')
                walker = walker->pLeft;
            if (posFromRoot[i] == 'R')
                walker = walker->pRight;
        }
        if(posFromRoot[l-1] == 'L')
            walker->pLeft = new Node(key, value);
        if(posFromRoot[l-1] == 'R')
            walker->pRight = new Node(key, value);
    }

    class queueNode {
    public:
        Node* value;
        queueNode* next;
        queueNode(Node* Value) {
            value = Value;
            next = nullptr;
        }
        ~queueNode() {}
    };
    class Queue {
    public:
        queueNode* head;
        queueNode* tail;
        Queue() {
            head = nullptr;
            tail = nullptr;
        }

        void push(Node* value) {
            if(head == nullptr) {
                head = new queueNode(value);
                tail = head;
            }
            else {
                queueNode* temporaryCursor = new queueNode(value);
                temporaryCursor->next = head;
                head = temporaryCursor;
            }
        }
        void pop() {
            queueNode* temporaryHead = head;
            if(head == tail) {
                head = nullptr;
                tail = nullptr;
                return;
            }
            while(temporaryHead->next != tail) {
                temporaryHead = temporaryHead->next;
            }
            temporaryHead->next = nullptr;
            tail = temporaryHead;
        }
        bool empty() {
            return head == nullptr ? 1 : 0;
        }
        Node* front() {
            return tail->value;
        }
    };

    // STUDENT ANSWER BEGIN
    int countTwoChildrenNode()
    {
        int result = 0;
        Queue traverseQueue = Queue();
        traverseQueue.push(this->root);
        while(!traverseQueue.empty()) {
            Node* target = traverseQueue.front();
            traverseQueue.pop();

            if(target->pLeft != nullptr) traverseQueue.push(target->pLeft);
            if(target->pRight != nullptr) traverseQueue.push(target->pRight);
            if(target->pLeft != nullptr && target->pRight != nullptr) {
                result++;
            }
        }
        return result;
    }
    // STUDENT ANSWER END
};
int main() {
    BinaryTree<int, int> binaryTree;
    binaryTree.addNode("",2, 4);
    binaryTree.addNode("L",3, 5);

    binaryTree.addNode("R",4, 6);
    binaryTree.addNode("RL",7, 14);
    binaryTree.addNode("LL",5, 10);
    binaryTree.addNode("LR",6, 11);
    binaryTree.addNode("RR",8, 19);
    cout << binaryTree.countTwoChildrenNode();
    return 0;
}