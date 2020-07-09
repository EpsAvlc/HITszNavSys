/*
 * Created on Mon Jul 06 2020
 *
 * Copyright (c) 2020 HITSZ-NRSL
 * All rights reserved
 *
 * Author: EpsAvlc
 */

#ifndef BUTTON_H__
#define BUTTON_H__

#include <iostream>

#include "control.h"
#include "tools.h"

namespace CUI
{
    class Button : public Control
    {
    public:
        Button() {};
        Button(float x, float y, std::string text) 
            :text_(text)
            {
                x_ = x;
                y_ = y;
            }
        virtual void Draw() override;
        void SetCurserOn(bool on)
        {
            curserOn_ = on;
        }
        PointI Pos(){return PointI(x_, y_);}
    protected:
        std::string text_;
        bool curserOn_ = false;
        int height_ = 1;
        int width_ = 4;
        Color bg_color_ = BLUE;
        Color bg_color_curserOn = GREEN;
        Color fg_color_curserOn_ = YELLO;
        Color fg_color_ = WHITE;
    };
}

#endif