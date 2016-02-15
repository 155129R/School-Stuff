#include "DetectMemoryLeak.h"
#include "Node.h"
#include "LinkedList.h"
#include "Stack.h"
#include "Queue.h"

// DO NOT MODIFY ANY LINE ABOVE OR ADD EXTRA INCLUDES

/*! 
 *  \brief     DM2126 Assignment 2
 *  \details   Submit the whole solution, but only this file will be used to grade
 *  \author    Sri Sham Haran S/O R Raja
 *  \date      2015 
 *  \note      155129R
 */

//*******************************************************************//
// Linked list stuff
//*******************************************************************//
LinkedList::LinkedList()
:head(nullptr)
{

}

LinkedList::~LinkedList()
{

}

void LinkedList::push_front(int data)
{
    Node* newNode = new Node(data);
    if (head == nullptr)
        head = newNode;
    else{
        newNode->next = head;
        head = newNode;
    }
    newNode->~Node();
}

void LinkedList::push_back(int data)
{
    Node* newNode = new Node(data);
    Node * curr = head;
    Node* prev = head;
    if (head == nullptr){
        head = newNode;
        head->next = nullptr;
    }
    else{
        while (curr != nullptr)
        {
            prev = curr;
            curr = curr->next;
        }
        curr = newNode;
    }
    if (prev)
    prev->next = curr;
    if (curr)
    curr->next = nullptr;



}

int LinkedList::pop_front()
{
    if (!head)
        return 0;
    int poppedVal = head->data;
    head = head->next;
    
    return poppedVal;
}

int LinkedList::pop_back()
{
    Node* curr = head;
    Node* prev = head;

    if (!head)
        return 0;

    else{

        int poppedVal;
        while (curr->next != nullptr)
        {

            prev = curr;
            curr = curr->next;
        }
        if (head->next == nullptr){
            poppedVal = head->data;
            head = nullptr;
        }
        else{
            poppedVal = curr->data;
            prev->next = nullptr;
            curr = nullptr;
        }
        
        return poppedVal;
        
    }

}

void LinkedList::insert_at(int pos, int data)
{
    Node* prev = new Node();
    Node* curr = new Node();
    Node* newNode = new Node(data);

   

    curr = head;
    if (head == nullptr){
        head = newNode;
        newNode->next = nullptr;

    }
    else{
        int tempPos = 0;
        while (curr->next != nullptr && tempPos != pos){
            prev = curr;
            curr = curr->next;
            tempPos++;
        }
        if (pos == 0 || pos < 0){
            push_front(data);
        }
        else if (curr->next == nullptr && pos == tempPos + 1){
            push_back(data);
        }
        else if (pos > tempPos + 1){
            push_back(data);
        }
        else{
            prev->next = newNode;
            newNode->next = curr;
        }
    }

}

int LinkedList::pop_at(int pos)
{
    Node* curr = head;
    Node* prev = head;
    if (pos <= 0)
    {
        return pop_front();
    }
    else if (int(size()) <= pos)
    {
        return 0;
    }
    int nodeVal = 0;
    while (nodeVal != pos)
    {
        prev = curr;
        curr = curr->next;
        nodeVal++;
    }
    nodeVal = curr->data;
    prev->next = curr->next;
    delete curr;
    return nodeVal;
}

size_t LinkedList::size()
{
    size_t count = 0;
    Node* curr = head;
    if (!head)
        return 0;
    while (curr != nullptr)
    {
        curr = curr->next;
        count++;
    }

    return count;

}

//*******************************************************************//
// Queue stuff
//*******************************************************************//
Queue::Queue()
:front(0), back(0)
{

}

Queue::~Queue()
{
    Node* curr = front;
    while (curr){
        Node* next = curr->next;
        delete curr;
        curr = curr->next;
    }
}

void Queue::enqueue(int data)
{
    Node* temp = new Node(data);

    if (front == nullptr){
        front = back = temp;
        back->next = 0;
    }
    else{
        back->next = temp;
        back = temp;
    }

}

int Queue::dequeue()
{
    int returnVal = 0;
    Node* temp = front;
    if (front == nullptr && back == nullptr)
    {
        return 0;
    }
    else if (front == back)
    {
        returnVal = front->data;
        front = nullptr;
        back = nullptr;
        delete temp;
    }
    else
    {
        returnVal = front->data;
        front = front->next;
        delete temp;
    }
    return returnVal;
}

size_t Queue::size()
{
    Node* tempNode = front;
    int count = 0;
    while (tempNode != nullptr){
        tempNode = tempNode->next;
        count++;
    }
    return count;
}

//*******************************************************************//
// Stack stuff
//*******************************************************************//
Stack::Stack()
:top(nullptr)
{

}

Stack::~Stack()
{

}

void Stack::push(int data)
{
    Node* tempTop = new Node(data);
    if (top == nullptr){
        tempTop->next = nullptr;
        top = tempTop;
    }
    else{
        tempTop->next = top;
        top = tempTop;
    }

}

int Stack::pop()
{
    if (top == nullptr)
    return 0;
    else{
        Node *temp = top;
        top = top->next;
        return temp->data;
    }
}

size_t Stack::size()
{
    if (top == nullptr)
    return 0;
    else{
        Node* temp = top;
        int count = 0;
        while (temp != nullptr){
            temp = temp->next;
            count++;
        }
        return count;
    }
}
