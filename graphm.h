#ifndef GRAPHM_H
#define GRAPHM_H
#include <iostream>
#include "nodedata.h"
#include <fstream>
#include <string>
#include "limits.h"
using namespace std;

const int MAXNODES = 101;                                      //never use zero as a subscript

 struct TableType 
 {
    bool visited;                                                                // whether node has been visited
    int dist;                                                                       // shortest distance from source known so far
    int path;                                                                      // previous node in path of min dist
    TableType()
    {
        visited = false;
        dist = INT_MAX;
        path = 0;
    }
};

class GraphM
{
    private:
        NodeData data[MAXNODES];                            // data for graph nodes
        int C[MAXNODES][MAXNODES];                   // Cost array, the adjacency matrix
        int size;                                                                    // number of nodes in the graph
        TableType T[MAXNODES][MAXNODES];      // stores visited, distance, path

    public:
        GraphM();

        void buildGraph(ifstream&);
        void insertEdge(int, int, int);
        void removeEdge(int, int);
        void findShortestPath();
        int min(int, int);
        void displayAll();
        void REC(int j, int i, TableType T[][MAXNODES]);
        int getV(const int) const;
        void display(int, int);
        void names(int, int, TableType T[][MAXNODES]);
};

#endif