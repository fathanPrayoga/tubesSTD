void createEdge(char destVertexID, int edgeWeight, adrEdge &e, string edgeLokasi) {
    e = new edge;
    e->destVertexId = destVertexID;
    e->lokasi = edgeLokasi;
    e->jarak = edgeWeight;
    e->nextEdge = nullptr;
}

void createVertex(char newVertexID, adrVertex &v) {
    v = new vertex;
    v->idVertex = newVertexID;
    v->nextVertex = nullptr;
    v->firstEdge = nullptr;
}


void initGraph(graph &G) {
    G.firstVertex = nullptr;
}

bool vertexExists(const graph &G, char id) {
    adrVertex curr = G.firstVertex;
    while (curr != nullptr) {
        if (curr->idVertex == id) {
            return true;
        }
        curr = curr->nextVertex;
    }
    return false;
}

void addVertex(graph &G, char newVertexID) {
    if (vertexExists(G, newVertexID)) {
        cout << "Vertex dengan ID " << newVertexID << " sudah ada. Tidak ditambahkan." << endl;
        return;
    }

    adrVertex v;
    createVertex(newVertexID, v);
    if (G.firstVertex == nullptr) {
        G.firstVertex = v;
    } else {
        adrVertex curr = G.firstVertex;
        while (curr->nextVertex != nullptr) {
            curr = curr->nextVertex;
        }
        curr->nextVertex = v;
    }
}

void addEdge(adrVertex &v, char destVertexID, int edgeWeight, string edgeLokasi) {
    adrEdge e;
    createEdge(destVertexID, edgeWeight, e, edgeLokasi);
    if (v->firstEdge == nullptr) {
        v->firstEdge = e;
    } else {
        adrEdge curr = v->firstEdge;
        while (curr->nextEdge != nullptr) {
            curr = curr->nextEdge;
        }
        curr->nextEdge = e;
    }
}

void buildGraph(graph &G) {
    char charInput;
    int intInput;
    string lokasi;
    while (true) {
        cout << "=== Vertex ===" << endl;
        cout << "Masukkan ID Vertex (A-Z): ";
        cin >> charInput;
        if (charInput < 'A' || charInput > 'Z') break;
        addVertex(G, charInput);

        adrVertex v = G.firstVertex;
        while (v->nextVertex != nullptr) {
            v = v->nextVertex;
        }

        // Input edges untuk vertex tersebut
        cout << "=== Edges untuk Vertex " << v->idVertex << " ===" << endl;
        while (true) {
            cout << "Masukkan ID Tujuan Edge (A-Z): ";
            cin >> charInput;
            if (charInput < 'A' || charInput > 'Z') break;
            cout << "Masukkan Weight Edge: ";
            cin >> intInput;
            cout << "Masukkan lokasi : ";
            cin >> lokasi;
            addEdge(v, charInput, intInput, lokasi);
        }
    }
}

void showEdges(adrVertex v) {
    adrEdge curr = v->firstEdge;
    while (curr != nullptr) {
        cout << "\tEdge ke " << curr->destVertexId << " dengan weight " << curr->jarak << endl;
        curr = curr->nextEdge;
    }
}

void showGraph(const graph &G) {
    adrVertex curr = G.firstVertex;
    if (curr == nullptr) {
        cout << "Graph kosong." << endl;
        return;
    }
    cout << "=== Isi Graph ===" << endl;
    while (curr != nullptr) {
        cout << "Vertex: " << curr->idVertex << endl;
        showEdges(curr);
        curr = curr->nextVertex;
    }
}

