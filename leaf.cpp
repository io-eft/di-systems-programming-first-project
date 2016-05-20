#include "mytrie.hpp"

MyTrie::Node::Leaf::Leaf(Node* n): frequency(0), parent(n) {}

void MyTrie::Node::Leaf::increaseFrequency()
{
    frequency++;
}

int MyTrie::Node::Leaf::getFrequency()
{
    return frequency;
}

MyTrie::Node* MyTrie::Node::Leaf::getParent()
{
    return parent;
}

std::string MyTrie::Node::Leaf::getWord()
{
    std::string s;
    Node* temp = parent;    //set an iterator to the parent of the leaf
    while(temp->parent != NULL) //while the node has a parent, meaning it's not the root
    {   //put the character of the node in the beginning for the string
        s = temp->character + s;
        temp = temp->parent;
    }
    return s;   //return the string
}
