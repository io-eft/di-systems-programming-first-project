#include "mytrie.hpp"

MyTrie::Node::LeafList::LeafNode::LeafNode(Leaf* l): content(l), next(NULL) {}

MyTrie::Node::LeafList::LeafList(): head(NULL), items(0) {}

MyTrie::Node::LeafList::~LeafList()     //List destructor to free node memory
{
    while(head != NULL)
    {
        LeafNode* temp = head;
        head = head->next;
        delete temp;
    }
}

bool MyTrie::Node::LeafList::exists(Leaf* l)
{   //check if a leaf already exists in a list
    LeafNode* temp = head;
    while(temp != NULL)
    {
        if(temp->content == l)
            return true;
        temp = temp->next;
    }
    return false;
}

bool MyTrie::Node::LeafList::insertWord(Leaf* l)    //insert a word in a leaf list
{   //returns true if it actually inserted it, false otherwise
    if(exists(l))   //if the word is already on the list return true
        return true;
    else
    {   //if it doesn't exist
        if(items < MAXLIST) //if the list has less items than the maximum number allowed
        {
            LeafNode* n = new LeafNode(l);  //create a new node
            n->next = head; //and put it on the top
            head = n;
            items++;
            return true;    //return true since it was inserted
        }
        else    //if it already has the maximum amount of items
        {
            int lowest = getLowest();   //find the one with the lowest frequency
            if(l->getFrequency() >= lowest) //if the new one has larger or equal frequency
            {
                LeafNode* n = new LeafNode(l);  //create a new node
                n->next = head;         //and insert it on top
                head = n;
                LeafNode* removed = removeLowest(lowest);   //then remove the lowest alphabetically
                if(removed != n)    //if the removed one is not the new one
                {
                    delete removed; //delete the node to free the memory
                    return true;    //return true since the new one was inserted
                }
                else    //if it was the new one
                {
                    delete removed; //delete it
                    return false;   //and return false because it was not inserted
                }
            }
        }
        return false;       //if you reach to this point, it means the frequency was not high enough, so return false
    }
}

int MyTrie::Node::LeafList::getLowest()
{
    if(head != NULL)    //if the list has items
    {   //get the frequency of the head
        int lowest = head->content->getFrequency();
        LeafNode* temp = head;  //set an iterator
        while(temp != NULL)
        {   //go through the list to find the one with the lowest frequency
            if(temp->content->getFrequency() < lowest)
                lowest = temp->content->getFrequency();
            temp = temp->next;
        }
        return lowest;  //return said frequency
    }
    return 0;   //return 0 in case there's no item in the list (should never reach here anyway)
}

MyTrie::Node::LeafList::LeafNode* MyTrie::Node::LeafList::removeLowest(int n)
{   //removed the alphabetically last word that has frequency n from the list
    LeafNode* candidate;
    std::string candidateWord = "";
    std::string tempWord;
    LeafNode* temp = head;
    while(temp != NULL) //while there are still words in the list
    {
        if(temp->content->getFrequency() == n)  //if the temp has
        {
            tempWord = temp->content->getWord();    //get that word
            if(tempWord > candidateWord)        //check it's order
            {
                candidateWord = tempWord;       //if it's "bigger" than the candidate
                candidate = temp;               //make it the new candidate
            }
        }
        temp = temp->next;                      //check the next word
    }
    return removeLowest(candidate);             //call the function to remove it and return the result
}

MyTrie::Node::LeafList::LeafNode* MyTrie::Node::LeafList::removeLowest(LeafNode* ln)
{   //remove the lowest node from the list
    LeafNode* temp = head;  //set the iterator
    if(head == ln)  //if the head is the one to be removed
    {
        head = head->next;  //set the 2nd one as the new head
        return temp;        //and return it
    }
    else    //if it's not the head
    {
        while(temp->next != NULL)   //while it has a next one
        {
            if(temp->next == ln)    //check if the next one is the one we are looking for
            {
                LeafNode* toBeRemoved = temp->next;     //if it is, put a "mark" on it
                temp->next = toBeRemoved->next;         //fix the order of the list
                return toBeRemoved;             //return the removed one
            }
            temp = temp->next;      //get the next element
        }
    }
}

CustomList* MyTrie::Node::LeafList::getWords()
{
    CustomList* cl = new CustomList();  //create a new list of strings
    LeafNode* temp = head;
    //int i = 0;
    while(temp != NULL) //go through the list to get words
    {
        //cl->insertEntry(temp->content->getWord(), i);
        cl->insertEntry(temp->content->getWord());  //and insert them to the new tree
        //i++;
        temp = temp->next;
    }
    return cl;  //return the new list. Don't forget to clear the memory where you called this function.
}


