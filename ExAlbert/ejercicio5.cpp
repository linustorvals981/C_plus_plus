#include <iostream>
using namespace std;

struct Node
{
    float promedio;
    Node *next;
};

void merge(Node *&head1, Node *&head2)
{
    Node dummy;
    dummy.promedio = 0;
    dummy.next = NULL;

    Node *temp = &dummy;
    Node *temp1 = head1;
    Node *temp2 = head2;

    while (temp1 != NULL && temp2 != NULL)
    {
        if (temp1->promedio < temp2->promedio)
        {
            temp->next = temp1;
            temp1 = temp1->next;
        }
        else
        {
            temp->next = temp2;
            temp2 = temp2->next;
        }
        temp = temp->next;
    }

    while (temp1 != NULL)
    {
        temp->next = temp1;
        temp1 = temp1->next;
        temp = temp->next;
    }

    while (temp2 != NULL)
    {
        temp->next = temp2;
        temp2 = temp2->next;
        temp = temp->next;
    }

    head1 = dummy.next;
    head2 = NULL;

    if (head1 != NULL)
    {
        temp->next = head1;
    }
}

void printCircular(Node *head)
{
    if (head == NULL)
        return;

    Node *temp = head;

    do
    {
        cout << temp->promedio << " ";
        temp = temp->next;
    } while (temp != head);

    cout << endl;
}

int main()
{
    Node *head1 = new Node;
    head1->promedio = 1;
    head1->next = new Node;
    head1->next->promedio = 2;
    head1->next->next = new Node;
    head1->next->next->promedio = 3;
    head1->next->next->next = new Node;
    head1->next->next->next->promedio = 4;
    head1->next->next->next->next = new Node;
    head1->next->next->next->next->promedio = 5;
    head1->next->next->next->next->next = NULL;

    Node *head2 = new Node;
    head2->promedio = 6;
    head2->next = new Node;
    head2->next->promedio = 7;
    head2->next->next = new Node;
    head2->next->next->promedio = 8;
    head2->next->next->next = new Node;
    head2->next->next->next->promedio = 9;
    head2->next->next->next->next = new Node;
    head2->next->next->next->next->promedio = 10;
    head2->next->next->next->next->next = new Node;
    head2->next->next->next->next->next->promedio = 11;
    head2->next->next->next->next->next->next = new Node;
    head2->next->next->next->next->next->next->promedio = 12;
    head2->next->next->next->next->next->next->next = NULL;

    merge(head1, head2);

    printCircular(head1);

    return 0;
}
