//
// Created by cm on 2020/7/5.
//

#ifndef PROJECT_TOOLS_H
#define PROJECT_TOOLS_H
namespace CUI
{
    enum Color
    {
        BLACK = 30,
        RED,
        GREEN,
        YELLO,
        BLUE,
        PURPLE,
        DEEP_GREEN,
        WHITE
    };
    void SetCursorPos(int x, int y);
    void SetForegroundColor(const Color& c);
    void SetBackgroundColor(const Color& c);
    void ReverseColor();
}

#endif //PROJECT_TOOLS_H
