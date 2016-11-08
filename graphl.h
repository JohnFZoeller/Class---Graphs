#ifndef GRAPHL_H
#define GRAPHL_H
#include <iostream>
#include <fstream>
#include <string>
#include "nodedata.h"
#include "limits.h"
using namespace std;

struct EdgeNode;

struct GraphNode
    {                                  
        EdgeNode* edgeHead;                                                           // head of the list of edges
        NodeData* data;                                                                    // data information about each node
        bool visited;                
    };

struct EdgeNode 
    {
        int adjGraphNode;                                                                   //subscript of the adjacent graph node
        EdgeNode* nextEdge;                                                              //next pointer
    };

class GraphL
{
    private:
        GraphNode *arr;
        int nodes;

    public:
        GraphL();
        ~GraphL();

        void buildGraph(ifstream&);
        void setEdges(GraphNode*, ifstream&);
        void displayGraph();
        void depthFirstSearch();
        void dfs(GraphNode&);
};

#endif