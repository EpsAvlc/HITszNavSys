/*
 * Created on Thu Jul 09 2020
 *
 * Copyright (c) 2020 HITSZ-NRSL
 * All rights reserved
 *
 * Author: EpsAvlc
 */

#ifndef POLYLINE_H__
#define POLYLINE_H__
#include "tools.h"
#include "control.h"

namespace CUI
{
    class Polyline : public Control
    {
    public:
        Polyline(const PointI& start, const PointI& end) 
            : start_(start), end_(end){}
        virtual void Draw() override;
        void SetActive(bool active) {active_ = active; }
    private:
        PointI start_;
        PointI end_;
        bool active_ = false;
    };
}
#endif // !POLYLINE_H__