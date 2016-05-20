#ifndef __CUSTOMLIST__HPP
#define __CUSTOMLIST__HPP
#include <iostream>
#include <string>	

class CustomList{
    struct Node{
        std::string content;
	//int number;
        Node* next;

        Node(std::string s);
	//Node(std::string s, int n);
        Node();
	~Node();
    };
    Node* head;
    Node* tail;
    unsigned int items;

    public:
        CustomList();
        ~CustomList();
        bool isEmpty();
	bool exists(std::string name);
        int length();

        void insertEntry(std::string s);
	//void insertEntry(std::string s, int n);
        std::string getTop();
        void removeTopEntry();
	std::string itemAt(int i);
	//int numberAt(int i);

	Node* popTopNode();
	void putInOrder();

        void print();
};

#endif

