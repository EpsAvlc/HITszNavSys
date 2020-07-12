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
#include "UI/text.h"

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
    /**
     * @brief Query the best path from start to end via n spots.
     * 
     * @param start 
     * @param end 
     * @param n 
     */
    std::vector<std::string> QueryPath(CampusVertex& start, CampusVertex& end, int n);
    std::vector<std::string> QueryPath(const int start, const int end, int n)
    {
        return QueryPath(vertices_[start], vertices_[end], n);
    }
    std::vector<std::string> QueryPath(const std::string& start, const std::string& end, int n)
    {
        return QueryPath(*vertices_map_[start], *vertices_map_[end], n);
    }
private:
    void addVertices();
    void addEdges();
    std::string genResultDescription(std::vector<std::string>& res);
    void queryPathSub(CampusVertex& v, CampusVertex& end, int n, 
    std::map<std::string, int>& visited, std::vector<std::vector<std::string>>& res);

    std::vector<CampusVertex> vertices_;
    /* Map vertice from its name to itself*/
    std::map<std::string, CampusVertex*> vertices_map_;
    std::map<std::string, int> vertices_index_map_;
    std::vector<std::pair<std::string, std::string>> edges_;
    std::map<std::pair<std::string, std::string>, int> edges_map_;

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
        DETAIL,
        HELP,
    };
    void drawBackground();
    void drawNavigation();
    void drawWelcome();
    void readKeyboardInput();

    std::thread kb_thread_; 
    char kb_input_;
    std::mutex kb_mutex_;
    bool state_changed_ = true;
    CampusGraph cg_;
    SystemState state_ = NAVIGATION;

    std::vector<CUI::Button> vertex_buttons_;
    std::vector<CUI::Button> menu_buttons_;
    std::vector<CUI::Text> texts_;
    std::vector<CUI::Polyline> polylines_;
};

#endif // !CAMPUS_GRAPH__