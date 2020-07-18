#include "campus_graph_drawer.h"
#include <chrono>
#include <algorithm>
#include <stdio.h>                                 
#include <stdlib.h>
#include <fcntl.h>
#include <memory.h>
#include <unistd.h>
#include <termios.h>
#include <cmath>

using namespace std;

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
        if(cg_.vertices_[i].name.substr(0, 6) == "Litchi")
        {
            b.SetPadding(2, 1);
            b.SetColor(CUI::RED);
        }
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
                state_changed_ = false;
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
                        state_ = GUIDE;
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
                        texts_[6].SetColor(CUI::RED);
                        n_str += kb_input_;
                        texts_[6].SetText("        " + n_str);
                    }

                }
                if(state_changed_)
                {
                    clearAllState();
                    texts_[0].SetText("1. Please select starting point.");
                    texts_[7].SetText("--------------------------");
                }
                if(pressed_ == true)
                {
                switch (kb_input_)
                {
                {
                case 'd':
                case 's':
                case 'a':
                case 'w':
                    int neigh = cg_.getVertexNeighbour(last_curserOn, kb_input_);
                    if(neigh != -1)
                        last_curserOn = neigh;
                    break;
                }
                case 10:
                    if(pressed_count == 0)
                    {
                        texts_[2].SetColor(CUI::RED);
                        texts_[2].SetText("        " + cg_.vertices_[last_curserOn].name);
                        vertex_buttons_[last_curserOn].SetPressed(true);
                        texts_[3].SetText("2. Please select destination.");
                        from_vertex = last_curserOn;
                    }
                    if(pressed_count == 1)
                    {
                        texts_[4].SetColor(CUI::RED);
                        texts_[4].SetText("        " + cg_.vertices_[last_curserOn].name);
                        vertex_buttons_[last_curserOn].SetPressed(true);
                        texts_[5].SetText("3. Please input n.");
                        to_vertex = last_curserOn;
                    }
                    if(pressed_count == 2)
                    {
                        int via_n = atoi(n_str.c_str());
                        vector<string> res = cg_.QueryPathViaN(from_vertex, to_vertex, via_n);
                        for(int i = 0; i < (int)res.size() - 1; i++)
                        {
                            polylines_[cg_.edges_map_[make_pair(res[i], res[i+1])]].SetActive(true);
                        }
                        for(int i = 0; i < texts_.size(); i++)
                        {
                            texts_[i].SetText("");
                        }
                        string res_description = cg_.genNavigationResultDescription(res);
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
                        texts_[7].SetText("--------------------------");
                    }
                    pressed_count ++;
                    break;
                case 27:
                    state_ = WELCOME;
                    state_changed_ = true;
                    clearAllState();
                    continue;
                default:
                    break;
                }
                if(!vertex_buttons_[last_curserOn].Pressed())
                    vertex_buttons_[last_curserOn].SetCurserOn(true);
                if(pressed_count != 3)
                    texts_[8].SetText(cg_.vertices_[last_curserOn].description);
                }
                drawNavigationOrGuide();
                state_changed_ =false;
            }
            else if(state_ == GUIDE)
            {
                static int last_curserOn = 0;
                static int pressed_count = 0;
                if(state_changed_)
                {
                    clearAllState();
                    texts_[7].SetText("--------------------------");
                }
                if(pressed_)
                {
                    switch (kb_input_)
                    {
                        {
                            case 'd':
                            case 's':
                            case 'a':
                            case 'w':
                                vertex_buttons_[last_curserOn].SetCurserOn(false);
                                int neigh = cg_.getVertexNeighbour(last_curserOn, kb_input_);
                                if(neigh != -1)
                                    last_curserOn = neigh;
                                break;
                        }
                        case 10: // Enter;
                        // pressed_count ++;
                        if(pressed_count == 0)
                        {
                            vector<vector<string>> all_paths(cg_.vertices_.size());
                            for(int i = 0; i < cg_.vertices_.size(); i++)
                            {
                                if(cg_.vertices_[i].name.substr(0, 6) == "Litchi")
                                    continue;
                                if(i == last_curserOn)
                                    continue;
                                vector<string> path = cg_.QueryShortestPath(last_curserOn, i);
                                all_paths[i] = path;
                            }
                            sort(all_paths.begin(), all_paths.end(), 
                            [&](vector<string>& lhs, vector<string>& rhs)
                            {
                                return cg_.getPathLength(lhs) < cg_.getPathLength(rhs);
                            }
                            );
                            for(int i = 0; i < texts_.size(); i++)
                                texts_[i].SetText("");
                            texts_[0].SetText(cg_.genGuideResultDescription(all_paths));
                        }
                        if(pressed_count == 2)
                        {
                            
                        }
                        break;
                        case 27:
                        state_ = WELCOME;
                        state_changed_ = true;
                        continue;
                    default:
                        break;
                    }
                }
                vertex_buttons_[last_curserOn].SetCurserOn(true);
                drawNavigationOrGuide();
                state_changed_ = false;
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
    for(int i = 0; i < 12; i++)
    {
        cout << string(blank) << endl;
    }

    CUI::SetForegroundColor(CUI::Color::YELLO);
    CUI::SetBackgroundColor(CUI::Color::BLUE);
    CUI::SetCursorPos(0, 0);
    printf("                      HITSZ Campus Navigation System                       \n");
    
    CUI::SetBackgroundColor(CUI::Color::GREEN);
    CUI::SetForegroundColor(CUI::Color::WHITE);
    CUI::SetCursorPos(0, 13);
    printf("                          Designed By Cao Ming                             \n");

    char side_blank[40];
    memset(side_blank, ' ', 40);
    CUI::SetBackgroundColor(CUI::Color::DEEP_GREEN);
    CUI::SetForegroundColor(CUI::Color::WHITE);
    for(int i = 1; i < 14; i++)
    {
        if(i == 1)
        {
            CUI::SetBackgroundColor(CUI::Color::GREEN);
            char title_array[40];
            memset(title_array, ' ', 40);
            string str_title;
            if(state_ == WELCOME)
                str_title = "Welcome";
            else if(state_ == NAVIGATION)
                str_title = "Navigation";
            else
                str_title = "Guide";
            
            int start = (40 - str_title.size()) / 2; 
            for(int i = 0; i < str_title.size(); i++)
            {
                title_array[start + i] = str_title[i];   
            }
            CUI::SetCursorPos(76, i);
            cout << string(title_array).substr(0, 39) << endl;
        }
        else if (i == 13)
            CUI::SetBackgroundColor(CUI::Color::BLUE);
        else
            CUI::SetBackgroundColor(CUI::Color::DEEP_GREEN);
        CUI::SetCursorPos(76, i);
        if(i != 1)
            cout << string(side_blank).substr(0, 39) << endl;
        
    }
}

void CampusGraphDrawer::drawWelcome()
{
    clearAllState();
    drawBackground();


    for(int i = 0; i < menu_buttons_.size(); i++)
    {
        menu_buttons_[i].Draw();
    }

    string welcome_str = 
    R"(       _   __ ____  _____  __ 
      / | / // __ \/ ___/ / / 
     /  |/ // /_/ /\__ \ / /  
    / /|  // _, _/___/ // /___
   /_/ |_//_/ |_|/____//_____/)";
    texts_[2].SetColor(CUI::YELLO);
    texts_[2].SetText(welcome_str);
    texts_[2].Draw();
    texts_[2].SetColor(CUI::WHITE);
    texts_[8].SetText("Harbin Institute of Technology SZ");
    texts_[8].Draw();
}

void CampusGraphDrawer::drawNavigationOrGuide()
{
    // clearAllState();
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
        case 27: // esc
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