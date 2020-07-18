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
using namespace CUI;

void Button::Draw()
{
    SetCursorPos(x_, y_);
    if(curserOn_)
    {
        SetBackgroundColor(bg_color_curserOn);
        SetForegroundColor(fg_color_curserOn_);
    }
    else if(pressed_)
    {
        SetBackgroundColor(bg_color_pressed_);
        SetForegroundColor(fg_color_pressed_);
    }
    else
    {
        SetBackgroundColor(bg_color_);
        SetForegroundColor(fg_color_);
    }
    for(int i = 0; i < padding_h_; i++)
    {
        for(int j = 0; j < padding_w_ * 2 + text_.size(); j++)
        {
            printf(" ");
        }
        printf("\n");
    }
    SetCursorPos(x_, y_+padding_h_);
    for(int i = 0; i < padding_w_; i++)
    {
        printf(" ");
    }
    cout << text_;
    for(int i = 0; i < padding_w_; i++)
    {
        printf(" ");
    }
    printf("\n");
    SetCursorPos(x_, y_+padding_h_+1);
    for(int i = 0; i < padding_h_; i++)
    {
        for(int j = 0; j < padding_w_ * 2+ text_.size(); j++)
        {
            printf(" ");
        }
        printf("\n");
    }
};