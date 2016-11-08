#include "graphl.h"
#include <iostream>
#include <fstream>
#include <string>
#include "limits.h"

// ------------------------------------constructor----------------------------------------------- 
// Description: sets nodes to 0 and GraphNodes array to NULL
// -------------------------------------------------------------------------------------------------------------
GraphL::GraphL()
{
    arr = NULL;
    nodes = 0;
}

// ------------------------------------destructor----------------------------------------------- 
// Description: deletes the GraphNode array
// -------------------------------------------------------------------------------------------------------------
GraphL::~GraphL()
{
	EdgeNode *temp;
	for(int i = 0; i < nodes; i++)
		delete arr[i].data;
	//nodedata *pointer;  only need to delete nodedatas corresponding to array elements
	for(int i = 0; i < nodes; i++)
	{
		EdgeNode *ptr = arr[i].edgeHead;
		while(ptr != NULL)
		{
			temp = ptr;
			ptr = ptr->nextEdge;
			delete temp;
		}
	}
	delete [] arr;
	//delete all the node data as well
	//the nodeDatas might be deleted by nodedata.h
}

// ------------------------------------buildGraph----------------------------------------------- 
// Description: reads size from file, allocates GraphNode array based on that size
//    loops through nodes.  Fills nodeData members by calling set data, allocates new edgeheads
//      sets thier nextEdges to NULL and initializes their adj numbers
// -------------------------------------------------------------------------------------------------------------
void GraphL::buildGraph(ifstream& in)
{
    in >> nodes;
    arr = new GraphNode[nodes];
    in.ignore(100, '\n');

    for(int i = 0; i < nodes; i++)
    {
        arr[i].data = new NodeData;
        arr[i].data->setData(in);
        arr[i].edgeHead = new EdgeNode;
        arr[i].edgeHead->adjGraphNode = i + 1;
        arr[i].edgeHead->nextEdge = NULL;
    }
    setEdges(arr, in);
}

// ------------------------------------depthfirstsearch----------------------------------------------- 
// Description: sets all visited to false, calls dfs to display the depth first search results. 
// -------------------------------------------------------------------------------------------------------------
void GraphL::depthFirstSearch()
{
    for(int i = 0; i < nodes; i++)
        arr[i].visited = false;

    cout << "Depth-First Ordering: ";
    for(int i = 0; i < nodes; i++)
        if(arr[i].visited == false)
            dfs(arr[i]);

    cout << endl << endl;
}

// ------------------------------------dfs----------------------------------------------- 
// Description: recursive helper function for depthfirst search
// -------------------------------------------------------------------------------------------------------------
void GraphL::dfs(GraphNode& v)
{
    v.visited = true;
    EdgeNode *ptr = NULL;

    cout << v.edgeHead->adjGraphNode << " ";

    ptr = v.edgeHead->nextEdge;

    for(; ptr != NULL; ptr = ptr->nextEdge)
        if(arr[ptr->adjGraphNode - 1].visited == false)
            dfs(arr[ptr->adjGraphNode - 1]);
}

// ------------------------------------setEdges----------------------------------------------- 
// Description: reads from file to build a list for each edgeHead
// -------------------------------------------------------------------------------------------------------------
void GraphL::setEdges(GraphNode* array, ifstream& infile)
{
    int from, to;
    int old = 1;

    EdgeNode *prev = NULL;
    EdgeNode *newNode = NULL;

   for(;;)
    {
        infile >> from >> to;
		infile.clear();
        infile.ignore(100, '\n');

        if(from == 0 || from > nodes)
            break;

        if(from != old)
        {
            old = from;
            prev = NULL;
        }

        newNode = new EdgeNode;                                             // allocate
        newNode->adjGraphNode = to;                                     // set node number
        newNode->nextEdge = prev;                  //look here
        arr[from - 1].edgeHead->nextEdge = newNode;  //and here    ALWAYS INSERT INTO THE FRONT OF THE LINKED LIST
        prev = newNode;                           //and here
    }
}

// ------------------------------------displayGraph----------------------------------------------- 
// Description: iterates through each list, displaying its contents
// -------------------------------------------------------------------------------------------------------------
void GraphL::displayGraph()
{
    EdgeNode *ptr = NULL;
    cout << "Graph:" << endl;

    for(int i = 0; i < nodes; i++)
    {
        cout << "Node " << i + 1 << "          " << *arr[i].data << endl;      
        ptr = arr[i].edgeHead;

        for(; ptr->nextEdge != NULL; ptr = ptr->nextEdge)
            cout << "   edge " << i + 1 << "  " << ptr->nextEdge->adjGraphNode << endl;
    }
    cout << endl;
}
