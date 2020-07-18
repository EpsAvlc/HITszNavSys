/*
 * Created on Sun Jul 12 2020
 *
 * Copyright (c) 2020 HITSZ-NRSL
 * All rights reserved
 *
 * Author: EpsAvlc
 */

#ifndef TEXT_H__
#define TEXT_H__

#include "tools.h"
#include "control.h"

#include <iostream>
namespace CUI
{
class Text : public Control
{
public:
    Text(const PointI& pos, const std::string& text, int width = 15):
        pos_(pos), text_(text), width_(width){};
    virtual void Draw() override;
    void SetText(const std::string& str) {text_ = str;};
    void SetColor(Color fg_color, Color bg_color = DEEP_GREEN)
    {
        fg_color_ = fg_color;
        bg_color_ = bg_color;
    }
private:
    std::string text_;
    int width_;
    PointI pos_;
    Color fg_color_ = WHITE, bg_color_ = DEEP_GREEN;
};
}

#endif