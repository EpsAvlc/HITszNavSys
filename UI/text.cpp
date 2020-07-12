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
    SetForegroundColor(WHITE);
    SetBackgroundColor(DEEP_GREEN);
    SetCursorPos(pos_);
    int cur_y = pos_.y;
    for(int i = 0; i < text_.size(); i++)
    {
        cout << text_[i];
        if((i + 1) % width_ == 0)
        {
            cout << endl;
            cur_y ++;
            SetCursorPos(pos_.x, cur_y);
        }
    }
    cout << endl;
}
    