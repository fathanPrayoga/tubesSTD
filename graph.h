#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>

using namespace std;

typedef struct vertex *adrVertex;
typedef struct edge *adrEdge;

struct vertex {
    string idVertex;
    string namaStasiun; // ganti string biar stasiunnya bisa banyak
    adrVertex nextVertex;
    adrEdge firstEdge;
};

struct edge {
    string destVertexId;
    string lokasi;
    int jarak;
    adrEdge nextEdge;
};

struct graph {
    adrVertex firstVertex;
};

void createEdge(string destVertexID, int edgeWeight, adrEdge &e, string edgeLokasi);
void createVertex(string newVertexID, string namaStasiun, adrVertex &v);
void initGraph(graph &G);
bool vertexExists(const graph &G, string id);
void addVertex(graph &G, string newVertexID, string namaStasiun);
void addEdge(graph &G, string sourceVertexID, string destVertexID, int edgeWeight, string edgeLokasi);
void showGraph(const graph &G);
void printGraph(const graph &G, string startVertexID);
void dekatStasiun(const graph &G, const string &stationID);

#endif
