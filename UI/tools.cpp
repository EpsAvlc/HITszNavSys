#include "tools.h"
#include <iostream>


void CUI::SetCursorPos(int x, int y)
{
    printf("\033[%d;%df", y, x);
}

void CUI::SetCursorPos(CUI::PointI& pt)
{
    printf("\033[%d;%df", pt.y, pt.x);
}
void CUI::SetForegroundColor(const Color& c)
{
    printf("\033[%dm", c);
}

void CUI::SetBackgroundColor(const Color& c)
{
    printf("\033[%dm", c+10);
}

void CUI::ReverseColor()
{
    std::cout << "\033[7m";
}