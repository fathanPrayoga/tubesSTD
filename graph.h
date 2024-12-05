#include <iostream>
#include <string>
using namespace std;


typedef struct vertex *adrVertex;
typedef struct edge *adrEdge;

struct vertex {
    char idVertex;
    adrVertex nextVertex;
    adrEdge firstEdge;
};


struct edge {
    char destVertexId;
    string lokasi;
    int jarak;
    adrEdge nextEdge;
};


struct graph {
    adrVertex firstVertex;
};
