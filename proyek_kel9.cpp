#include <iostream>
#include <cstring>
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

// =============================================
// TAMBAH BUKU
// =============================================
void tambahBuku() {
    Buku* baru = new Buku();
    baru->id = jumlahBuku + 1;
    baru->next = NULL;
    baru->prev = NULL;

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
    cout << "Buku berhasil ditambahkan!\n";
}

// =============================================
// TAMPILKAN BUKU
// =============================================
void tampilkanBuku() {
    if (headBuku == NULL) {
        cout << "Belum ada buku.\n";
        return;
    }

    Buku* curr = headBuku;
    while (curr != NULL) {
        cout << "\nID        : " << curr->id;
        cout << "\nJudul     : " << curr->judul;
        cout << "\nPengarang : " << curr->pengarang;
        cout << "\nHarga     : " << curr->harga;
        cout << "\nStok      : " << curr->stok << endl;
        curr = curr->next;
    }
}

// =============================================
// HAPUS BUKU
// =============================================
void hapusBuku() {
    int id;
    cout << "Masukkan ID buku: ";
    cin >> id;

    Buku* curr = headBuku;

    while (curr != NULL && curr->id != id) {
        curr = curr->next;
    }

    if (curr == NULL) {
        cout << "Tidak ditemukan\n";
        return;
    }

    // kasus 1: node pertama
    if (curr == headBuku) {
        headBuku = curr->next;
        if (headBuku != NULL)
            headBuku->prev = NULL;
    }
    // kasus 2: node terakhir
    else if (curr == tailBuku) {
        tailBuku = curr->prev;
        tailBuku->next = NULL;
    }
    // kasus 3: tengah
    else {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
    }

    delete curr;
    jumlahBuku--;
    cout << "Buku berhasil dihapus\n";
}

// =============================================
// UPDATE BUKU
// =============================================
void updateBuku() {
    int id;
    cout << "Masukkan ID: ";
    cin >> id;

    Buku* curr = headBuku;

    while (curr != NULL && curr->id != id) {
        curr = curr->next;
    }

    if (curr == NULL) {
        cout << "Tidak ditemukan\n";
        return;
    }

    cout << "Judul baru: ";
    cin.ignore();
    cin.getline(curr->judul, 100);

    cout << "Pengarang baru: ";
    cin.getline(curr->pengarang, 100);

    cout << "Harga baru: ";
    cin >> curr->harga;

    cout << "Stok baru: ";
    cin >> curr->stok;

    cout << "Berhasil diupdate\n";
}

// =============================================
// TRANSAKSI
// =============================================
void transaksi() {
    tampilkanBuku();

    int id, jumlah;
    cout << "ID buku: ";
    cin >> id;

    Buku* curr = headBuku;
    while (curr != NULL && curr->id != id) {
        curr = curr->next;
    }

    if (curr == NULL || curr->stok == 0) {
        cout << "Buku tidak tersedia\n";
        return;
    }

    cout << "Jumlah beli: ";
    cin >> jumlah;

    if (jumlah > curr->stok) {
        cout << "Stok tidak cukup\n";
        return;
    }

    float total = jumlah * curr->harga;

    Transaksi* baru = new Transaksi();
    baru->id = jumlahTransaksi + 1;
    baru->id_buku = curr->id;
    strcpy(baru->judul_buku, curr->judul);
    baru->jumlah = jumlah;
    baru->total = total;
    baru->next = NULL;
    baru->prev = NULL;

    if (headTransaksi == NULL) {
        headTransaksi = tailTransaksi = baru;
    } else {
        tailTransaksi->next = baru;
        baru->prev = tailTransaksi;
        tailTransaksi = baru;
    }

    curr->stok -= jumlah;
    jumlahTransaksi++;

    cout << "Transaksi berhasil!\n";
}

// =============================================
// LAPORAN
// =============================================
void laporan() {
    Transaksi* curr = headTransaksi;
    float total = 0;

    while (curr != NULL) {
        cout << "\nID: " << curr->id;
        cout << "\nBuku: " << curr->judul_buku;
        cout << "\nJumlah: " << curr->jumlah;
        cout << "\nTotal: " << curr->total << endl;

        total += curr->total;
        curr = curr->next;
    }

    cout << "\nTotal Pendapatan: " << total << endl;
}

// =============================================
// MAIN MENU
// =============================================
int main() {
    int pilih;

    do {
        cout << "\n=== TOKO BUKU (DLL) ===\n";
        cout << "1. Tambah Buku\n";
        cout << "2. Tampilkan Buku\n";
        cout << "3. Update Buku\n";
        cout << "4. Hapus Buku\n";
        cout << "5. Transaksi\n";
        cout << "6. Laporan\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih) {
            case 1: tambahBuku(); break;
            case 2: tampilkanBuku(); break;
            case 3: updateBuku(); break;
            case 4: hapusBuku(); break;
            case 5: transaksi(); break;
            case 6: laporan(); break;
        }

    } while (pilih != 0);

    return 0;
}