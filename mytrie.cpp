#include "mytrie.hpp"

MyTrie::Node::Node(): character(' '), parent(NULL), word(NULL)
{
    topWords = new LeafList();
    children = new MyList();
}

MyTrie::Node::Node(char c): character(c), parent(NULL), word(NULL)
{
    topWords = new LeafList();
    children = new MyList();
}

MyTrie::Node::Node(char c, Node* n): character(c), parent(n), word(NULL)
{
    topWords = new LeafList();
    children = new MyList();
}

MyTrie::Node::~Node()
{
    delete topWords;
    delete children;
    if(word != NULL)
        delete word;
}

MyTrie::MyTrie(const char* c): dictionary(c)
{
    root = new Node();
    current = root;
    isWord = false;
    isValidWord = true;
    newWords = new NamesList;
}

MyTrie::~MyTrie()
{
    delete root;
    delete newWords;
}

std::string MyTrie::getWord(Node* n)
{
    std::string s = "";
    while(n != root)    //while not in the root
    {
        s = n->character + s;   //set the node character as the beginning of the string
        n = n->parent;
    }
    return s;   //return the string
}

std::string MyTrie::getWord(Node::Leaf* l)
{   //same as the above
    std::string s = "";
    Node* n = l->getParent();
    while(n != root)
    {
        s = n->character + s;
        n = n->parent;
    }
    return s;
}

void MyTrie::resetCurrent()
{
    current = root;
}

void MyTrie::goDown(char c)
{
    current = current->children->goDown(c, current);
}

void MyTrie::confirmWord()
{
    if(current != root) //make sure it's not the root
    {
        if(current->word == NULL)   //if this word is not in the dictionary already
        {
            current->word = new Node::Leaf(current);    //create a new leaf
            newWords->insertEntry(getWord(current->word));  //insert this word to the words meant to be added to the dictionary
        }
        current->word->increaseFrequency(); //increase the frequency
        Node* temp = current;   //set an iterator for the nodes
        while(temp != NULL && temp->topWords->insertWord(current->word))
        {   //while there is a parent, and the confirmed word belongs to the top word list, keep going up
            temp = temp->parent;
        }
        current = root; //set the current as the root
    }
}

void MyTrie::confirmWordInLoad()    //same as above, with 2 differences
{
    if(current != root)
    {
        if(current->word == NULL)
        {
            current->word = new Node::Leaf(current);    //words not added to the new words
        }//frequency remains 0
        Node* temp = current;
        while(temp != NULL && temp->topWords->insertWord(current->word))
        {
            temp = temp->parent;
        }
        current = root;
    }
}

CustomList* MyTrie::Node::getTopWords()
{
    return topWords->getWords();
}

void MyTrie::printTopWords()
{
    CustomList* cl = current->getTopWords();    //get current top words
    cl->putInOrder();   //put them in alphabetical order
    cl->print();    //print them
    delete cl;  //free the memory
}

void MyTrie::loadDictionary()
{   //load the given dictionary
   std::ifstream myDictionary;

   myDictionary.open(dictionary);   //open the dictionary
   if(myDictionary.is_open())   //if it is onep
   {
        std::cout << "Loading Dictionary";
        int k = 0;
        std::string line;
        while(getline(myDictionary, line))  //read it line by line
        {
            if(k % 72 == 0 || k % 72 == 12 || k % 72 == 24) //some poor attempt on to graphically show that loading is in progress
                std::cout << ".";
            if(k % 72 == 36 || k % 72 == 48 || k % 72 == 60)
                std::cout << "\b \b";
            k++;
            isValidWord = true; //set it to be a valid word
            for(int i = 0; i < line.length(); i++)  //read the line letter by letter
            {
                if(line[i] >= 'a' && line[i] <= 'z')    //if it's a lower case character
                {
                    goDown(line[i]);    //go down the tree with that character
                }
                else
                {
                    if(line[i] >= 'A' && line[i] <= 'Z')    //if it's a capital letter
                    {
                        char c = line[i] + 32;  //set it as lowercase
                        goDown(c);  //go down with that letter
                    }
                    else
                    {
                        isValidWord = false;    //if not, set the word to be not valid
                    }
                }
            }
            if(isValidWord) //once you finish reading the line
                confirmWordInLoad();    //confirm the word in load
            else    //if not
                resetCurrent(); //reset the current pointer
        }
        std::cout << std::endl;
    myDictionary.close();   //close the dictionary
    }
    else    //if you can't open it, let the user know
        std::cout << "Could not find the dictionary!" << std::endl;
}

int MyTrie::getHeight()
{   //get the current height of the node you are in
    Node* temp = current;   //set a pointer at the current node
    int i = 0;
    while(temp->parent != NULL) //while you're not on the root
    {
        i++;    //increase the counter
        temp = temp->parent;    //set the temp to point at the parent
    }
    return i;   //return the height
}

void MyTrie::printNewWords()
{   //print the new words to the dictionary
    std::ofstream words;
    words.open(dictionary, std::ofstream::app); //open the dictionary in append mode
    if(words.is_open())
    {
        while(!newWords->isEmpty()) //while there are words in the new word list
        {
            std::string s = newWords->getTop(); //get the top word
            //std::cout << s << std::endl;
            words << s << std::endl;    //put it in the file
            newWords->removeTopEntry(); //remove the top
        }
    }
    words.close();  //close the dictionary
}

void MyTrie::goUp() //if you're not in the parent, go up
{
    if(current != root)
        current = current->parent;
}
