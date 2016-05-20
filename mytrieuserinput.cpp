#include "mytrie.hpp"
#include "myfunctions.hpp"

void MyTrie::userInput()
{
    int next;
    std::string line;
    while ((next = getchar_silent()) != EOF)
    {   //get a char through the given function
        if(next != VEOF)
        {   //while the other function returns true, and char received is not ctrl+d, keep going
            if(!inputCharacter(next, &line))
               break;
        }
        else    //if ctlr + d is received
        {   //check and confirm word and exit
            if(isWord && isValidWord)
                confirmWord();
            break;
        }
    }
    printf("\n\nExiting. Bye...");
    putchar('\n');
    return;
}

bool MyTrie::inputCharacter(char next, std::string* line)
{   //it's book so the calling function knows when ctrl+D is pressed
    std::string lastSubString;
    if (next >= 'a' && next <= 'z') //if it's a lower case character
    {
        isWord = true;  //set it to be a word
        goDown(next);   //go down with the tree
        *line += next;  //add it to the string holding the line
        putchar(next);  //put it on the screen
        return true;    //and return true
    }
    if (next >= 'A' && next <= 'Z') //if it's a capital, do the same as above
    {
        isWord = true;
        goDown(next+32);    //only go down with the lower case version of it
        *line += next;
        putchar(next);
        return true;
    }

    switch(next) {  //if the character is not a letter

        case '\n':  //if it's new line or white space
        case ' ':
            if(next == ' ') //in case of white space, add it to the line
                *line += next;
            else    //in case of new line, empty the line string
                *line = "";
            if(isWord && isValidWord)   //if it's a word and a valid word, confirm it
                confirmWord();
            else    //else reset current
                resetCurrent();
            isWord = false; //set it to not be a word
            isValidWord = true; //but also set it to be a valid word
            putchar(next);  //put the character in the screen
            break;  //break so it returns true

            case '.':   //if it's a legal character ending a word, but not starting a new one
            case ',':
            case ';':
            case '*':
            case '/':
            case '?':
            case '!':
            case '-':
            case '\'':
            case ':':
                *line += next;  //put it to the line string
                if(isWord && isValidWord)   //if you are currently in a valid word
                    confirmWord();  //confirm it
                else
                    resetCurrent(); //else reset the trie
                isWord = false;     //set it to not currently be in a word
                isValidWord = false;    //set it to not currently be in a valid word
                putchar(next);  //put in on the screen
                break;  //and break out of the swich, so it returns true

            case '\t':  //if it's a tab
                std::cerr << std::endl; //put a new line in cerr
                if(!isValidWord)    //if it's not in a valid word
                {
                    std::cerr << "Not currently in a valid word" << std::endl;  //let the user know
                    std::cout << *line; //and put the last line in cout again
                }
                else    //if it's a valid word
                {
                    CustomList* ml = current->topWords->getWords(); //get the top words of the current node
                    std::string s;
                    lastSubString = getLastSubstring(*line);
                    switch(ml->length())    //get the length of the list
                    {
                        case 0: std::cerr << "No words currently in the list" << std::endl; std::cout << *line;break;   //if there are no words with that prefix currently, let the user know
                        case 1:
                            std::cerr << "Only one word currently on the list, completing it automatically." << std::endl;
                            s = ml->getTop();   //if there's only one
                            completeWord(s, lastSubString, line);
                            std::cout << *line;     //print the line
                            break;                  //break to return true
                        default:                //if it has more than one entry
                            ml->putInOrder();   //put the list in alphabetical order
                            ml->print();        //print the list
                            next = getchar_silent();    //get the users choice
                            if(next == VEOF)            //if the user enters control+D
                            {
                                if(isWord && isValidWord)   //if it's in a word and that word is valid
                                    confirmWord();  //confirm it
                                delete ml;  //free the list memory
                                return false;   //return false so the program can exit
                            }
                            if(next == '\t')    //if it's tab
                            {
                                //std::cerr << std::endl;
                                std::cout << *line; //put the line as it is
                                break;
                            }
                            else
                            {
                                if((next - '0') > 0 && (next - '0') <= MAXLIST)
                                {   //if it's a number from one to maxlist
                                    s = ml->itemAt(next - '0' - 1); //get the item (-1) from the list
                                    completeWord(s, lastSubString, line);
                                    std::cout << *line; //return the line
                                    break;  //and break so it returns true
                                }
                                else    //if it's not between 1 and maxlist
                                {   //if maxlist is 10 and number is 0
                                    if(MAXLIST == 10 && (next - '0') == 0)
                                    {
                                        s = ml->itemAt(9);  //get the last item on the list
                                        completeWord(s, lastSubString, line);
                                        std::cout << *line;
                                        break;
                                    }
                                    else    //in any other case
                                    {
                                        std::cout << *line; //return the line
                                        //if(next != BACKSPACE) //in case backspace is not used
                                        //{
                                            delete ml;  //free the memory of the list
                                            return inputCharacter(next, line);  //call this function recursivelly
                                        //}
                                    }
                                }

                            }
                    }
                    delete ml;  //free the memory of the list
                }
                break;  //break out of the switch

            case BACKSPACE: //if it's backspace
          //      if(isLastAlpha(*line))  //if the last character was a letter
            //        goUp(); //go up the tree
                *line = line->substr(0, line->length() - 1);    //remove the last letter from the line string

                lastSubString = getLastSubstring(*line);    //get the last substring of the line
                checkWordValidity(lastSubString);       //set validword and is word properly
                printf("\b \b");    //remove the character from the screen
                break;      //return

            default:    //if it's not any of the above
                *line+=next;    //add it to the string line
                isWord = false; //set word to be false
                isValidWord = false;    //same with the validword
                putchar(next);  //put in on the screen
                return true;    //and return true
            }
    return true;
}

void MyTrie::checkWordValidity(std::string s)
{   //check if the string contains a valid word, only used for backspace
    resetCurrent(); //go to the root of the tree
    isValidWord = true; //since it starts from white space, set it to be a valid word
    isWord = false; //and not a word, since it might actually not contain letters at all
    for(int i = 0; i < s.length(); i++)
    {
        if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
            isWord = true;  //if you come across a character, set the it to be a word
        else    //if you come across anything else, set it to be an invalid word
            isValidWord = false;
    }
    if(isWord && isValidWord)   //if the substring is a valid word
    {
        for(int i = 0; i < s.length(); i++) //for each letter if the string, go down the proper path
        {
            if(s.at(i) >= 'a' && s.at(i) <= 'z')
                goDown(s.at(i));
            if(s.at(i) >= 'A' && s.at(i) <= 'Z')
                goDown(s.at(i) + 32);
        }
    }
}

void MyTrie::completeWord(std::string s, std::string lastSubString, std::string* line)
{
    s = s.substr(getHeight());  //get the suffix of the word
    if(isAllCaps(lastSubString))
    {
        for(int i = 0; i < s.length(); i++) //for each letter in the suffix
        {
            goDown(s.at(i));    //go down the tree
            *line += (s.at(i) - 32);   //and add it to the line
        }
    }
    else
    {
        for(int i = 0; i < s.length(); i++) //for each letter in the suffix
        {
            goDown(s.at(i));    //go down the tree
            *line += s.at(i);   //and add it to the line
        }
    }
}
