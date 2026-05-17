#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

struct Buku {
    int id;
    char judul[100];
    char pengarang[100];
    float harga;
    int stok;
    Buku* prev;
    Buku* next;
};

struct Transaksi {
    int id;
    int id_buku;
    char judul_buku[100];
    int jumlah;
    float total;
    Transaksi* prev;
    Transaksi* next;
};

Buku* headBuku = NULL;
Buku* tailBuku = NULL;

Transaksi* headTransaksi = NULL;
Transaksi* tailTransaksi = NULL;

int jumlahBuku = 0;
int jumlahTransaksi = 0;

void simpanBuku() {
    FILE* f = fopen("buku.txt", "w");
    if (!f) return;

    fprintf(f, "%d\n", jumlahBuku);

    Buku* curr = headBuku;
    while (curr != NULL) {
        fprintf(f, "%d\n",   curr->id);
        fprintf(f, "%s\n",   curr->judul);
        fprintf(f, "%s\n",   curr->pengarang);
        fprintf(f, "%.2f\n", curr->harga);
        fprintf(f, "%d\n",   curr->stok);
        curr = curr->next;
    }
    fclose(f);
}

void muatBuku() {
    FILE* f = fopen("buku.txt", "r");
    if (!f) return;

    int total;
    fscanf(f, "%d\n", &total);

    for (int i = 0; i < total; i++) {
        Buku* b = new Buku();
        b->prev = b->next = NULL;

        fscanf(f, "%d\n",     &b->id);
        fscanf(f, "%[^\n]\n", b->judul);
        fscanf(f, "%[^\n]\n", b->pengarang);
        fscanf(f, "%f\n",     &b->harga);
        fscanf(f, "%d\n",     &b->stok);

        if (headBuku == NULL) {
            headBuku = tailBuku = b;
        } else {
            tailBuku->next = b;
            b->prev = tailBuku;
            tailBuku = b;
        }
    }

    jumlahBuku = total;
    fclose(f);
}

void simpanTransaksi() {
    FILE* f = fopen("transaksi.txt", "w");
    if (!f) return;

    fprintf(f, "%d\n", jumlahTransaksi);

    Transaksi* curr = headTransaksi;
    while (curr != NULL) {
        fprintf(f, "%d\n",   curr->id);
        fprintf(f, "%d\n",   curr->id_buku);
        fprintf(f, "%s\n",   curr->judul_buku);
        fprintf(f, "%d\n",   curr->jumlah);
        fprintf(f, "%.2f\n", curr->total);
        curr = curr->next;
    }
    fclose(f);
}

void muatTransaksi() {
    FILE* f = fopen("transaksi.txt", "r");
    if (!f) return;

    int total;
    fscanf(f, "%d\n", &total);

    for (int i = 0; i < total; i++) {
        Transaksi* t = new Transaksi();
        t->prev = t->next = NULL;

        fscanf(f, "%d\n",     &t->id);
        fscanf(f, "%d\n",     &t->id_buku);
        fscanf(f, "%[^\n]\n", t->judul_buku);
        fscanf(f, "%d\n",     &t->jumlah);
        fscanf(f, "%f\n",     &t->total);

        if (headTransaksi == NULL) {
            headTransaksi = tailTransaksi = t;
        } else {
            tailTransaksi->next = t;
            t->prev = tailTransaksi;
            tailTransaksi = t;
        }
    }

    jumlahTransaksi = total;
    fclose(f);
}

void tambahBuku() {
    Buku* baru = new Buku();
    baru->id = jumlahBuku + 1;
    baru->prev = baru->next = NULL;

    cout << "\n=== TAMBAH BUKU ===\n";
    cout << "Judul     : ";
    cin.ignore();
    cin.getline(baru->judul, 100);

    cout << "Pengarang : ";
    cin.getline(baru->pengarang, 100);

    cout << "Harga     : ";
    cin >> baru->harga;

    cout << "Stok      : ";
    cin >> baru->stok;

    if (headBuku == NULL) {
        headBuku = tailBuku = baru;
    } else {
        tailBuku->next = baru;
        baru->prev = tailBuku;
        tailBuku = baru;
    }

    jumlahBuku++;
    simpanBuku();
    cout << "Buku berhasil ditambahkan!\n";
}

void tampilkanBuku() {
    if (headBuku == NULL) {
        cout << "\n  Belum ada data buku.\n";
        return;
    }

    cout << "\n";
    cout << "+====+================================+======================+============+=======+\n";
    cout << "| ID | Judul                          | Pengarang            | Harga      | Stok  |\n";
    cout << "+====+================================+======================+============+=======+\n";

    Buku* curr = headBuku;
    while (curr != NULL) {
        // %-20s  = teks rata kiri, lebar 20 karakter
        // %10.0f = angka desimal, lebar 10, tanpa koma
        // %5d    = angka bulat, lebar 5
        printf("| %-2d | %-30.30s | %-20.20s | Rp %7.0f | %5d |\n",
            curr->id,
            curr->judul,
            curr->pengarang,
            curr->harga,
            curr->stok);
        cout << "+----+--------------------------------+----------------------+------------+-------+\n";
        curr = curr->next;
    }
}

void updateBuku() {
    int id;
    cout << "\n=== UPDATE BUKU ===\n";
    cout << "Masukkan ID: ";
    cin >> id;

    Buku* curr = headBuku;
    while (curr != NULL && curr->id != id)
        curr = curr->next;

    if (curr == NULL) {
        cout << "Buku tidak ditemukan.\n";
        return;
    }

    cout << "Judul baru     : ";
    cin.ignore();
    cin.getline(curr->judul, 100);

    cout << "Pengarang baru : ";
    cin.getline(curr->pengarang, 100);

    cout << "Harga baru     : ";
    cin >> curr->harga;

    cout << "Stok baru      : ";
    cin >> curr->stok;

    simpanBuku();
    cout << "Buku berhasil diupdate!\n";
}

void hapusBuku() {
    int id;
    cout << "\n=== HAPUS BUKU ===\n";
    cout << "Masukkan ID buku: ";
    cin >> id;

    Buku* curr = headBuku;
    while (curr != NULL && curr->id != id)
        curr = curr->next;

    if (curr == NULL) {
        cout << "Buku tidak ditemukan.\n";
        return;
    }

    // Kasus 1: node pertama (head)
    if (curr == headBuku) {
        headBuku = curr->next;
        if (headBuku != NULL)
            headBuku->prev = NULL;
    }
    // Kasus 2: node terakhir (tail)
    else if (curr == tailBuku) {
        tailBuku = curr->prev;
        tailBuku->next = NULL;
    }
    // Kasus 3: node tengah
    else {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
    }

    delete curr;
    jumlahBuku--;
    simpanBuku();
    cout << "Buku berhasil dihapus!\n";
}

void cariBuku() {
    cout << "\n=== CARI BUKU ===\n";
    cout << "Masukkan judul: ";
    char keyword[100];
    cin.ignore();
    cin.getline(keyword, 100);

    Buku* curr = headBuku;
    bool ketemu = false;

    while (curr != NULL) {
        if (strstr(curr->judul, keyword) != NULL) {
            cout << "\nDitemukan!\n";
            cout << "ID        : " << curr->id;
            cout << "\nJudul     : " << curr->judul;
            cout << "\nPengarang : " << curr->pengarang;
            cout << "\nHarga     : Rp " << curr->harga;
            cout << "\nStok      : " << curr->stok << "\n";
            ketemu = true;
        }
        curr = curr->next;
    }

    if (!ketemu)
        cout << "Buku tidak ditemukan.\n";
}

//SORT BERDASARKAN HARGA (murah ke mahal)
void sortByHarga() {
    bool ada_tukar = true;
    while (ada_tukar) {
        ada_tukar = false;
        Buku* curr = headBuku;

        while (curr->next != NULL) {
            if (curr->harga > curr->next->harga) {
                int   tmp_id    = curr->id;
                float tmp_harga = curr->harga;
                int   tmp_stok  = curr->stok;
                char  tmp_judul[100], tmp_peng[100];
                strcpy(tmp_judul, curr->judul);
                strcpy(tmp_peng,  curr->pengarang);

                curr->id    = curr->next->id;
                curr->harga = curr->next->harga;
                curr->stok  = curr->next->stok;
                strcpy(curr->judul,     curr->next->judul);
                strcpy(curr->pengarang, curr->next->pengarang);

                curr->next->id    = tmp_id;
                curr->next->harga = tmp_harga;
                curr->next->stok  = tmp_stok;
                strcpy(curr->next->judul,     tmp_judul);
                strcpy(curr->next->pengarang, tmp_peng);

                ada_tukar = true;
            }
            curr = curr->next;
        }
    }
}

//SORT BERDASARKAN JUDUL (A - Z)
void sortByJudul() {
    bool ada_tukar = true;
    while (ada_tukar) {
        ada_tukar = false;
        Buku* curr = headBuku;

        while (curr->next != NULL) {
            if (strcmp(curr->judul, curr->next->judul) > 0) {
                int   tmp_id    = curr->id;
                float tmp_harga = curr->harga;
                int   tmp_stok  = curr->stok;
                char  tmp_judul[100], tmp_peng[100];
                strcpy(tmp_judul, curr->judul);
                strcpy(tmp_peng,  curr->pengarang);

                curr->id    = curr->next->id;
                curr->harga = curr->next->harga;
                curr->stok  = curr->next->stok;
                strcpy(curr->judul,     curr->next->judul);
                strcpy(curr->pengarang, curr->next->pengarang);

                curr->next->id    = tmp_id;
                curr->next->harga = tmp_harga;
                curr->next->stok  = tmp_stok;
                strcpy(curr->next->judul,     tmp_judul);
                strcpy(curr->next->pengarang, tmp_peng);

                ada_tukar = true;
            }
            curr = curr->next;
        }
    }
}

void sortBuku() {
    if (headBuku == NULL) {
        cout << "Belum ada buku.\n";
        return;
    }

    cout << "\n=== URUTKAN BUKU ===\n";
    cout << "1. Berdasarkan Harga\n";
    cout << "2. Berdasarkan Judul\n";
    cout << "Pilih: ";
    int p; cin >> p;

    if (p == 1) {
        sortByHarga();
        cout << "Buku diurutkan berdasarkan harga!\n";
        tampilkanBuku();
    } else if (p == 2) {
        sortByJudul();
        cout << "Buku diurutkan berdasarkan judul!\n";
        tampilkanBuku();
    } else {
        cout << "Pilihan tidak valid.\n";
    }
}

void transaksi() {
    tampilkanBuku();

    int id, jumlah;
    cout << "\n=== TRANSAKSI ===\n";
    cout << "ID buku     : ";
    cin >> id;

    Buku* curr = headBuku;
    while (curr != NULL && curr->id != id)
        curr = curr->next;

    if (curr == NULL || curr->stok == 0) {
        cout << "Buku tidak tersedia.\n";
        return;
    }

    cout << "Jumlah beli : ";
    cin >> jumlah;

    if (jumlah > curr->stok) {
        cout << "Stok tidak cukup! Stok: " << curr->stok << "\n";
        return;
    }

    float total = jumlah * curr->harga;

    Transaksi* baru = new Transaksi();
    baru->id = jumlahTransaksi + 1;
    baru->id_buku = curr->id;
    baru->jumlah = jumlah;
    baru->total = total;
    baru->prev = baru->next = NULL;
    strcpy(baru->judul_buku, curr->judul);

    if (headTransaksi == NULL) {
        headTransaksi = tailTransaksi = baru;
    } else {
        tailTransaksi->next = baru;
        baru->prev = tailTransaksi;
        tailTransaksi = baru;
    }

    curr->stok -= jumlah;
    jumlahTransaksi++;

    cout << "\n--- STRUK ---\n";
    cout << "Buku    : " << baru->judul_buku << "\n";
    cout << "Jumlah  : " << baru->jumlah << "\n";
    printf("Total   : Rp %.0f\n", baru->total);
    cout << "Transaksi berhasil!\n";

    simpanBuku();
    simpanTransaksi();
}

void laporan() {
    cout << "\n=== LAPORAN PENJUALAN ===\n";

    if (headTransaksi == NULL) {
        cout << "Belum ada transaksi.\n";
        return;
    }

    Transaksi* curr = headTransaksi;
    float totalPendapatan = 0;

    while (curr != NULL) {
        cout << "\nID Transaksi : " << curr->id;
        cout << "\nBuku         : " << curr->judul_buku;
        cout << "\nJumlah       : " << curr->jumlah;
        printf("\nTotal        : Rp %.0f", curr->total);
        cout << "\n--------------------------\n";
        totalPendapatan += curr->total;
        curr = curr->next;
    }

    printf("\nTOTAL PENDAPATAN: Rp %.0f\n", totalPendapatan);
}

int main() {
    muatBuku();
    muatTransaksi();

    int pilih;
    do {
		cout << "\n";
		cout << "+==============================+\n";
		cout << "|  SISTEM MANAJEMEN TOKO BUKU  |\n";
		cout << "+==============================+\n";
		cout << "|  1. Tambah Buku              |\n";
		cout << "|  2. Tampilkan Buku           |\n";
		cout << "|  3. Update Buku              |\n";
		cout << "|  4. Hapus Buku               |\n";
		cout << "|  5. Cari Buku                |\n";
		cout << "|  6. Urutkan Buku             |\n";
		cout << "|  7. Transaksi                |\n";
		cout << "|  8. Laporan                  |\n";
		cout << "+------------------------------+\n";
		cout << "|  0. Keluar                   |\n";
		cout << "+==============================+\n";
		cout << "  Pilih: ";
        cin >> pilih;

        switch (pilih) {
            case 1: tambahBuku();    break;
            case 2: tampilkanBuku(); break;
            case 3: updateBuku();    break;
            case 4: hapusBuku();     break;
            case 5: cariBuku();      break;
            case 6: sortBuku();      break;
            case 7: transaksi();     break;
            case 8: laporan();       break;
        }

    } while (pilih != 0);

    cout << "Terimakasih telah menggunakan program, Have a Good Day!!\n";
    return 0;
}
