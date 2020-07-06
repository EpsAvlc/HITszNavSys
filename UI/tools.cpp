#include "tools.h"
#include <iostream>

#define linux

#ifdef linux
void CMDTools::SetCursorPos(int x, int y)
{
    printf("\033[%d;%df", y, x);
}

void CMDTools::SetForegroundColor(const Color& c)
{
    printf("\033[1;%dm", c);
}

void CMDTools::SetBackgroundColor(const Color& c)
{
    printf("\033[1;%dm", c+10);
}
#endif