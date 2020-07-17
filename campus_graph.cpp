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
#include <cmath>
#include <unordered_map>

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

    v.x = 410;
    v.y = 351;
    v.name = "T";
    v.description = "Building T, Teaching building II, locates at (" + to_string((int)v.x) + 
     ", " + to_string((int)v.y) + ").";
    vertices_.push_back(v);
    
    v.x = 260;
    v.y = 351;
    v.name = "L1";
    v.description = "Building L1, Dormitory I, locates at (" + to_string((int)v.x) + 
     ", " + to_string((int)v.y) + ").";
    vertices_.push_back(v);

    v.x = 147;
    v.y = 351;
    v.name = "L2";
    v.description = "Building L2, Dormitory II, locates at (" + to_string((int)v.x) + 
     ", " + to_string((int)v.y) + ").";
    vertices_.push_back(v);

    v.x = 170;
    v.y = 210;
    v.name = "Litchi Hill 1";
    v.description = "";
    vertices_.push_back(v);

    v.x = 300;
    v.y = 230;
    v.name = "Litchi Hill 2";
    v.description = "";
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
    edges_.push_back(make_pair("H", "T"));
    edges_.push_back(make_pair("J", "T"));
    edges_.push_back(make_pair("L1", "T"));
    edges_.push_back(make_pair("L1", "A"));
    edges_.push_back(make_pair("L1", "L2"));
    edges_.push_back(make_pair("L2", "D"));

    for(int i = 0; i < edges_.size(); i++)
    {
        vertices_map_[edges_[i].first]->neighbours.push_back(vertices_map_[edges_[i].second]);
        vertices_map_[edges_[i].second]->neighbours.push_back(vertices_map_[edges_[i].first]);

        edges_map_[make_pair(edges_[i].first, edges_[i].second)] = i;
        edges_map_[make_pair(edges_[i].second, edges_[i].first)] = i;
    }
}


vector<string> CampusGraph::QueryPathViaN(CampusVertex& start, CampusVertex& end, int n)
{
    map<string, int> visited;
    visited[start.name] = n;
    vector<vector<string>> visited_res;
    queryPathSub(start, end, n-1, visited, visited_res);
    
    if(visited_res.size() > 0)
    {
        float shortest_length = numeric_limits<float>::max();
        int shortest_index = -1;
        for(int i = 0; i < visited_res.size(); i++)
        {
            float cur_length = getPathLength(visited_res[i]);
            if(cur_length < shortest_length)
            {
                shortest_length = cur_length;
                shortest_index = i;
            }
        }
        return visited_res[shortest_index];
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

vector<string> CampusGraph::QueryShortestPath(const int start, const int end)
{
    /**************A_sta**************/
    vector<string> res;
    vector<CampusVertex*> fathers(vertices_.size());

    /* vertice name, g, h */
    unordered_map<string, pair<float, float>> open_set; 
    map<string, bool> close_set;

    open_set[vertices_[start].name].first = 0;
    open_set[vertices_[start].name].second = distOfVertices(vertices_[start], vertices_[end]);
    while(!open_set.empty())
    {
        CampusVertex* smallest;
        float min_val = numeric_limits<float>::max();
        for(auto item : open_set)
        {
            if(item.second.first + item.second.second < min_val)
            {
                smallest = vertices_map_[item.first];
                min_val = item.second.first + item.second.second;
            }
        }
        if(smallest->name == vertices_[end].name)
        {
            while(smallest->name != vertices_[start].name)
            {
                res.push_back(smallest->name);
                smallest = fathers[vertices_index_map_[smallest->name]];
            }
            res.push_back(vertices_[start].name);
            reverse(res.begin(), res.end());
            return res;
        }
        close_set[smallest->name] = true;

        for(int i = 0; i < smallest->neighbours.size(); i++)
        {
            CampusVertex* cur_neighbour = smallest->neighbours[i];
            if(close_set.count(cur_neighbour->name) > 0)
            {
                continue;
            }
            float g = open_set[smallest->name].first + distOfVertices(*smallest, *cur_neighbour);
            float h = distOfVertices(*cur_neighbour, vertices_[end]);
            /* if cur_neighbour not in openset */
            if(open_set.count(cur_neighbour->name) == 0)
            {
                open_set[cur_neighbour->name].first = g;
                open_set[cur_neighbour->name].second = h;
                fathers[vertices_index_map_[cur_neighbour->name]] = smallest;
            }
            else
            {
                if(open_set[cur_neighbour->name].first + 
                    open_set[cur_neighbour->name].second > g+h)
                    {
                        open_set[cur_neighbour->name].first = g;
                        open_set[cur_neighbour->name].second = h;
                        fathers[vertices_index_map_[cur_neighbour->name]] = smallest;
                    }
            }
            
        }
        open_set.erase(smallest->name);
    }
    return vector<string>();
}

float CampusGraph::getPathLength(std::vector<std::string>& path_strs)
{
    if(path_strs.size()==0)
        return numeric_limits<float>::max();
    float res = 0;
    for(int i = 0; i < path_strs.size()-1; i++)
    {
        CampusVertex& start = *vertices_map_[path_strs[i]];
        CampusVertex& end = *vertices_map_[path_strs[i+1]];
        float cur_length = sqrt((start.x - end.x) * (start.x - end.x)  +
            (start.y - end.y) * (start.y - end.y));
        res += cur_length;
    }
    return res;
}

int CampusGraph::getVertexNeighbour(int vertex_index, char neigh_dir)
{
    function<bool(int, int, int, int)> neigh_func;
    switch (neigh_dir)
    {
    case 'w':
        neigh_func = [](int x1, int y1, int x2, int y2)
            {return (y2 < y1) && (y1 - y2 > abs(x2-x1));};
        break;
    case 'a':
        neigh_func = [](int x1, int y1, int x2, int y2)
            {return (x2 < x1) && (x1 - x2) > abs(y2 - y1);};
        break;
    case 's':
        neigh_func = [](int x1, int y1, int x2, int y2)
            {return (y2 > y1) && (y2 - y1) > abs(x2- x1);};
        break;
    case 'd':
        neigh_func = [](int x1, int y1, int x2, int y2)
            {return (x2 > x1) && (x2 -x1) > abs(y2 - y1);};
        break;
    default:
        break;
    }
    vector<CampusVertex*> neighs = vertices_[vertex_index].neighbours;
    for(int i = 0; i < neighs.size(); i++)
    {
        int x1 = vertices_[vertex_index].x;
        int y1 = vertices_[vertex_index].y;
        int x2 = neighs[i]->x;
        int y2 = neighs[i]->y;
        if(neigh_func(x1, y1, x2, y2))
            return vertices_index_map_[neighs[i]->name];
    }
    return -1;
}

string CampusGraph::genNavigationResultDescription(vector<string>& res)
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

string CampusGraph::genGuideResultDescription(vector<string>& res)
{
    string description;
    for(int i = 0; i < res.size(); i++)
    {
        description += res[i];
        if(i != res.size() -1)
            description += "->";
    }
}

