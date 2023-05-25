#include <iostream>

struct Node 
{
    int data;
    Node* next;
};

class LinkedList 
{
private:
    Node* head;

public:
    LinkedList() 
    {
        head = nullptr;
    }

    void insert(int value) 
    {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = nullptr; 

        if (head == nullptr) 
        {
            head = newNode;
        } else 
        {
            Node* temp = head;
            while (temp->next != nullptr) 
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void display() 
    {
        Node* temp = head;
        while (temp != nullptr) 
        {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    void cleanup() 
    {
        Node* current = head;
        while (current != nullptr) 
        {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }
};

int main() 
{
    LinkedList myList;
    myList.insert(5);
    myList.insert(10);
    myList.insert(15);
    myList.display();

    myList.cleanup();

    return 0;
}
