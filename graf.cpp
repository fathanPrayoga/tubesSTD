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
                 << " (Waktu: " << currEdge->waktuTempuh << " menit, Lokasi: " << currEdge->rute << ")" << endl;
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
                         << destVertex->namaStasiun << ", " << temp->waktuTempuh << " menit, " << temp->rute << ")\n";
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
