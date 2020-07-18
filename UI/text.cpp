/*
 * Created on Sun Jul 12 2020
 *
 * Copyright (c) 2020 HITSZ-NRSL
 * All rights reserved
 *
 * Author: EpsAvlc
 */

#include "text.h"

using namespace CUI;
using namespace std;

void Text::Draw()
{
    SetForegroundColor(fg_color_);
    SetBackgroundColor(bg_color_);
    SetCursorPos(pos_);
    int cur_y = pos_.y;
    int line_count = 0;
    for(int i = 0; i < text_.size(); i++)
    {
        cout << text_[i];
        line_count ++;
        if(text_[i] == '\n')
        {
            line_count = 0;
            SetCursorPos(pos_.x, ++cur_y);
            continue;
        }
        if((line_count) % width_ == 0)
        {
            cout << endl;
            cur_y ++;
            SetCursorPos(pos_.x, cur_y);
            line_count = 0;
        }
    }
    cout << endl;
}
    