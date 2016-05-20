#include "mytrie.hpp"

MyTrie::NamesList::Node::Node(): content(""), next(NULL) {}

MyTrie::NamesList::Node::Node(std::string s): content(s), next(NULL){}

MyTrie::NamesList::Node::~Node()
{

}

MyTrie::NamesList::NamesList():head(NULL), tail(NULL) {}

MyTrie::NamesList::~NamesList()
{
    Node* temp;
    while(head != NULL)
    {
        temp = head;
        head = head->next;
        delete temp;
    }
}

bool MyTrie::NamesList::isEmpty()
{
    if(head == NULL)
        return true;
    else
        return false;
}

void MyTrie::NamesList::insertEntry(std::string s)
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
}

std::string MyTrie::NamesList::getTop()
{
    return head->content;
}

void MyTrie::NamesList::removeTopEntry()
{
    Node* temp = head;
    head = head->next;
    delete temp;
}
