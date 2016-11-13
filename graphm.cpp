#include "graphm.h"
#include <fstream>
#include <iostream>
#include <string>  
#include "limits.h"                 

// ------------------------------------Constructor----------------------------------------------- 
// Description: initializes size to 0, data array to empty strings,
//  cost array to 102030 (which i treat as infinity)
//      TableType array 
// -------------------------------------------------------------------------------------------------------------
GraphM::GraphM()
{
    size = 0;
    NodeData data[] = {};
    TableType T[MAXNODES][MAXNODES];

    for(int i = 1; i < MAXNODES; i++)
        for(int j = 1; j < MAXNODES; j++)
            C[i][j] = 102030;
}

// ------------------------------------buildGraph----------------------------------------------- 
// Description: calls display help, returns ostream out
// -------------------------------------------------------------------------------------------------------------
void GraphM::buildGraph(ifstream& in)  {
    int to, from, dumy;

    in >> size;
    in.ignore(100, '\n');

    for(int i = 1; i <= size; i ++){
        data[i].setData(in); 
    }
    if(size != 0){
    for(;;){
        in >> from >> to;
        if(from == 0) {
            in >> dumy;
            in.clear();
            in.ignore(100, '\n');
            break;
        }

        in >> C[from][to];
        in.clear();
        in.ignore(100, '\n');
    }
    }
}

// ------------------------------------findShortestPath----------------------------------------------- 
// Description: calls display help, returns ostream out
// -------------------------------------------------------------------------------------------------------------
void GraphM::findShortestPath(){
    int v = 0;

    for(int source = 1; source <= size; source++){
        T[source][source].dist = 0;

        for(int dest = 1; dest <= size; dest++){

            v = getV(source);
            T[v][v].visited = true;

            for(int w = 1; w <= size; w++){
                if((C[v][w] > -1) && (T[w][w].visited == false)){
                    if((T[source][v].dist + C[v][w]) < T[source][w].dist){
                        T[source][w].dist =  (T[source][v].dist + C[v][w]);    
                        T[source][w].path = v;    
                    }
                }
            }
        }
        for(int j = 1; j <= size; j++)
            T[j][j].visited = false;
    }
}

// ------------------------------------displayAll----------------------------------------------- 
// Description: displays contents of graph and the shortest paths
//  calls recursive function REC to display the shortest path 
// -------------------------------------------------------------------------------------------------------------
void GraphM::displayAll()
{
    cout << "Description:      From Node:    To Node:    Djikstra's Path:" << endl;
    for(int j = 1; j <= size; j++){
        cout << data[j] << endl << endl;

        for(int i = 1; i <= size; i++){
            if(i == j) continue;

            cout << "            " << j << "        " << i << "        ";

            if(T[j][i].dist < 102030) //change to 102030
            {
                cout << T[j][i].dist << "     ";
                REC(j, T[j][i].path, T);

                cout << i << endl;
            }
            else cout <<  "----" << endl;

        }
    }
}

// ------------------------------------display----------------------------------------------- 
// Description: takes two integers representing the from and to nodes 
//  calls recursive function REC to display the shortest path 
//     calls recursive names function to display the names of the shortest path
// -------------------------------------------------------------------------------------------------------------
void GraphM::display(int i, int j)
{
    cout << i << "       " << j << "     ";
    if(T[i][j].dist < 102030) //change to 102030 
    {
        cout  << T[i][j].dist << "       ";
        REC(i, T[i][j].path, T);
        cout << j << endl;
        names(i, T[i][j].path, T);
        cout << data[j] << endl << endl;
    }
    else cout << "----" << endl;
}

// ------------------------------------names----------------------------------------------- 
// Description: recursive names display function
// -------------------------------------------------------------------------------------------------------------
void GraphM::names(int j, int path, TableType T[][MAXNODES]){
    if(path == 0)
        cout << "";
    if(path != j)
        names(j, T[j][path].path, T);
    cout << data[path] << endl;
}

// ------------------------------------REC----------------------------------------------- 
// Description: recursive path display function
// -------------------------------------------------------------------------------------------------------------
void GraphM::REC(int j, int path, TableType T[][MAXNODES]){
    if(path == 0)
         cout << "";
    if(path != j)
        REC(j, T[j][path].path, T);
    cout << path << " ";
}

// ------------------------------------getV----------------------------------------------- 
// Description: returns the lowest distance 
// -------------------------------------------------------------------------------------------------------------
int GraphM::getV(const int vertex) const{
    int low = 0;

    for(int i = 1; i <= size; i++)
        if(T[vertex][i].dist < T[vertex][low].dist && T[i][i].visited == false)
            low = i;

    return low;
}

// ------------------------------------insertEdge----------------------------------------------- 
// Description: 
/*the main assumption here is that if an edge already exists between two nodes
//im just going to replace that edge with the users new edge no matter what
//assuming that insert edge is also edit edge
//also use absolute values for from, to, and distance
//if from, to, or distance is a zero nothing gets inserted. 
*/
// -------------------------------------------------------------------------------------------------------------
void GraphM::insertEdge(int from, int to, int d){
    if(from != 0 && to != 0 && d != 0){
        if(from < 0)
            from = -from;
        if(to < 0)
            to = -to;
        if(d < 0)
            d = -d;

        C[from][to] = d;
    }
}

// ------------------------------------removeEdge----------------------------------------------- 
// Description: sets the cost from one node to another to infinity
// -------------------------------------------------------------------------------------------------------------
void GraphM::removeEdge(int from, int to){
    if(from != 0 && to != 0){
        if(from < 0)
            from = -from;
        if(to < 0)
            to = -to;

        C[from][to] = 102030; //possibly change to 102030
    }
}

// ------------------------------------min----------------------------------------------- 
// Description: didnt end up using, but returns the smaller of two numbers
// -------------------------------------------------------------------------------------------------------------
int GraphM::min(int a, int b){
    return (a < b) ? a : b;
}


