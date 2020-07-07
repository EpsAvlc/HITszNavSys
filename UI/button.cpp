/*
 * Created on Mon Jul 06 2020
 *
 * Copyright (c) 2020 HITSZ-NRSL
 * All rights reserved
 *
 * Author: EpsAvlc
 */

#include "button.h"

using namespace std;
namespace CUI
{
void Button::Draw()
{
    SetCursorPos(x_, y_);
    if(!curserOn_)
    {
        SetBackgroundColor(bg_color_);
        SetForegroundColor(fg_color_);
    }
    else
    {
        SetBackgroundColor(bg_color_curserOn);
        SetForegroundColor(fg_color_curserOn_);
    }
    
    for(int i = 0; i < (width_ - text_.length()) / 2; i++)
    {
        printf(" ");
    }
    cout << text_;
    for(int i = 0; i < (width_ - text_.length()) / 2; i++)
    {
        printf(" ");
    }
    printf("\n");
};
}