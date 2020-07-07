//
// Created by cm on 2020/6/26.
//

#include "Graph.h"

#include <stack>
#include <queue>
#include <algorithm>
#include <functional>

static std::string _CutParenthesesNTail(std::string&& prettyFuncon)
{
    auto pos = prettyFuncon.find('(');
    if(pos!=std::string::npos)
        prettyFuncon.erase(prettyFuncon.begin()+pos, prettyFuncon.end());

    return std::move(prettyFuncon);
}

#define __STR_FUNCTION__ _CutParenthesesNTail(std::string(__PRETTY_FUNCTION__))

using namespace std;
Graph::Graph(DataType type, uint vertex_num) : type_(type), vertex_num_(vertex_num)
{
    if(type_ == AdjacentMatrix)
    {
        adjacent_matrix_.resize(vertex_num);
        for(int i = 0; i < vertex_num; i++)
        {
            adjacent_matrix_[i].resize(vertex_num, 0);
        }
    }
    cout << __STR_FUNCTION__  << ": This is a graph which based on ";
    if(type_ == AdjacentList)
        cout << "adjacent list" << endl;
    else
        cout << "adjacent matrix" << endl;

}

void Graph::AddEdge(int from_vertex, int to_vertex, int weight)
{
    if(type_ == AdjacentList)
    {
        adjacent_list_[from_vertex].push_back(make_pair(to_vertex, weight));
    }
    else if(type_ == AdjacentMatrix)
    {
        adjacent_matrix_[from_vertex][to_vertex] = weight;
    }
}

void Graph::Dijkstra(int from_vertex, int to_vertex)
{
    struct Vertex
    {
        int dist = 1000;
        bool known = false;
        int prev;
    };
    vector<Vertex> vertices(vertex_num_);
    vertices[from_vertex].dist = 0;

    auto getAdjacent = [&](int index)
    {
        vector<pair<int, int>> res;
        if(type_ == AdjacentList)
        {
            for(pair<int, int> vertex_and_weight : adjacent_list_[index])
            {
                res.push_back(vertex_and_weight);
            }
        }
        else if(type_ == AdjacentMatrix)
        {
            for(int i = 0; i < vertex_num_; i++)
            {
                int weight = adjacent_matrix_[index][i];
                if(weight > 0)
                {
                    res.push_back(make_pair(i, weight));
                }
            }
        }
        return res;
    };

    auto findSmallestUnknownDistVertex = [& vertices]()
    {
        int smallest_dist = 1001;
        int smallest_index = -1;
        for(int i = 0; i < vertices.size(); i++)
        {
            if(vertices[i].known)
                continue;
            if(vertices[i].dist < smallest_dist)
            {
                smallest_dist = vertices[i].dist;
                smallest_index = i;
            }
        }
        return smallest_index;
    };

    for( ; ; )
    {
        int smallest_index = findSmallestUnknownDistVertex();
        if(smallest_index == -1)
            break;
        vertices[smallest_index].known = true;

        vector<pair<int, int>> adjacent_vertices = getAdjacent(smallest_index);
        for(auto adj : adjacent_vertices)
        {
            if(vertices[adj.first].known)
                continue;
            int dist = vertices[smallest_index].dist + adj.second;
            if(dist < vertices[adj.first].dist)
            {
                vertices[adj.first].dist = dist;
                vertices[adj.first].prev = smallest_index;
            }
        }
    }
    stack<int> record;
    int cur_vertex = to_vertex;
    while(vertices[cur_vertex].prev != from_vertex)
    {
        cur_vertex = vertices[cur_vertex].prev;
        record.push(cur_vertex);
    }
    record.push(from_vertex);
    cout << __STR_FUNCTION__ << ": Shortest path from " << from_vertex << " to " << to_vertex << " is " << endl;
    while(!record.empty())
    {
        cout << record.top() <<" -> ";
        record.pop();
    }
    cout << to_vertex << endl;
    cout << __STR_FUNCTION__ << ": Shortest dist from " << from_vertex << " to " << to_vertex << " is "<< vertices[to_vertex].dist << endl;
}

void Graph::KruskalMST()
{
    auto getAllEdges = [&]()
    {
        vector<tuple<int, int, int>> res;
        if(type_ == AdjacentList)
        {
            for(auto adj : adjacent_list_)
            {
                for (int i = 0; i < adj.second.size(); i++)
                {
                    res.push_back(make_tuple(adj.first, adj.second[i].first, adj.second[i].second));
                }
            }
        }
        else
        {
            for(int i = 0; i < vertex_num_; i++)
                for(int j = 0; j < vertex_num_; j++)
                {
                    if(adjacent_matrix_[i][j] > 0)
                        res.push_back(make_tuple(i, j, adjacent_matrix_[i][j]));
                }
        }
        return res;
    };

    struct TreeNode
    {
        int index = -1;
        TreeNode* father = this;
        vector<TreeNode*> children;
        vector<int> weights;
        TreeNode* GetRoot()
        {
            TreeNode* cur = this;
            while(cur != cur->father)
            {
                cur = cur->father;
            }
            return cur;
        }
    };

    vector<TreeNode> mst(vertex_num_);
    for(int i = 0; i < vertex_num_; i++)
    {
        mst[i].index = i;
    }
    vector<tuple<int, int, int>> all_edges = getAllEdges();
    sort(all_edges.begin(), all_edges.end(), [](tuple<int, int, int>& lhs, tuple <int, int, int>& rhs)
    {
        return(get<2>(lhs) < get<2>(rhs));
    });
    for(auto edge : all_edges)
    {
        int from_vertex = get<0>(edge);
        int to_vertex = get<1>(edge);
        if(mst[from_vertex].GetRoot() != mst[to_vertex].GetRoot())
        {
            if(mst[from_vertex].GetRoot() != &mst[from_vertex])
            {
                mst[to_vertex].father = &mst[from_vertex];
                mst[from_vertex].children.push_back(&mst[to_vertex]);
                mst[from_vertex].weights.push_back(get<2>(edge));
            } else
            {
                mst[from_vertex].father = &mst[to_vertex];
                mst[to_vertex].children.push_back(&mst[from_vertex]);
                mst[to_vertex].weights.push_back(get<2>(edge));
            }
        }
    }

    TreeNode* root = mst[0].GetRoot();
    int vec_left[100] = {0};
    cout << __STR_FUNCTION__ << ": The Kruskal's minimum spanning Tree is " << endl;
    function<void(TreeNode*, int)> printTree = [&](TreeNode *root, int ident)
    {
        if (ident > 0)
        {
            for (int i = 0; i < ident - 1; ++i)
            {
                printf(vec_left[i] ? "│   " : "    ");
            }
            printf(vec_left[ident - 1] ? "├── " : "└── ");
        }
        printf("%d\n", root->index);
        if (root->children.empty())
        {
            return;
        }

        for (TreeNode *child:root->children)
        {
            if(child != root->children.back())
                vec_left[ident] = 1;
            else
                vec_left[ident] = 0;
            printTree(child, ident + 1);
        }
    };

    printTree(root, 0);
}
