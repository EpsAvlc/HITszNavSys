/*
 * Created on Wed Jul 15 2020
 *
 * Copyright (c) 2020 HITSZ-NRSL
 * All rights reserved
 *
 * Author: EpsAvlc
 */

#ifndef CAMPUS_GRAPH_DRAWER_H__
#define CAMPUS_GRAPH_DRAWER_H__

#include <iostream>
#include "UI/button.h"
#include "UI/polyline.h"
#include "UI/text.h"
#include "campus_graph.h"

class CampusGraphDrawer
{
public:
    CampusGraphDrawer(const CampusGraph& cg);
    void Spin();
private:
    enum SystemState
    {
        WELCOME,
        NAVIGATION,
        GUIDE,
        HELP,
    };
    void drawBackground();
    void drawNavigationOrGuide();
    void drawWelcome();
    void readKeyboardInput();

    std::thread kb_thread_; 
    char kb_input_;
    std::mutex kb_mutex_;
    bool state_changed_ = true, pressed_ = true;;
    CampusGraph cg_;
    SystemState state_ = WELCOME;

    std::vector<CUI::Button> vertex_buttons_;
    std::vector<CUI::Button> menu_buttons_;
    std::vector<CUI::Text> texts_;
    std::vector<CUI::Polyline> polylines_;
};

#endif
