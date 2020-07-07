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
}

void CampusGraph::addVertices()
{
    CampusVertex v;
    v.x = 108;
    v.y = 120;
    v.name = "E";
    v.description = "";
    vertices_.push_back(v);

    v.x = 155;
    v.y = 120;
    v.name = "D";
    v.description = "";
    vertices_.push_back(v);

    v.x = 197;
    v.y = 120;
    v.name = "F";
    v.description = "";
    vertices_.push_back(v);

    v.x = 226;
    v.y = 120;
    v.name = "C";
    v.description = "";
    vertices_.push_back(v);

    v.x = 248;
    v.y = 163;
    v.name = "A";
    v.description = "";
    vertices_.push_back(v);

    v.x = 303;
    v.y = 149;
    v.name = "B";
    v.description = "";
    vertices_.push_back(v);

    v.x = 345;
    v.y = 189;
    v.name = "G";
    v.description = "";
    vertices_.push_back(v);

    v.x = 428;
    v.y = 228;
    v.name = "K";
    v.description = "";
    vertices_.push_back(v);

    v.x = 427;
    v.y = 282;
    v.name = "J";
    v.description = "";
    vertices_.push_back(v);

    v.x = 461;
    v.y = 303;
    v.name = "H";
    v.description = "";
    vertices_.push_back(v);
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
    for(int i = 0; i < cg_.vertices_.size(); i++)
    {
        float grid_x = (cg_.vertices_[i].x - origin_x) / kGridWidth;
        float grid_y = (cg_.vertices_[i].y - origin_y) / kGridHeight;
        CUI::Button b(grid_x, grid_y, cg_.vertices_[i].name);
        buttons_.push_back(b);
    }
};

void CampusGraphDrawer::Spin()
{
    system("clear");
    char c;
    while(1)
    {
        if(state_changed_)
        {
            if(state_ == NAVIGATION)
            {
                static int last_curserOn = 0;
                buttons_[last_curserOn].SetCurserOn(false);
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
                default:
                    break;
                }
                buttons_[last_curserOn].SetCurserOn(true);
                drawNavigation();
            }

            state_changed_ = false;
        } 
        this_thread::sleep_for(chrono::milliseconds(300));
    }
}

void CampusGraphDrawer::drawNavigation()
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

    for(int i = 0; i < buttons_.size(); i++)
    {
        buttons_[i].Draw();
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
            state_changed_ = true;
            kb_input_ = c;
            break;
        default:
            break;
        }
    }
}