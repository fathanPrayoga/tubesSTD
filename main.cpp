#include "graph.h"
#include <iostream>

using namespace std;

void menu() {
    cout << "===== MENU =====" << endl;
    cout << "1. Tambah Stasiun (Vertex)" << endl;
    cout << "2. Tambah Jalur (Edge)" << endl;
    cout << "3. Tampilkan Graph (Detail)" << endl;
    cout << "4. Tampilkan Jalur Lintasan" << endl;
    cout << "5. Tampilkan stasiun yang berdekatan" << endl;
    cout << "6. Keluar" << endl;
    cout << "================" << endl;
}

int main() {
    graph G;
    initGraph(G);

    //stasiun lrt
    addVertex(G, "A", "Stasiun Soekarno-Hatta");
    addVertex(G, "B", "Stasiun Dadap");
    addVertex(G, "C", "Stasiun Kamalraya");
    addVertex(G, "D", "Stasiun Rawabuaya");
    addVertex(G, "E", "Stasiun Pesing");
    addVertex(G, "F", "Stasiun Grogol");
    addVertex(G, "G", "Stasiun Tomang");
    addVertex(G, "H", "Palmerah");
    addVertex(G, "I", "Gelora");
    addVertex(G, "J", "Senayan");
    addVertex(G, "K", "Dukuh Atas");
    addVertex(G, "L", "Kuningan Sentral");

    addEdge(G, "A", "B", 10, "Rute 1");
    addEdge(G, "B", "C", 15, "Rute 1");
    addEdge(G, "C", "D", 20, "Rute 1");
    addEdge(G, "D", "E", 10, "Rute 1");
    addEdge(G, "E", "F", 25, "Rute 1");
    addEdge(G, "F", "G", 30, "Rute 1");
    addEdge(G, "G", "H", 30, "Rute 1 (Pilih rute)");

    addEdge(G, "H", "I", 5, "Rute 2");
    addEdge(G, "I", "J", 5, "Rute 2");
    addEdge(G, "H", "K", 7, "Rute 3");
    addEdge(G, "K", "L", 8, "Rute 3");

    int choice;
    string sourceID, destID;
    string stasiun, lokasi;
    int weight;

    do {
        menu();
        cout << "Pilihan: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Masukkan ID Stasiun: ";
                cin >> sourceID;
                cout << "Masukkan nama stasiun: ";
                cin.ignore();
                getline(cin, stasiun);
                addVertex(G, sourceID, stasiun);
                break;
            }

            case 2: {
                cout << "Masukkan ID Stasiun Asal: ";
                cin >> sourceID;
                cout << "Masukkan ID Stasiun Tujuan: ";
                cin >> destID;
                cout << "Masukkan waktu tempuh (dalam menit): ";
                cin >> weight;
                cout << "Masukkan nama jalur: ";
                cin.ignore();
                getline(cin, lokasi);
                addEdge(G, sourceID, destID, weight, lokasi);
                break;
            }

            case 3:
                showGraph(G);
                break;

            case 4: {
                cout << "Masukkan ID Stasiun Awal: ";
                cin >> sourceID;
                printGraph(G, sourceID);
                break;
            }

            case 5:
                cout << "Masukkan ID Stasiun untuk melihat stasiun terdekat: ";
                cin >> sourceID;
                dekatStasiun(G, sourceID);
                break;

            case 6:
                cout << "terima kasih sudah menggunakan program ini" <<endl;
                break;

            default:
                cout << "Pilihan tidak valid." << endl;
                break;
        }
    } while (choice != 6);

    return 0;
}
