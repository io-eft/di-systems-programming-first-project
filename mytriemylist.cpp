#include "mytrie.hpp"

MyTrie::Node::MyList::ListNode::ListNode(): content(NULL), next(NULL) {}

MyTrie::Node::MyList::ListNode::~ListNode()
{
    if(content != NULL)
        delete content;
}

MyTrie::Node::MyList::MyList(): head(NULL) {}

MyTrie::Node::MyList::~MyList()
{
    while(head != NULL)
    {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

MyTrie::Node* MyTrie::Node::MyList::goDown(char c, Node* n)
{
    ListNode* temp = head;  //set a pointer to the top of the list
    if(temp != NULL)    //if it's not empty
    {
        if(temp->content->character == c)   //if the inserted character is equal to the head, return it's content
            return temp->content;
        while(temp->next != NULL && c > temp->next->content->character)
        {   //else, go down the list while there's more items in the list, and the character is larger than the content of the next item in the list
            temp = temp->next;
        }   //once done
        if(c == temp->content->character)   //if the charactes equals the character contained in the node pointed by the iterator
            return temp->content;           //return said node
        if(temp->next == NULL)      //else, if there's no next node
        {
            ListNode* ln = new ListNode;    //create a new one
            temp->next = ln;    //set it as the next of the last one
            ln->content = new Node(c, n);   //create a new node containing that character
            return ln->content; //return said node
        }
        else    //if there are more items in the list
        {
            if(c == temp->next->content->character) //check if the next one contains the character we have
                return temp->next->content; //if so return it
            else    //else create a new one and insert it properly in the list
            {
                ListNode* ln = new ListNode;
                ln->next = temp->next;
                temp->next = ln;
                ln->content = new Node(c, n);
                return ln->content;
            }
        }
    }
    else    //if it's empty
    {
        temp = new ListNode();  //create a new listnode
        head = temp;    //set the head as the new one
        temp->content = new Node(c, n); //create a new node as the list's head node
        return temp->content;   //return the new node
    }
}
