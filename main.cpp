#include "graph.h"
#include <iostream>

using namespace std;

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
    addVertex(G, "H", "Stasiun Palmerah");
    addVertex(G, "I", "Stasiun Gelora");
    addVertex(G, "J", "Stasiun Senayan");
    addVertex(G, "K", "Stasiun Dukuh Atas");
    addVertex(G, "L", "Stasiun Kuningan Sentral");
    addVertex(G, "M", "Stasiun Soemantri");
    addVertex(G, "N", "Stasiun Kuningan");
    addVertex(G, "O", "Stasiun Pancoran");
    addVertex(G, "P", "Stasiun Tebet BKPM");
    addVertex(G, "Q", "Stasiun Cikoko");
    addVertex(G, "R", "Stasiun Cawang 1 (Transit)");
    addVertex(G, "S", "Stasiun Cawang 2 (Transit)");
    addVertex(G, "T", "Stasiun Halim");
    addVertex(G, "U", "Stasiun Jati Bening");
    addVertex(G, "V", "Stasiun Bekasi Barat");
    addVertex(G, "W", "Stasiun Bekasi Timur");
    addVertex(G, "X", "Stasiun Taman Mini");
    addVertex(G, "Y", "Stasiun Kampung Rambutan");
    addVertex(G, "Z", "Stasiun Ciracas");
    addVertex(G, "A1", "Stasiun Cibubur");
    addVertex(G, "A2", "Stasiun Cibinong");
    addVertex(G, "A3", "Stasiun Sentul Circuit");
    addVertex(G, "A4", "Stasiun Sentul City");
    addVertex(G, "A5", "Stasiun Bogor Baranangsiang");


    addEdge(G, "A", "B", 10, "Rute 1"); //Soekarno Hatta - Dadap
    addEdge(G, "B", "C", 15, "Rute 1"); //Dadap - Kamal Raya
    addEdge(G, "C", "D", 20, "Rute 1"); //Kamal Raya - Rawa Buaya
    addEdge(G, "D", "E", 10, "Rute 1"); //Rawa Buaya - Pesing
    addEdge(G, "E", "F", 25, "Rute 1"); //Pesing - Grogol

    addEdge(G, "F", "G", 30, "Rute 2"); // Grogol - Tomang
    addEdge(G, "G", "H", 30, "Rute 2 (Transit)"); //Tomang Palmerah

    addEdge(G, "H", "I", 5, "Rute 3"); //Palmerah - Gelora
    addEdge(G, "I", "J", 5, "Rute 3"); //Gelora - Senayan
    addEdge(G, "H", "K", 7, "Rute 3"); //Palmerah - Dukuh Atas

    addEdge(G, "K", "L", 8, "Rute 4"); //Dukuh Atas - Kuningan Sentral
    addEdge(G, "L", "M", 5, "Rute 4"); //Kuningan Sentral - Soemantri
    addEdge(G, "M", "N", 5, "Rute 4"); //Soemantri - Kuningan
    addEdge(G, "N", "O", 4, "Rute 4"); //Kuningan - Pancoran
    addEdge(G, "O", "P", 4, "Rute 4"); //Pancoran - Tebet BKPM
    addEdge(G, "P", "Q", 4, "Rute 4"); //Tebet BKPM - Cikoko
    addEdge(G, "Q", "R", 5, "Rute 4"); //Cikoko - Cawang 1
    addEdge(G, "R", "X", 5, "Rute 4"); //Cawang 1 - Taman Mini
    addEdge(G, "X", "Y", 5, "Rute 4"); //Taman mini - Kampung Rambutan
    addEdge(G, "Y", "Z", 5, "Rute 4"); //Kampung Rambutan - Ciracas
    addEdge(G, "Z", "A1", 5, "Rute 4"); //Ciracas - Cibubur

    addEdge(G, "A1", "A2", 6, "Rute 5"); //Cibubur -Cibinong
    addEdge(G, "A2", "A3", 4, "Rute 5"); //Cibinong - Sentul Circuit
    addEdge(G, "A3", "A4", 4, "Rute 5"); //Sentul Circuit - Sentul City
    addEdge(G, "A4", "A5", 4, "Rute 5"); //Sentul city - Bogor Baranangsiang

    addEdge(G, "R", "S", 8, "Rute 6"); //Cawang 1 - Cawang 2
    addEdge(G, "S", "T", 8, "Rute 6"); //Cawang 2 - Halim
    addEdge(G, "T", "U", 8, "Rute 6"); //Halim - Jati Bening
    addEdge(G, "U", "V", 8, "Rute 6"); //Jati Bening - Bekasi Barat
    addEdge(G, "V", "W", 8, "Rute 6"); //Bekasi Barat - Bekasi Timur


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
            
            case 6: {
                cout << "Masukkan ID Stasiun Awal: ";
                cin >> sourceID;
                cout << "Masukkan ID Stasiun Tujuan: ";
                cin >> destID;

                string visited[100]; // Array statis untuk menyimpan rute (maksimal 100 stasiun)
                int visitedCount = 0; // Jumlah stasiun dalam rute

                findRoute(G, sourceID, destID, visited, visitedCount, 0);

                // Tidak ada break atau exit, sehingga program kembali ke menu
                break;
            }          

            case 7: 
                cout << "terima kasih sudah menggunakan program ini" <<endl;
                break;

            default:
                cout << "Pilihan tidak valid." << endl;
                break;
        }
    } while (choice != 7);

    return 0;
}
