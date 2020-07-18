/*
 * Created on Thu Jul 09 2020
 *
 * Copyright (c) 2020 HITSZ-NRSL
 * All rights reserved
 *
 * Author: EpsAvlc
 */

#include "polyline.h"

#include <iostream>

using namespace CUI;
using namespace std;
void Polyline::Draw()
{
    if(active_)
        SetForegroundColor(RED);
    else
        SetForegroundColor(BLUE);
    SetBackgroundColor(WHITE);
    PointI horizon_start = start_.x < end_.x ? PointI(start_) : PointI(end_);
    PointI vertical_start;
    vertical_start.x = start_.x > end_.x ? start_.x + 1 : end_.x + 1;
    vertical_start.y = start_.y < end_.y ? start_.y : end_.y;
    for(int i = 0; i < abs(end_.x - start_.x) + 1; i++)
    {
        horizon_start.x ++;
        SetCursorPos(horizon_start);
        if(active_)
            cout << "━";
        else
            cout << "─";
    }
    SetCursorPos(vertical_start);
    for(int i = 0; i < abs(end_.y - start_.y); i++)
    {
        SetCursorPos(vertical_start);
        if(i == 0)
        {
            if(active_)
                cout << "┓";
            else
                cout << "┐";
        }
        else 
        {
            if(active_)
                cout << "┃";
            else
                cout << "│";
        }
        vertical_start.y ++ ;
    }
}