#include "graph.h"

void createEdge(string destVertexID, int edgeWeight, adrEdge &e, string edgeLokasi) {
    e = new edge;
    e->destVertexId = destVertexID;
    e->lokasi = edgeLokasi;
    e->jarak = edgeWeight;
    e->nextEdge = nullptr;
}

void createVertex(string newVertexID, string namaStasiun, adrVertex &v) {
    v = new vertex;
    v->idVertex = newVertexID;
    v->namaStasiun = namaStasiun;
    v->nextVertex = nullptr;
    v->firstEdge = nullptr;
}

void initGraph(graph &G) {
    G.firstVertex = nullptr;
}

bool vertexExists(const graph &G, string id) {
    adrVertex curr = G.firstVertex;
    while (curr != nullptr) {
        if (curr->idVertex == id) {
            return true;
        }
        curr = curr->nextVertex;
    }
    return false;
}

void addVertex(graph &G, string newVertexID, string namaStasiun) {
    if (vertexExists(G, newVertexID)) {
        cout << "Stasiun dengan ID " << newVertexID << " sudah ada. Tidak ditambahkan." << endl;
        return;
    }

    adrVertex v;
    createVertex(newVertexID, namaStasiun, v);

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

void addEdge(graph &G, string sourceVertexID, string destVertexID, int edgeWeight, string edgeLokasi) {
    adrVertex curr = G.firstVertex;
    while (curr != nullptr && curr->idVertex != sourceVertexID) {
        curr = curr->nextVertex;
    }

    if (curr != nullptr) {
        adrEdge e;
        createEdge(destVertexID, edgeWeight, e, edgeLokasi);

        if (curr->firstEdge == nullptr) {
            curr->firstEdge = e;
        } else {
            adrEdge edgeCurr = curr->firstEdge;
            while (edgeCurr->nextEdge != nullptr) {
                edgeCurr = edgeCurr->nextEdge;
            }
            edgeCurr->nextEdge = e;
        }
    } else {
        cout << "Stasiun asal tidak ditemukan: " << sourceVertexID << endl;
    }
}

void showGraph(const graph &G) {
    adrVertex currVertex = G.firstVertex;

    if (currVertex == nullptr) {
        cout << "Graph kosong. Tidak ada stasiun atau jalur." << endl;
        return;
    }

    cout << "=== Isi Graph ===" << endl;
    while (currVertex != nullptr) {
        cout << "Stasiun: " << currVertex->idVertex << " (" << currVertex->namaStasiun << ")" << endl;

        adrEdge currEdge = currVertex->firstEdge;
        while (currEdge != nullptr) {
            cout << "  -> " << currEdge->destVertexId
                 << " (Waktu: " << currEdge->jarak << " menit, Lokasi: " << currEdge->lokasi << ")" << endl;
            currEdge = currEdge->nextEdge;
        }

        currVertex = currVertex->nextVertex;
    }
}

void printGraph(const graph &G, string startVertexID) {
    adrVertex curr = G.firstVertex;

    // Cari vertex awal berdasarkan ID
    while (curr != nullptr && curr->idVertex != startVertexID) {
        curr = curr->nextVertex;
    }

    if (curr == nullptr) {
        cout << "Stasiun dengan ID " << startVertexID << " tidak ditemukan!" << endl;
        return;
    }


    cout << curr->namaStasiun;

    while (curr != nullptr) {
        adrEdge nextEdge = curr->firstEdge;
        if (nextEdge == nullptr) {
            break; // Tidak ada jalur keluar
        }

        // Pilih stasiun yang rute cabang, tampilin pilihan
        if (nextEdge->nextEdge != nullptr) {
            cout << "\n\nPilih rute keluar dari " << curr->namaStasiun << ":\n";

            adrEdge temp = nextEdge;
            int count = 1;
            while (temp != nullptr) {
                // Cari nama stasiun tujuan berdasarkan ID
                adrVertex destVertex = G.firstVertex;
                while (destVertex != nullptr && destVertex->idVertex != temp->destVertexId) {
                    destVertex = destVertex->nextVertex;
                }

                if (destVertex != nullptr) {
                    cout << count << ". " << destVertex->namaStasiun << " (ke "
                         << destVertex->namaStasiun << ", " << temp->jarak << " menit, " << temp->lokasi << ")\n";
                }

                temp = temp->nextEdge;
                count++;
            }

            int choice;
            cout << "Pilih rute (1-" << count - 1 << "): ";
            cin >> choice;

            // milih jalur
            temp = nextEdge;
            for (int i = 1; i < choice && temp != nullptr; i++) {
                temp = temp->nextEdge;
            }

            nextEdge = temp;
        }

        if (nextEdge != nullptr) {
            adrVertex nextVertex = G.firstVertex;
            while (nextVertex != nullptr && nextVertex->idVertex != nextEdge->destVertexId) {
                nextVertex = nextVertex->nextVertex;
            }

            if (nextVertex != nullptr) {
                cout << " - " << nextVertex->namaStasiun;
                curr = nextVertex; // Pindah ke vertex tujuan berikutnya
            } else {
                curr = nullptr;
            }
        } else {
            curr = nullptr;
        }
    }

    cout << endl;
}

void dekatStasiun(const graph &G, const string &stationID){ //nampilin stasiun yg berdekatan (masih satu arah doang yang kebaca)
    adrVertex curr = G.firstVertex;
    while (curr != nullptr && curr->idVertex != stationID) {
        curr = curr->nextVertex;
    }

    if (curr == nullptr) {
        cout << "Stasiun dengan ID " << stationID << " tidak ditemukan!" << endl;
        return;
    }

    cout << "Stasiun-stasiun yang berdekatan dengan " << curr->namaStasiun << ":\n";

    adrEdge edge = curr->firstEdge;
    while (edge != nullptr) {
        // Cari nama stasiun tujuan berdasarkan ID
        adrVertex destVertex = G.firstVertex;
        while (destVertex != nullptr && destVertex->idVertex != edge->destVertexId) {
            destVertex = destVertex->nextVertex;
        }

        if (destVertex != nullptr) {
            cout << "- " << destVertex->namaStasiun << " (Waktu: " << edge->jarak << " menit, Lokasi: " << edge->lokasi << ")\n";
        }

        edge = edge->nextEdge;
    }

    cout << endl;
}
