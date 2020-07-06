//
// Created by cm on 2020/6/26.
//

#ifndef HW2_GRAPH_H
#define HW2_GRAPH_H

#include <iostream>
#include <unordered_map>
#include <vector>

enum DataType
{
    AdjacentList,
    AdjacentMatrix
};


class Graph {
public:
    Graph(DataType type, uint vertex_num_);
    void AddEdge(int from_vertex, int to_vertex, int weight);
    void Dijkstra(int from_vertex, int to_vertex);
    void KruskalMST();
private:
    DataType type_;
    uint vertex_num_;
    std::unordered_map<int, std::vector<std::pair<int, int>>> adjacent_list_;
    std::vector<std::vector<int>> adjacent_matrix_;
};


#endif //HW2_GRAPH_H
