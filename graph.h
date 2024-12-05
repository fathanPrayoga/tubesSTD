#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <iostream>

using namespace std;

struct edge;
struct vertex;

typedef vertex* adrVertex;
typedef edge* adrEdge;

struct edge{
    int tujuan;
    double biaya;
    string tipeTrans;
};

struct graph{

};



#endif // GRAPH_H_INCLUDED
