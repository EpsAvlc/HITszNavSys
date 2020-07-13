/*
 * Created on Mon Jul 06 2020
 *
 * Copyright (c) 2020 HITSZ-NRSL
 * All rights reserved
 *
 * Author: EpsAvlc
 */

#include "campus_graph.h"
#include <chrono>
#include <algorithm>
#include <stdio.h>                                 
#include <stdlib.h>
#include <fcntl.h>
#include <memory.h>
#include <unistd.h>
#include <termios.h>

using namespace std;

CampusGraph::CampusGraph()
{
    addVertices();
    addEdges();
}

void CampusGraph::addVertices()
{
    CampusVertex v;
    v.x = 108;
    v.y = 120;
    v.name = "E";
    v.description = "Buiding E, Civil Building, locate at (" + to_string((int)v.x) + 
        ", " + to_string((int)v.y) + ").";
    vertices_.push_back(v);

    v.x = 155;
    v.y = 120;
    v.name = "D";
    v.description = "Buiding D,  Materia building, locates at (" + to_string((int)v.x) + 
        ", " + to_string((int)v.y) + ").";
    vertices_.push_back(v);

    v.x = 197;
    v.y = 120;
    v.name = "F";
    v.description = "Buiding F, Academic building, locates at (" + to_string((int)v.x) + 
        ", " + to_string((int)v.y) + ").";
    vertices_.push_back(v);

    v.x = 226;
    v.y = 120;
    v.name = "C";
    v.description = "Buiding C, Mechantronic building, locates at (" + to_string((int)v.x) + 
        ", " + to_string((int)v.y) + ").";
    vertices_.push_back(v);

    v.x = 260;
    v.y = 163;
    v.name = "A";
    v.description = "Buiding A, Teaching buliding I, locates at (" + to_string((int)v.x) + 
        ", " + to_string((int)v.y) + ").";
    vertices_.push_back(v);

    v.x = 303;
    v.y = 149;
    v.name = "B";
    v.description = "Buiding B, Social Science building, locates at (" + to_string((int)v.x) + 
        ", " + to_string((int)v.y) + ").";
    vertices_.push_back(v);

    v.x = 345;
    v.y = 189;
    v.name = "G";
    v.description = "Buiding G, Sciences building, locates at (" + to_string((int)v.x) + 
        ", " + to_string((int)v.y) + ").";
    vertices_.push_back(v);

    v.x = 400;
    v.y = 228;
    v.name = "K";
    v.description = "Buiding K, Experiment building, locates at (" + to_string((int)v.x) + 
     ", " + to_string((int)v.y) + ").";
    vertices_.push_back(v);

    v.x = 400;
    v.y = 282;
    v.name = "J";
    v.description = "Building J, Recreation center, locates at (" + to_string((int)v.x) + 
     ", " + to_string((int)v.y) + ").";
    vertices_.push_back(v);

    v.x = 440;
    v.y = 303;
    v.name = "H";
    v.description = "Building H, Main building, locates at (" + to_string((int)v.x) + 
     ", " + to_string((int)v.y) + ").";
    vertices_.push_back(v);

    for(int i = 0; i < vertices_.size(); i++)
    {
        vertices_map_[vertices_[i].name] = &vertices_[i];
        vertices_index_map_[vertices_[i].name] = i;
    }
}

void CampusGraph::addEdges()
{
    edges_.push_back(make_pair("E", "D"));
    edges_.push_back(make_pair("D", "F"));
    edges_.push_back(make_pair("C", "F"));
    edges_.push_back(make_pair("C", "A"));
    edges_.push_back(make_pair("B", "A"));
    edges_.push_back(make_pair("B", "G"));
    edges_.push_back(make_pair("K", "G"));
    edges_.push_back(make_pair("K", "J"));
    edges_.push_back(make_pair("H", "J"));
    edges_.push_back(make_pair("H", "K"));

    for(int i = 0; i < edges_.size(); i++)
    {
        vertices_map_[edges_[i].first]->neighbours.push_back(vertices_map_[edges_[i].second]);
        vertices_map_[edges_[i].second]->neighbours.push_back(vertices_map_[edges_[i].first]);

        edges_map_[make_pair(edges_[i].first, edges_[i].second)] = i;
        edges_map_[make_pair(edges_[i].second, edges_[i].first)] = i;
    }
}

vector<string> CampusGraph::QueryPath(CampusVertex& start, CampusVertex& end, int n)
{
    map<string, int> visited;
    visited[start.name] = n;
    vector<vector<string>> visited_res;
    queryPathSub(start, end, n-1, visited, visited_res);
    
    if(visited_res.size() > 0)
    {
        return visited_res[0];
    }
    else
    {
        return vector<string>();
    }
}

void CampusGraph::queryPathSub(CampusVertex& v, CampusVertex& end, int n, 
    map<string, int>& visited, vector<vector<string>>& visited_res)
{
    if(n == 0)
    {
        if(v.name == end.name)
        {
            vector<string> visited_order;
            for(auto item:visited)
            {
                if(item.second != 0)
                    visited_order.push_back(item.first);
            }
            sort(visited_order.begin(), visited_order.end(), 
            [&visited](string& lhs, string& rhs)
            {
                return visited[lhs] > visited[rhs];
            }
            );
            visited_res.push_back(visited_order);
        }
        return;
    }
    for(int i = 0; i < v.neighbours.size(); i++)
    {
        if(visited[v.neighbours[i]->name] != 0)
            continue;
        visited[v.neighbours[i]->name] = n;
        queryPathSub(*v.neighbours[i], end, n-1, visited, visited_res);
        visited[v.neighbours[i]->name] = 0;
    }
}

string CampusGraph::genResultDescription(vector<string>& res)
{
    string description = "";
    if(res.size() != 0)
    {
        description += "Best way has been highlighted, and is ";
        for(int i = 0; i < res.size(); i++)
        {
            description += res[i];
            if(i != res.size() -1)
                description += "->";
        }
    }
    else
    {
        description += "No way to reach the destination";
    }
    
    description += ". \n Press Enter to return.";
    return description;
}

/*------------ CampusGraphDrawer --------------*/

CampusGraphDrawer::CampusGraphDrawer(const CampusGraph& cg): cg_{cg} 
{
    kb_thread_ = std::thread(std::bind(&CampusGraphDrawer::readKeyboardInput, this));
    kb_thread_.detach();

    const float origin_x = 98;
    const float origin_y = 20;
    const float kGridWidth = 5;
    const float kGridHeight = 30;

    /* Vertices button */
    for(int i = 0; i < cg_.vertices_.size(); i++)
    {
        float grid_x = (cg_.vertices_[i].x - origin_x) / kGridWidth;
        float grid_y = (cg_.vertices_[i].y - origin_y) / kGridHeight;
        CUI::Button b(grid_x, grid_y, cg_.vertices_[i].name);
        vertex_buttons_.push_back(b);
    }

    /* Menu buttons */
    CUI::Button nav_button(20, 5, "Navigation");
    nav_button.SetPadding(2, 1);
    CUI::Button detail_button(45, 5, "Guide");
    detail_button.SetPadding(2, 1);
    menu_buttons_.push_back(nav_button);
    menu_buttons_.push_back(detail_button);

    /* Texts */
    CUI::Text t1 (CUI::PointI(80, 2), "1. Please select starting point", 33);
    texts_.push_back(t1);
    for(int i = 0; i < 8; i++)
        texts_.push_back(CUI::Text(CUI::PointI(80, 2 + i), "", 33));
    texts_[7].SetText("--------------------------");

    /* Polylines */
    for(int i = 0; i < cg_.edges_.size(); i++)
    {
        CUI::PointI start, end;
        start.x = vertex_buttons_[cg_.vertices_index_map_[cg_.edges_[i].first]].Pos().x;
        start.y = vertex_buttons_[cg_.vertices_index_map_[cg_.edges_[i].first]].Pos().y;
        end.x = vertex_buttons_[cg_.vertices_index_map_[cg_.edges_[i].second]].Pos().x;
        end.y = vertex_buttons_[cg_.vertices_index_map_[cg_.edges_[i].second]].Pos().y;
        CUI::Polyline pl(start, end);
        polylines_.push_back(pl);
    }


};

void CampusGraphDrawer::Spin()
{
    system("clear");
    char c;
    while(1)
    {
        if(pressed_ || state_changed_)
        {
            if(state_ == WELCOME)
            {
                static int last_curserOn = 0;
                menu_buttons_[last_curserOn].SetCurserOn(false);
                switch (kb_input_)
                {
                case 'd':
                case 's':
                    if(last_curserOn < menu_buttons_.size() - 1)
                        last_curserOn ++;
                    break;
                case 'a':
                case 'w':
                    if(last_curserOn > 0)
                        last_curserOn --;
                    break;
                case 10:
                    if(last_curserOn == 0)
                    {
                        state_ = NAVIGATION;
                        state_changed_ = true;
                    }
                    else if (last_curserOn == 1)
                    {
                        // state_changed_ = true;
                        state_ = DETAIL;
                    }
                default:
                    break;
                }
                menu_buttons_[last_curserOn].SetCurserOn(true);
                drawWelcome();
            }
            else if(state_ == NAVIGATION)
            {
                static int last_curserOn = 0;
                static int pressed_count = 0;
                vertex_buttons_[last_curserOn].SetCurserOn(false);
                static string n_str = "";
                static int from_vertex = -1, to_vertex = -1; 
                if(kb_input_ <= '9' && kb_input_ >= '0')
                {
                    if(pressed_count == 2)
                    {
                        n_str += kb_input_;
                        texts_[6].SetText(n_str);
                    }

                }
                if(pressed_ == true)
                {
                switch (kb_input_)
                {
                case 'd':
                case 's':
                    if(last_curserOn < cg_.vertices_.size() - 1)
                        last_curserOn ++;
                    break;
                case 'a':
                case 'w':
                    if(last_curserOn > 0)
                        last_curserOn --;
                    break;
                case 10:
                    if(pressed_count == 0)
                    {
                        texts_[2].SetText(cg_.vertices_[last_curserOn].name);
                        vertex_buttons_[last_curserOn].SetPressed(true);
                        texts_[3].SetText("2. Please select destination.");
                        from_vertex = last_curserOn;
                    }
                    if(pressed_count == 1)
                    {
                        texts_[4].SetText(cg_.vertices_[last_curserOn].name);
                        vertex_buttons_[last_curserOn].SetPressed(true);
                        texts_[5].SetText("Please input n.");
                        to_vertex = last_curserOn;
                    }
                    if(pressed_count == 2)
                    {
                        int via_n = atoi(n_str.c_str());
                        vector<string> res = cg_.QueryPath(from_vertex, to_vertex, via_n);
                        for(int i = 0; i < (int)res.size() - 1; i++)
                        {
                            polylines_[cg_.edges_map_[make_pair(res[i], res[i+1])]].SetActive(true);
                        }
                        for(int i = 0; i < texts_.size(); i++)
                        {
                            texts_[i].SetText("");
                        }
                        string res_description = cg_.genResultDescription(res);
                        texts_[0].SetText(res_description);
                    }
                    if(pressed_count == 3)
                    {
                        pressed_count = -1;
                        for(int i = 0; i < vertex_buttons_.size(); i++)
                        {
                            vertex_buttons_[i].SetPressed(false);
                        }
                        for(int i = 0; i < polylines_.size(); i++)
                        {
                            polylines_[i].SetActive(false);
                        }
                        for(int i = 0; i < texts_.size(); i++)
                        {
                            texts_[i].SetText("");
                        }
                        n_str = "";
                        texts_[0].SetText("1. Please select starting point.");
                        
                    }
                    pressed_count ++;
                    break;
                default:
                    break;
                }
                vertex_buttons_[last_curserOn].SetCurserOn(true);
                if(pressed_count != 3)
                    texts_[8].SetText(cg_.vertices_[last_curserOn].description);
                }
                drawNavigation();
                state_changed_ =false;
            }

            pressed_ = false;
        } 
        this_thread::sleep_for(chrono::milliseconds(30));
    }
}

void CampusGraphDrawer::drawBackground()
{
    CUI::SetBackgroundColor(CUI::Color::WHITE);
    char blank[75] = {};
    memset(blank, ' ', 75);
    CUI::SetCursorPos(0, 0);
    for(int i = 0; i < 10; i++)
    {
        cout << string(blank) << endl;
    }

    CUI::SetForegroundColor(CUI::Color::YELLO);
    CUI::SetBackgroundColor(CUI::Color::BLUE);
    CUI::SetCursorPos(0, 0);
    printf("                      HITSZ Campus Navigation System                       \n");
    
    CUI::SetBackgroundColor(CUI::Color::GREEN);
    CUI::SetForegroundColor(CUI::Color::WHITE);
    CUI::SetCursorPos(0, 11);
    printf("                          Designed By Cao Ming                             \n");

    if(state_ == NAVIGATION)
    {
        char side_blank[40];
        memset(side_blank, ' ', 40);
        CUI::SetBackgroundColor(CUI::Color::DEEP_GREEN);
        CUI::SetForegroundColor(CUI::Color::WHITE);
        for(int i = 1; i < 12; i++)
        {
            if(i == 1)
                CUI::SetBackgroundColor(CUI::Color::GREEN);
            else if (i == 11)
                CUI::SetBackgroundColor(CUI::Color::BLUE);
            else
                CUI::SetBackgroundColor(CUI::Color::DEEP_GREEN);
            CUI::SetCursorPos(76, i);
            cout << string(side_blank).substr(0, 39) << endl;
        }
    }
}

void CampusGraphDrawer::drawWelcome()
{
    drawBackground();


    for(int i = 0; i < menu_buttons_.size(); i++)
    {
        menu_buttons_[i].Draw();
    }
}

void CampusGraphDrawer::drawNavigation()
{
    drawBackground();

    for(int i = 0; i < polylines_.size(); i++)
    {
        polylines_[i].Draw();
    }

    for(int i = 0; i < vertex_buttons_.size(); i++)
    {
        vertex_buttons_[i].Draw();
    }

    for(int i = 0; i < texts_.size(); i++)
    {
        texts_[i].Draw();
    }
}

char nonblocking_input( void )
{
    char input_ch;
    struct termios newt, oldt;
    
    int tty = open("/dev/tty", O_RDONLY);    //Open control terminal
    
    tcgetattr(tty, &oldt);            //Get terminal properties
    newt = oldt;
    
    //Set characters are not buffered(~ICANON) and do not echo(~ECHO).
    //You can also choose only one of them.
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr(tty, TCSANOW, &newt);    
    read(tty, &input_ch, 1);
    tcsetattr(tty, TCSANOW, &oldt);        //Restore terminal properties
    return input_ch;
}

void CampusGraphDrawer::readKeyboardInput()
{
    char c;
    while(c = nonblocking_input())
    {
        lock_guard<mutex> kb_lock(kb_mutex_);
        switch (c)
        {
        case 'a': // left
        case 'w': // up
        case 'd': // right
        case 's': // down
        case 10: // enter
            pressed_ = true;
            kb_input_ = c;
            break;
        default:
            break;
        }
        if(c <= '9' && c >= '0')
        {
            pressed_ = true;
            kb_input_ = c;
        }
    }
}