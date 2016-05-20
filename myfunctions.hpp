#ifndef __MYFUNCTIONS__HPP
#define __MYFUNCTIONS__HPP
#include <sys/ioctl.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <string>

#define LINESIZE 128
#define BACKSPACE 0x7f

int getchar_silent();

std::string getLastSubstring(std::string s);

bool isLastAlpha(std::string s);

bool isAllCaps(std::string s);
#endif
