#ifndef PESANAN_H
#define PESANAN_H

#include "../boolean.h"
#include "../location/location.h"

typedef enum JenisItemEnum {NORMAL, HEAVY, PERISHABLE, VIP, UNKNOWN} JenisItem;

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
#define TimeoutPerishInitial(p) (p).timeout

// Create Pesanan, harga item otomatis disimpulkan dari JenisItem
void CreatePesanan(Pesanan *p, JenisItem jenisItem, Location pickUp, Location dropOff, int waktuIn);
// Create Pesanan, untuk Perishable (dengan timeout)
void CreatePesananPerish(Pesanan *p, JenisItem jenisItem, Location pickUp, Location dropOff, int waktuIn, int timeout);
// Mendapatkan tipe Pesanan dalam string (bukan angka enum)
char* getJenisItemString(Pesanan p);
// Menampilkan pesanan
void displayPesanan(Pesanan p);

// Apakah pesanan sudah masuk waktu sehingga muncul di To Do
boolean isPesananMasukWaktu(Pesanan p, int waktu);
// Return true jika timout item sudah habis (khusus Perishable)
boolean isPesananExpired(Pesanan p);

#endif