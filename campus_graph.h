/*
 * Created on Mon Jul 06 2020
 *
 * Copyright (c) 2020 HITSZ-NRSL
 * All rights reserved
 *
 * Author: EpsAvlc
 */

#ifndef CAMPUS_GRAPH__
#define CAMPUS_GRAPH__

#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <mutex>

#include "UI/button.h"

struct CampusVertex
{
    float x;
    float y;
    std::string name;
    std::string description;
    CampusVertex(){};
    CampusVertex(std::string _name, float _x, float _y, std::string _description = "")
        : name(_name), x(_x), y(_y), description(_description) {};
};

class CampusGraphDrawer;

class CampusGraph
{
public:
    friend CampusGraphDrawer;
    CampusGraph();
private:
    void addVertices();

    std::vector<CampusVertex> vertices_;
};

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
        DETAIL
    };
    void drawNavigation();
    void readKeyboardInput();

    std::thread kb_thread_; 
    char kb_input_;
    std::mutex kb_mutex_;
    bool state_changed_ = true;
    CampusGraph cg_;
    SystemState state_ = NAVIGATION;

    std::vector<CUI::Button> buttons_;
};

#endif // !CAMPUS_GRAPH__