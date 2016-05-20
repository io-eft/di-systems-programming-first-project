#include "mytrie.hpp"
#include <string.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[])
{
    if(argc == 1)   //if there are no arguments
    {
        string str;
        str = getenv("HOME");
        str += "/.dict";
        MyTrie mt(str.c_str());
        mt.loadDictionary();        //load the default dictionary
        cout << "Finished loading the dictionary!" << endl; //let the user know
        mt.userInput();
        mt.printNewWords();     //put the new words in the file
    }
    else    //if there are arguments
    {
        if(argc != 3)   //let the user know if they are not right
            cout << "Please run the program with the correct input." << endl;
        else
        {
            if(strcmp(argv[1], "-d") != 0)
                cout << "Please run the program with the correct input." << endl;
            else    //if they are
            {
                MyTrie mt(argv[2]); //load the given dictonary
                mt.loadDictionary();
                cout << "Finished loading the dictionary!" << endl; //and let the user know
                mt.userInput();
                mt.printNewWords(); //print new words in the file
            }
        }
    }
}
