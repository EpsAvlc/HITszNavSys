/*
 * Created on Thu Jul 09 2020
 *
 * Copyright (c) 2020 HITSZ-NRSL
 * All rights reserved
 *
 * Author: EpsAvlc
 */

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
    template <typename T>
    struct Point_t
    {
        T x = -1;
        T y = -1;
        Point_t(){}
        Point_t(T _x, T _y) : x(_x), y(_y){}
    };
    typedef Point_t<float> PointF;
    typedef Point_t<int> PointI;
    void SetCursorPos(int x, int y);
    void SetCursorPos(PointI& pt); 
    void SetForegroundColor(const Color& c);
    void SetBackgroundColor(const Color& c);
    void ReverseColor();
    
}

#endif //PROJECT_TOOLS_H
