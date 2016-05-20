#ifndef __MYTRIE__HPP
#define __MYTRIE__HPP
#include <iostream>
#include <string>
#include <fstream>
#include "customlist.hpp"
#define MAXLIST 5

class MyTrie{
    struct Node{	//Nodes of the trie, containing the character they represent, a list of their children, high frequency list, a word they might form and a pointer to their parent.
	class MyList{	//A list of nodes, pointing to the child of each node
	    struct ListNode{	//Node for the list of Nodes
		Node* content;
		ListNode* next;

	        ListNode();
		~ListNode();
	    };//ListNode end

	    ListNode* head;

	    public:
		MyList();
		~MyList();

		Node* goDown(char c, Node* n);
		//bool insertWord(Node* n);
	};//MyList end

	class Leaf{	//"Leaf" containing the frequency of the word they represent
	    int frequency;
	    Node* parent;

	    public:
		Leaf(Node* n);

		void increaseFrequency();
		int getFrequency();
		Node* getParent();
		std::string getWord();

	};//Leaf end

	class LeafList{	//List of the words with the highest frequency
		struct LeafNode{
                    Leaf* content;
                    LeafNode* next;

		    //LeafNode();
		    LeafNode(Leaf* l);
            	};//LeafNode end
	    LeafNode* head;
	    int items;
				
	    public:
		LeafList();
		~LeafList();

		bool exists(Leaf* l);
		bool insertWord(Leaf* l);
		int getLowest();
		LeafNode* removeLowest(int n);
		LeafNode* removeLowest(LeafNode* ln);
		CustomList* getWords();
	};//LeafList end
	    
	char character;
	LeafList* topWords;
	MyList* children;
	Node* parent;
	Leaf* word;

	Node();
	Node(char c);
	Node(char c, Node* n);
	~Node();
	CustomList* getTopWords();
    };//Node end

    class NamesList{	//list of new words added during execution
	struct Node{
	    std::string content;
	    Node* next;

	    Node(std::string s);
	    Node();
	    ~Node();
    };
    Node* head;
    Node* tail;

    public:
	NamesList();
	~NamesList();
	bool isEmpty();
	void insertEntry(std::string s);
	std::string getTop();
	void removeTopEntry();
    };//NamesList end

    Node* root;
    Node* current;
    bool isWord;
    bool isValidWord;
    NamesList* newWords;
    const char* dictionary;

    public:
	MyTrie(const char* c);
	~MyTrie();
	std::string getWord(Node* n);
	std::string getWord(Node::Leaf* l);
	void resetCurrent();
	void goDown(char c);
	int getHeight();
	void confirmWord();
	void confirmWordInLoad();
	void printTopWords();
	void loadDictionary();
	void printNewWords();
	void userInput();
	bool inputCharacter(char next, std::string* line);
	void goUp();
	void checkWordValidity(std::string s);
	void completeWord(std::string s, std::string lastSubString, std::string* line);
};//MyTrie end

#endif
