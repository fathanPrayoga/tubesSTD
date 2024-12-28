#include "graph.h"

void createEdge(string destVertexID, int waktuTempuh, adrEdge &e, string rute) {
    e = new edge;
    e->destVertexId = destVertexID;
    e->rute = rute;
    e->waktuTempuh = waktuTempuh;
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
    adrVertex src = G.firstVertex;
    while (src != nullptr && src->idVertex != sourceVertexID) {
        src = src->nextVertex;
    }

    adrVertex dest = G.firstVertex;
    while (dest != nullptr && dest->idVertex != destVertexID) {
        dest = dest->nextVertex;
    }

    if (src != nullptr && dest != nullptr) {
        adrEdge e1, e2;

        // Tambahkan edge dari source ke destination
        createEdge(destVertexID, edgeWeight, e1, edgeLokasi);
        if (src->firstEdge == nullptr) {
            src->firstEdge = e1;
        } else {
            adrEdge edgeCurr = src->firstEdge;
            while (edgeCurr->nextEdge != nullptr) {
                edgeCurr = edgeCurr->nextEdge;
            }
            edgeCurr->nextEdge = e1;
        }

        // Tambahkan edge dari destination ke source (arah sebaliknya) karena graf tak berarah atau dua arah
        createEdge(sourceVertexID, edgeWeight, e2, edgeLokasi);
        if (dest->firstEdge == nullptr) {
            dest->firstEdge = e2;
        } else {
            adrEdge edgeCurr = dest->firstEdge;
            while (edgeCurr->nextEdge != nullptr) {
                edgeCurr = edgeCurr->nextEdge;
            }
            edgeCurr->nextEdge = e2;
        }
    } else {
        if (src == nullptr) cout << "Stasiun asal tidak ditemukan: " << sourceVertexID << endl;
        if (dest == nullptr) cout << "Stasiun tujuan tidak ditemukan: " << destVertexID << endl;
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
        cout << "ID: " << currVertex->idVertex << " (" << currVertex->namaStasiun << ")" << endl;

        adrEdge currEdge = currVertex->firstEdge;
        while (currEdge != nullptr) {
            cout << "  -> " << currEdge->destVertexId
                 << " (Waktu: " << currEdge->waktuTempuh << " menit, Lokasi: " << currEdge->rute << ")" << endl;
            currEdge = currEdge->nextEdge;
        }
        cout << endl;
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

        // Pilih stasiun yang rute cabang, tampilkan pilihan
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
                         << destVertex->namaStasiun << ", " << temp->waktuTempuh << " menit, " << temp->rute << ")\n";
                }

                temp = temp->nextEdge;
                count++;
            }

            cout << "Pilih rute (1-" << count - 1 << " atau 0 untuk keluar): ";
            int choice;
            cin >> choice;

            // Jika pengguna memilih 0, keluar dari fungsi
            if (choice == 0) {
                cout << "Keluar dari navigasi rute.\n";
                return;
            }

            // Memilih jalur berdasarkan input pengguna
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
            cout << "- " << destVertex->namaStasiun << " (Waktu: " << edge->waktuTempuh << " menit, Lokasi: " << edge->rute << ")\n";
        }

        edge = edge->nextEdge;
    }

    cout << endl;
}

string getStationName(graph &G, string idVertex) {
    adrVertex curr = G.firstVertex;
    while (curr != nullptr) {
        if (curr->idVertex == idVertex) {
            return curr->namaStasiun; // Kembalikan nama stasiun jika ditemukan
        }
        curr = curr->nextVertex;
    }
    return "Stasiun tidak ditemukan"; // Jika tidak ditemukan
}


void findRoute(graph &G, string startVertexID, string endVertexID, string visited[], int &visitedCount, int totalTime) {
    // Cari vertex awal berdasarkan ID
    adrVertex curr = G.firstVertex;
    while (curr != nullptr && curr->idVertex != startVertexID) {
        curr = curr->nextVertex;
    }

    if (curr == nullptr) {
        cout << "Stasiun dengan ID " << startVertexID << " tidak ditemukan!" << endl;
        return;
    }

    // Tambahkan stasiun saat ini ke daftar yang sudah dikunjungi
    visited[visitedCount] = startVertexID;
    visitedCount++;

    // Jika kita sudah sampai di stasiun tujuan, hasilnya tampil
    if (startVertexID == endVertexID) {
        cout << "Rute yang ditemukan: ";
        for (int i = 0; i < visitedCount; i++) {
            cout << getStationName(G, visited[i]); // Tampilkan nama stasiun
            if (i != visitedCount - 1) cout << " -> ";
        }
        cout << " (Total waktu tempuh: " << totalTime << " menit)" << endl;
        return;
    }

    adrEdge edge = curr->firstEdge;
    while (edge != nullptr) {
        // Meriksa apakah stasiun tujuan udah pernah dikunjungi
        bool alreadyVisited = false;
        for (int i = 0; i < visitedCount; i++) {
            if (visited[i] == edge->destVertexId) {
                alreadyVisited = true;
                break;
            }
        }

        if (!alreadyVisited) {
            findRoute(G, edge->destVertexId, endVertexID, visited, visitedCount, totalTime + edge->waktuTempuh);
        }

        edge = edge->nextEdge;
    }

    // Backtracking: Keluarkan stasiun saat ini dari daftar yang dikunjungi
    visitedCount--;
}
