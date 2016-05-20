#include "myfunctions.hpp"

int getchar_silent()
{   //function given to us
    int ch;
    struct termios oldt, newt;

    /* Retrieve old terminal settings */
    tcgetattr(STDIN_FILENO, &oldt);

    /* Disable canonical input mode, and input character echoing. */
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );

    /* Set new terminal settings */
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    /* Read next character, and then switch to old terminal settings. */
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}

std::string getLastSubstring(std::string s)
{
    int i;
    for(i = s.length(); i > 0; i--) //find the last white space in a string
        if(s[i-1] == ' ')
            break;
    return s.substr(i); //return the substring that comes after
}

bool isLastAlpha(std::string s) //check if the string only contains letters
{
    if((s[s.length() - 1] >= 'a' && s[s.length() - 1] <= 'z') || (s[s.length() - 1] >= 'A' && s[s.length() - 1] <= 'Z'))
        return true;
    else
        return false;
}

bool isAllCaps(std::string s)
{
    if(s.length() == 0)
        return false;
    else
    {
        for(int i = 0; i < s.length(); i++)
        {
            if(s.at(i) >= 'a' && s.at(i) <= 'z')
                return false;
        }
        return true;
    }
}
