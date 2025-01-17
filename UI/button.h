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
        void SetColor(Color bg_color = BLUE, Color fg_color = WHITE)
        {
            bg_color_ = bg_color;
            fg_color_ = fg_color;
        }
        void SetCurserOn(bool on)
        {
            curserOn_ = on;
        }
        void SetPressed(bool pressed)
        {
            pressed_ = pressed;
        }
        void SetPadding(int padding_w, int padding_h)
        {
            padding_h_ = padding_h;
            padding_w_ = padding_w;
        }
        PointI Pos(){return PointI(x_, y_);}
        bool Pressed() {return pressed_;}
    protected:
        std::string text_;
        bool curserOn_ = false;
        bool pressed_ = false;
        int padding_w_ = 2;
        int padding_h_ = 0;
        Color bg_color_ = BLUE;
        Color bg_color_curserOn = GREEN;
        Color fg_color_curserOn_ = YELLO;
        Color fg_color_ = WHITE;
        Color bg_color_pressed_ = RED;
        Color fg_color_pressed_ = YELLO;
    };
}

#endif