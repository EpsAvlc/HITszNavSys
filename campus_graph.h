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
private:
    void addVertices();
    void addEdges();
    /**
     * @brief Get the Vertex Neighbour: Get a vertex's neighbour in a specific direction
     * 
     * @param vertex_index 
     * @param neigh_dir: "w" "a" "s" "d" for differenct directions
     * @return int: neighbour vertex's index. -1 for NULL
     */
    int getVertexNeighbour(int vertex_index, char neigh_dir);
    std::string genResultDescription(std::vector<std::string>& res);
    void queryPathSub(CampusVertex& v, CampusVertex& end, int n, 
    std::map<std::string, int>& visited, std::vector<std::vector<std::string>>& res);
    float getPathLength(std::vector<std::string>& path_strs);

    std::vector<CampusVertex> vertices_;
    /* Map vertice from its name to itself*/
    std::map<std::string, CampusVertex*> vertices_map_;
    std::map<std::string, int> vertices_index_map_;
    std::vector<std::pair<std::string, std::string>> edges_;
    std::map<std::pair<std::string, std::string>, int> edges_map_;

};

#endif // !CAMPUS_GRAPH__