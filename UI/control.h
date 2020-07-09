/*
 * Created on Mon Jul 06 2020
 *
 * Copyright (c) 2020 HITSZ-NRSL
 * All rights reserved
 *
 * Author: EpsAvlc
 */

#ifndef CONTROL_H__
#define CONTROL_H__
namespace CUI
{
    class Control
    {
    public:
        virtual void Draw() = 0;
    protected:
        float x_ = 0;
        float y_ = 0;
    };
}
#endif // !CONTROL_H__