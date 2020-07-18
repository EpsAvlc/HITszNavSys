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
#include <cmath>

/**
 * @brief Minimum spanning tree's node.
 * 
 */
struct MSTNode
{
    std::string name;
    MSTNode* father = this;
    std::vector<MSTNode*> children;
    MSTNode(std::string& _name)
    {
        name = _name;
    };
    MSTNode* GetRoot()
    {
        MSTNode* cur = this;
        while(cur != cur->father)
        {
            cur = cur->father;
        }
        return cur;
    }
};

struct CampusVertex
{
    int x;
    int y;
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
    std::vector<std::string> QueryPathViaN(CampusVertex& start, CampusVertex& end, int n);
    std::vector<std::string> QueryPathViaN(const int start, const int end, int n)
    {
        return QueryPathViaN(vertices_[start], vertices_[end], n);
    }
    std::vector<std::string> QueryPathViaN(const std::string& start, const std::string& end, int n)
    {
        return QueryPathViaN(*vertices_map_[start], *vertices_map_[end], n);
    }

    /**
     * @brief : Query Shortest Path between start and end. Use BST.
     * 
     * @param start: start vertex index 
     * @param end: end vertex index
     * @return std::vector<std::string> 
     */
    std::vector<std::string> QueryShortestPath(const int start, const int end);
    std::vector<std::string> QueryShortestPath(const std::string& start, const std::string& end)
    {
        int start_index = vertices_index_map_[start];
        int end_index = vertices_index_map_[end];
        return QueryShortestPath(start_index, end_index);
    }
private:
    void addVertices();
    void addEdges();
    void genMST();
    float distOfVertices(CampusVertex& lhs, CampusVertex& rhs)
    {
        return sqrt((lhs.x - rhs.x) * (lhs.x - rhs.x) + (lhs.y - rhs.y) * (lhs.y - rhs.y));
    }
    /**
     * @brief Get the Vertex Neighbour: Get a vertex's neighbour in a specific direction
     * 
     * @param vertex_index 
     * @param neigh_dir: "w" "a" "s" "d" for differenct directions
     * @return int: neighbour vertex's index. -1 for NULL
     */
    int getVertexNeighbour(int vertex_index, char neigh_dir);
    /**
     * @brief: give a query road result strings, generate the description.
     * 
     * @param res 
     * @return std::string 
     */
    std::string genNavigationResultDescription(std::vector<std::string>& res);
    std::string genGuideResultDescription(std::vector<std::vector<std::string>>& res);
    void queryPathSub(CampusVertex& v, CampusVertex& end, int n, 
    std::map<std::string, int>& visited, std::vector<std::vector<std::string>>& res);
    /**
     * @brief: get path length.
     * 
     * @param path_strs 
     * @return float 
     */
    float getPathLength(std::vector<std::string>& path_strs);

    std::vector<CampusVertex> vertices_;
    /* Map vertice from its name to itself*/
    std::map<std::string, CampusVertex*> vertices_map_;
    std::map<std::string, int> vertices_index_map_;
    std::vector<std::pair<std::string, std::string>> edges_;
    std::map<std::pair<std::string, std::string>, int> edges_map_;
};

#endif // !CAMPUS_GRAPH__