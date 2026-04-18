#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

struct Buku {
    int id;
    char judul[100];
    char pengarang[100];
    float harga;
    int stok;
    Buku* next;
};

struct Transaksi {
    int id;
    int id_buku;
    char judul_buku[100];
    int jumlah;
    float total;
    Transaksi* next;
};

//ini buat nandain kepala node buku sama node transaksinya, yang nanti bisa di geser2 kalo ada update data
Buku*      headBuku      = NULL;
Transaksi* headTransaksi = NULL;
int jumlahBuku      = 0;
int jumlahTransaksi = 0;

//ini buat nyimpen update an buku kalo abis ada update data
void simpanBuku() {
    FILE* file = fopen("buku.txt", "w");
    if (file == NULL) {
        cout << "Gagal membuka file!" << endl;
        return;
    }
    
    fprintf(file, "%d\n", jumlahBuku);

    Buku* curr = headBuku;
    while (curr != NULL) {
        fprintf(file, "%d\n",   curr->id);
        fprintf(file, "%s\n",   curr->judul);
        fprintf(file, "%s\n",   curr->pengarang);
        fprintf(file, "%.2f\n", curr->harga);
        fprintf(file, "%d\n",   curr->stok);
        curr = curr->next;
    }

    fclose(file);
}

//ini buat nampilin data buku yang ada di filenya
void muatBuku() {
    FILE* file = fopen("buku.txt", "r");
    if (file == NULL) return;

    int n;
    fscanf(file, "%d\n", &n);

    for (int i = 0; i < n; i++) {
        // Buat node baru
        Buku* baru = new Buku();
        baru->next = NULL;

        fscanf(file, "%d\n", &baru->id);
        fgets(baru->judul,     100, file); baru->judul[strcspn(baru->judul, "\n")]         = 0;
        fgets(baru->pengarang, 100, file); baru->pengarang[strcspn(baru->pengarang, "\n")] = 0;
        fscanf(file, "%f\n", &baru->harga);
        fscanf(file, "%d\n", &baru->stok);

        // Sisipin di akhir list
        if (headBuku == NULL) {
            headBuku = baru;
        } else {
            Buku* curr = headBuku;
            while (curr->next != NULL) curr = curr->next;
            curr->next = baru;
        }
        jumlahBuku++;
    }

    fclose(file);
    // ini contoh aja
    //apa tuhh
    // komen apa gitu bebas
}

