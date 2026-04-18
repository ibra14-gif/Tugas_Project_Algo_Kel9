#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

// =============================================
// STRUKTUR NODE LINKED LIST
// =============================================
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

// =============================================
// HEAD LINKED LIST & COUNTER
// =============================================
Buku*      headBuku      = NULL;
Transaksi* headTransaksi = NULL;
int jumlahBuku      = 0;
int jumlahTransaksi = 0;

// =============================================
// FUNGSI SIMPAN & MUAT FILE
// =============================================
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

        // Sisipkan di akhir list
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
}

void simpanTransaksi() {
    FILE* file = fopen("transaksi.txt", "w");
    if (file == NULL) return;

    fprintf(file, "%d\n", jumlahTransaksi);

    Transaksi* curr = headTransaksi;
    while (curr != NULL) {
        fprintf(file, "%d\n",   curr->id);
        fprintf(file, "%d\n",   curr->id_buku);
        fprintf(file, "%s\n",   curr->judul_buku);
        fprintf(file, "%d\n",   curr->jumlah);
        fprintf(file, "%.2f\n", curr->total);
        curr = curr->next;
    }

    fclose(file);
}

void muatTransaksi() {
    FILE* file = fopen("transaksi.txt", "r");
    if (file == NULL) return;

    int n;
    fscanf(file, "%d\n", &n);

    for (int i = 0; i < n; i++) {
        Transaksi* baru = new Transaksi();
        baru->next = NULL;

        fscanf(file, "%d\n", &baru->id);
        fscanf(file, "%d\n", &baru->id_buku);
        fgets(baru->judul_buku, 100, file); baru->judul_buku[strcspn(baru->judul_buku, "\n")] = 0;
        fscanf(file, "%d\n", &baru->jumlah);
        fscanf(file, "%f\n", &baru->total);

        if (headTransaksi == NULL) {
            headTransaksi = baru;
        } else {
            Transaksi* curr = headTransaksi;
            while (curr->next != NULL) curr = curr->next;
            curr->next = baru;
        }
        jumlahTransaksi++;
    }

    fclose(file);
}

// =============================================
// 1. TAMBAH BUKU
// =============================================
void tambahBuku() {
    cout << "\n=== TAMBAH BUKU ===" << endl;

    // Buat node baru
    Buku* baru = new Buku();
    baru->next = NULL;
    baru->id   = jumlahBuku + 1;

    cout << "ID Buku (otomatis) : " << baru->id << endl;

    cout << "Judul              : ";
    cin.ignore();
    cin.getline(baru->judul, 100);

    cout << "Pengarang          : ";
    cin.getline(baru->pengarang, 100);

    cout << "Harga              : ";
    cin >> baru->harga;

    cout << "Stok               : ";
    cin >> baru->stok;

    // Sisipkan di akhir list
    if (headBuku == NULL) {
        headBuku = baru;
    } else {
        Buku* curr = headBuku;
        while (curr->next != NULL) curr = curr->next;
        curr->next = baru;
    }

    jumlahBuku++;
    simpanBuku();

    cout << "Buku berhasil ditambahkan!" << endl;
}

// =============================================
// 2. TAMPILKAN BUKU
// =============================================
void tampilkanBuku() {
    cout << "\n=== DAFTAR BUKU ===" << endl;

    if (headBuku == NULL) {
        cout << "Belum ada buku." << endl;
        return;
    }

    Buku* curr = headBuku;
    while (curr != NULL) {
        cout << "-------------------" << endl;
        cout << "ID        : " << curr->id        << endl;
        cout << "Judul     : " << curr->judul      << endl;
        cout << "Pengarang : " << curr->pengarang  << endl;
        cout << "Harga     : Rp " << curr->harga   << endl;
        cout << "Stok      : " << curr->stok       << endl;
        curr = curr->next;
    }
    cout << "-------------------" << endl;
}

// =============================================
// 3. CARI BUKU
// =============================================
void cariBuku() {
    cout << "\n=== CARI BUKU ===" << endl;
    cout << "Masukkan judul yang dicari : ";
    cin.ignore();
    char kata[100];
    cin.getline(kata, 100);

    bool ketemu = false;
    Buku* curr  = headBuku;

    while (curr != NULL) {
        if (strstr(curr->judul, kata) != NULL) {
            cout << "-------------------" << endl;
            cout << "ID        : " << curr->id        << endl;
            cout << "Judul     : " << curr->judul      << endl;
            cout << "Pengarang : " << curr->pengarang  << endl;
            cout << "Harga     : Rp " << curr->harga   << endl;
            cout << "Stok      : " << curr->stok       << endl;
            ketemu = true;
        }
        curr = curr->next;
    }

    if (!ketemu) cout << "Buku tidak ditemukan." << endl;
}

// =============================================
// 4. UPDATE BUKU
// =============================================
void updateBuku() {
    cout << "\n=== UPDATE BUKU ===" << endl;
    cout << "Masukkan ID buku yang ingin diupdate : ";
    int id;
    cin >> id;

    // Cari buku dengan ID tersebut
    Buku* curr = headBuku;
    while (curr != NULL) {
        if (curr->id == id) break;
        curr = curr->next;
    }

    if (curr == NULL) {
        cout << "Buku dengan ID " << id << " tidak ditemukan." << endl;
        return;
    }

    cout << "Buku ditemukan: " << curr->judul << endl;
    cout << "Masukkan data baru:" << endl;

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
    cout << "Buku berhasil diupdate!" << endl;
}

// =============================================
// 5. HAPUS BUKU
// =============================================
void hapusBuku() {
    cout << "\n=== HAPUS BUKU ===" << endl;
    cout << "Masukkan ID buku yang ingin dihapus : ";
    int id;
    cin >> id;

    if (headBuku == NULL) {
        cout << "Belum ada buku." << endl;
        return;
    }

    Buku* curr = headBuku;
    Buku* prev = NULL;

    // Cari node dengan ID tersebut, sambil simpan node sebelumnya
    while (curr != NULL) {
        if (curr->id == id) break;
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        cout << "Buku dengan ID " << id << " tidak ditemukan." << endl;
        return;
    }

    cout << "Yakin hapus buku \"" << curr->judul << "\"? (y/n) : ";
    char konfirmasi;
    cin >> konfirmasi;

    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        if (prev == NULL) {
            // Hapus node pertama
            headBuku = curr->next;
        } else {
            // Sambungkan prev langsung ke node sesudah curr
            prev->next = curr->next;
        }
        delete curr;
        jumlahBuku--;
        simpanBuku();
        cout << "Buku berhasil dihapus!" << endl;
    } else {
        cout << "Penghapusan dibatalkan." << endl;
    }
}

// =============================================
// 6. TRANSAKSI
// =============================================
void transaksi() {
    cout << "\n=== TRANSAKSI ===" << endl;

    if (headBuku == NULL) {
        cout << "Belum ada buku yang tersedia." << endl;
        return;
    }

    // Tampilkan buku yang stoknya ada
    cout << "Buku yang tersedia:" << endl;
    Buku* curr = headBuku;
    while (curr != NULL) {
        if (curr->stok > 0) {
            cout << "[" << curr->id << "] "
                 << curr->judul
                 << " - Rp " << curr->harga
                 << " (stok: " << curr->stok << ")" << endl;
        }
        curr = curr->next;
    }

    cout << "Masukkan ID buku : ";
    int id;
    cin >> id;

    // Cari buku yang dipilih
    Buku* pilihan = headBuku;
    while (pilihan != NULL) {
        if (pilihan->id == id) break;
        pilihan = pilihan->next;
    }

    if (pilihan == NULL) {
        cout << "Buku tidak ditemukan." << endl;
        return;
    }

    if (pilihan->stok == 0) {
        cout << "Stok buku ini habis!" << endl;
        return;
    }

    cout << "Jumlah beli (stok tersedia: " << pilihan->stok << ") : ";
    int jumlah;
    cin >> jumlah;

    if (jumlah <= 0 || jumlah > pilihan->stok) {
        cout << "Jumlah tidak valid!" << endl;
        return;
    }

    float total = pilihan->harga * jumlah;

    cout << "\n--- Struk Pembelian ---"     << endl;
    cout << "Buku    : " << pilihan->judul  << endl;
    cout << "Jumlah  : " << jumlah          << endl;
    cout << "Total   : Rp " << total        << endl;
    cout << "Konfirmasi beli? (y/n) : ";
    char konfirmasi;
    cin >> konfirmasi;

    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        // Kurangi stok
        pilihan->stok -= jumlah;
        simpanBuku();

        // Buat node transaksi baru
        Transaksi* baru = new Transaksi();
        baru->next    = NULL;
        baru->id      = jumlahTransaksi + 1;
        baru->id_buku = pilihan->id;
        baru->jumlah  = jumlah;
        baru->total   = total;
        strcpy(baru->judul_buku, pilihan->judul);

        // Sisipkan di akhir list transaksi
        if (headTransaksi == NULL) {
            headTransaksi = baru;
        } else {
            Transaksi* curr = headTransaksi;
            while (curr->next != NULL) curr = curr->next;
            curr->next = baru;
        }

        jumlahTransaksi++;
        simpanTransaksi();

        cout << "Transaksi berhasil! Terima kasih." << endl;
    } else {
        cout << "Transaksi dibatalkan." << endl;
    }
}

// =============================================
// 7. LAPORAN
// =============================================
void laporan() {
    cout << "\n=== LAPORAN TRANSAKSI ===" << endl;

    if (headTransaksi == NULL) {
        cout << "Belum ada transaksi." << endl;
        return;
    }

    float totalPendapatan = 0;
    Transaksi* curr = headTransaksi;

    while (curr != NULL) {
        cout << "-------------------"                  << endl;
        cout << "ID Transaksi : " << curr->id          << endl;
        cout << "Buku         : " << curr->judul_buku  << endl;
        cout << "Jumlah       : " << curr->jumlah      << endl;
        cout << "Total        : Rp " << curr->total    << endl;
        totalPendapatan += curr->total;
        curr = curr->next;
    }

    cout << "-------------------" << endl;
    cout << "Total Pendapatan : Rp " << totalPendapatan << endl;
}

// =============================================
// MAIN - MENU UTAMA
// =============================================
int main() {
    muatBuku();
    muatTransaksi();

    int pilihan;
    do {
        cout << "\n=== SISTEM TOKO BUKU ===" << endl;
        cout << "1. Tambah Buku"             << endl;
        cout << "2. Tampilkan Buku"          << endl;
        cout << "3. Cari Buku"               << endl;
        cout << "4. Update Buku"             << endl;
        cout << "5. Hapus Buku"              << endl;
        cout << "6. Transaksi"               << endl;
        cout << "7. Laporan"                 << endl;
        cout << "0. Keluar"                  << endl;
        cout << "Pilihan : ";
        cin >> pilihan;

        if      (pilihan == 1) tambahBuku();
        else if (pilihan == 2) tampilkanBuku();
        else if (pilihan == 3) cariBuku();
        else if (pilihan == 4) updateBuku();
        else if (pilihan == 5) hapusBuku();
        else if (pilihan == 6) transaksi();
        else if (pilihan == 7) laporan();
        else if (pilihan == 0) cout << "Sampai jumpa!" << endl;
        else cout << "Pilihan tidak valid!" << endl;

    } while (pilihan != 0);

    return 0;
}
