#ifndef PESANAN_H
#define PESANAN_H

#include "../utilities/boolean.h"
#include "../point/location.h"

typedef enum JenisItemEnum {NORMAL, HEAVY, PERISHABLE, VIP, UNKNOWN} JenisItem;
#define JENISITEMCOUNT 5

typedef struct {
    Location pickUp;
    Location dropOff;
    int waktuIn;
    int price;
    int timeout; // waktu expired, khusus Perishable
    int timeoutInitial; // waktu expired awal (konstan, tidak dikurang dan dioperasikan), khusus Perishable
    JenisItem jenisItem;
} Pesanan;

#define LokasiPickUp(p) (p).pickUp
#define LokasiDropOff(p) (p).dropOff
#define WaktuIn(p) (p).waktuIn
#define Price(p) (p).price
#define JenisItem(p) (p).jenisItem
#define TimeoutPerish(p) (p).timeout
#define TimeoutPerishInitial(p) (p).timeoutInitial

// Create Pesanan, harga item otomatis disimpulkan dari JenisItem
void CreatePesanan(Pesanan *p, JenisItem jenisItem, Location pickUp, Location dropOff, int waktuIn);
// Create Pesanan, untuk Perishable (dengan timeout)
void CreatePesananPerish(Pesanan *p, JenisItem jenisItem, Location pickUp, Location dropOff, int waktuIn, int timeout);
// Mengubah karakter kode jenis item ke enum JenisItem
JenisItem charToJenisItem(char c);

// Mendapatkan tipe Pesanan dalam string (bukan angka enum)
char* getJenisItemString(Pesanan p);
// Mendapatkan tipe Pesanan dalam char
char getJenisItemChar(Pesanan p);
// Menampilkan Pesanan, ditambah \n baris baru pada akhir. Format: waktuIn pickup dropoff jenisItem harga+Yen [Timout perishable]
void displayPesanan(Pesanan p);

// Apakah pesanan sudah masuk waktu sehingga muncul di To Do
boolean isPesananMasukWaktu(Pesanan p, int waktu);
// Return true jika timout item sudah habis (khusus Perishable)
boolean isPesananExpired(Pesanan p);
// Return true jika p1 sama dengan p2
boolean isPesananEqual(Pesanan p1, Pesanan p2);

#endif
