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
#include <map>

#include "UI/button.h"
#include "UI/polyline.h"

struct CampusVertex
{
    float x;
    float y;
    std::string name;
    std::string description;
    std::vector<CampusVertex*> neighbours;
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
    void QueryPath(CampusVertex& start, CampusVertex& end, int n);
private:
    void addVertices();
    void addEdges();

    std::vector<CampusVertex> vertices_;
    /* Map vertice from its name to itself*/
    std::map<std::string, CampusVertex> vertices_map_;
    std::map<std::string, int> vertices_index_map_;
    std::vector<std::pair<std::string, std::string>> edges_;
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
    std::vector<CUI::Polyline> polylines_;
};

#endif // !CAMPUS_GRAPH__