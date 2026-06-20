#include <iostream>
using namespace std;

struct Node
{
    int dato;
    Node *next;
    Node* prev;
    Node* son;
    Node(int value) : dato(value), next(nullptr), prev(nullptr), son(nullptr) {}
};

void createList(Node* &head)
{

    // creación de nodos
    Node* n10 = new Node(10); Node* n20 = new Node(20); 
    Node* n30 = new Node(30); Node* n40 = new Node(40); 
    Node* n50 = new Node(50); Node* n60 = new Node(60); 
    Node* n70 = new Node(70); Node* n80 = new Node(80); 
    Node* n90 = new Node(90); Node* n100 = new Node(100); 
    // enlaces bidireccionales nivel 1
    n10->next = n20; n20->prev = n10;
    n20->next = n30; n30->prev = n20;
    n30->next = n40; n40->prev = n30;

    // enlace vertical nivel 1 -> nivel 2
    n20->son = n50;

    // enlaces bidireccionales nivel 2
    n50->next = n60; n60->prev = n50;

    // enlace vertical nivel 2 -> nivel 3
    n60->son = n70;

    // conexion vertical nivel 3 -> nivel 4
    n70->son = n80;

    // enlaces bidireccionales nivel 4
    n80->next = n90; n90->prev = n80;
    n90->next = n100; n100->prev = n90;

    head = n10;
}

Node* flattenDFS(Node* node)
{
    Node* curr = node;
    Node* last = node;

    while (curr != nullptr)
    {
        Node* next = curr->next;

        if (curr->son != nullptr)
        {
            Node* childLast = flattenDFS(curr->son);

            curr->next = curr->son;
            curr->son->prev = curr;
            curr->son = nullptr;

            if (next != nullptr)
            {
                childLast->next = next;
                next->prev = childLast;
            }

            last = childLast;
        }
        else
        {
            last = curr;
        }

        curr = next;
    }

    return last;
}

Node* flatten(Node* head)
{
    if (head == nullptr)
        return nullptr;

    flattenDFS(head);
    return head;
}

void printList(Node* head)
{
    Node* temp = head;

    while (temp != nullptr)
    {
        cout << temp->dato << " ";
        temp = temp->next;
    }

    cout << endl;
}

int main()
{
    Node* head = nullptr;
    createList(head);

    cout << "Antes de aplanar:" << endl;
    printList(head);

    head = flatten(head);

    cout << "Despues de aplanar:" << endl;
    printList(head);

    return 0;
}
