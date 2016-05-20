#include "customlist.hpp"

CustomList::Node::Node(): content(""), next(NULL) {}

CustomList::Node::Node(std::string s): content(s), next(NULL){}

//CustomList::Node::Node(std::string s, int n): content(s), number(n), next(NULL){}

CustomList::Node::~Node() {}

CustomList::CustomList(): head(NULL), tail(NULL), items(0) {}

CustomList::~CustomList()
{   //list destructor, to free all the node memory
    Node* temp;
    while(head != NULL)
    {
        temp = head;
        head = head->next;
        delete temp;
    }
}

bool CustomList::isEmpty()
{
    if(head == NULL)
        return true;
    else
        return false;
}

void CustomList::insertEntry(std::string s)
{
    Node* n = new Node(s);
    if(isEmpty())
    {
        head = n;
        tail = n;
    }
    else
    {
        tail->next = n;
        tail = n;
    }
    items++;
}
/*
void CustomList::insertEntry(std::string s, int i)
{
    Node* n = new Node(s, i);
    if(isEmpty())
    {
        head = n;
        tail = n;
    }
    else
    {
        tail->next = n;
        tail = n;
    }
    items++;
}*/

void CustomList::print()
{
    Node* current = head;
    int i = 1;
    while(current != NULL)
    {
        std::cerr << current->content << " (" << i % 10 << ")  ";
        i++;
       // std::cerr << current->content;
        current=current->next;
    }
    std::cout << std::endl;
}

std::string CustomList::getTop()
{
    return head->content;
}

void CustomList::removeTopEntry()
{
    Node* temp = head;
    head = head->next;
    items--;
    delete temp;
}

int CustomList::length()
{
    return items;
}

bool CustomList::exists(std::string name)
{
    Node* temp = head;
    while(temp != NULL)
    {
        if(temp->content == name)
            return true;
        temp = temp->next;
    }
    return false;
}

std::string CustomList::itemAt(int i)
{
    if(i <= items)
    {
        Node* n = head;
        for(int j = 0; j < i; j++)
            n = n->next;
        return n->content;
    }
    else
    {
        std::string s = "empty string";
        return s;
    }
}
/*
int CustomList::numberAt(int i)
{
    if(i <= items)
    {
        Node* n = head;
        for(int j = 0; j < i; j++)
            n = n->next;
        return n->number;
    }
    else
    {
        return -1;
    }
}*/

CustomList::Node* CustomList::popTopNode()
{
    if(head != NULL)
    {
        Node* temp = head;
        head = head->next;
        temp->next = NULL;
        return temp;
    }
    return NULL;
}

void CustomList::putInOrder()
{
    Node* newHead = popTopNode();   //put the top item of the list in a new head
    Node* iter = popTopNode();      //and remove it from the list
    while(iter != NULL) //while there are items in the list
    {
        if(iter->content < newHead->content)    //put them in order
        {
            iter->next = newHead;
            newHead = iter;
        }
        else
        {
            Node* temp = newHead;
            while(temp->next != NULL && iter->content > temp->next->content)
            {
                temp = temp->next;
            }
            iter->next = temp->next;
            temp->next = iter;
        }
        iter = popTopNode();
    }
    head = newHead; //set the new list head as the list head
}
