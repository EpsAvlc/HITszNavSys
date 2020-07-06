//
// Created by cm on 2020/7/5.
//

#ifndef PROJECT_TOOLS_H
#define PROJECT_TOOLS_H
namespace CMDTools
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
}

#endif //PROJECT_TOOLS_H
