#include <stdio.h>
#include "pesanan.h"
#include "../location/location.h"

void CreatePesanan(Pesanan *p, JenisItem jenisItem, Location pickUp, Location dropOff, int waktuIn){
    JenisItem(*p) = jenisItem;
    LokasiPickUp(*p) = pickUp;
    LokasiDropOff(*p) = dropOff;
    WaktuIn(*p) = waktuIn;
    TimeoutPerish(*p) = -1;
    TimeoutPerishInitial(*p) = -1;

    int harga;
    switch (jenisItem)
        {
        case NORMAL:
            harga = 200;
            break;
        case HEAVY:
            harga = 400;
            break;
        case PERISHABLE:
            harga = 400;
            break;
        case VIP:
            harga = 600;
            break;
        default:
            harga = 0;
            break;
        }
    Price(*p) = harga;
}

void CreatePesananPerish(Pesanan *p, JenisItem jenisItem, Location pickUp, Location dropOff, int waktuIn, int timeout){
    JenisItem(*p) = jenisItem;
    LokasiPickUp(*p) = pickUp;
    LokasiDropOff(*p) = dropOff;
    WaktuIn(*p) = waktuIn;
    TimeoutPerish(*p) = timeout;
    TimeoutPerishInitial(*p) = timeout;

    int harga;
    switch (jenisItem)
        {
        case NORMAL:
            harga = 200;
            break;
        case HEAVY:
            harga = 400;
            break;
        case PERISHABLE:
            harga = 400;
            break;
        case VIP:
            harga = 600;
            break;
        default:
            harga = 0;
            break;
        }
    Price(*p) = harga;
}

char* getJenisItemString(Pesanan p){
    switch (JenisItem(p))
        {
        case NORMAL:
            return "NORMAL";
            break;
        case HEAVY:
            return "HEAVY";
            break;
        case PERISHABLE:
            return "PERISHABLE";
            break;
        case VIP:
            return "VIP";
            break;
        default:
            return "UNKNOWN";
            break;
        }
}

void displayPesanan(Pesanan p){
    printf("%d %c %c %s %d Yen", WaktuIn(p), NAME(LokasiPickUp(p)), NAME(LokasiDropOff(p)), getJenisItemString(p), Price(p));
    if(JenisItem(p) == PERISHABLE)
        printf(" timeout: %d", TimeoutPerish(p));
    printf("\n");
}

boolean isPesananMasukWaktu(Pesanan p, int waktu){
    return waktu >= WaktuIn(p);
}

boolean isPesananExpired(Pesanan p){
    return TimeoutPerish(p) <= 0;
}

boolean isPesananEqual(Pesanan p1, Pesanan p2) {
    return (ABSIS(POINT(LokasiPickUp(p1))) == ABSIS(POINT(LokasiPickUp(p2))) && ORDINAT(POINT(LokasiPickUp(p1))) == ORDINAT(POINT(LokasiPickUp(p2))) && ABSIS(POINT(LokasiDropOff(p1))) == ABSIS(POINT(LokasiDropOff(p2))) && ORDINAT(POINT(LokasiDropOff(p1))) == ORDINAT(POINT(LokasiDropOff(p2))) && NAME(LokasiPickUp(p1)) == NAME(LokasiPickUp(p2)) && NAME(LokasiDropOff(p1)) == NAME(LokasiDropOff(p2)) && WaktuIn(p1) == WaktuIn(p2) && Price(p1) == Price(p2) && TimeoutPerish(p1) == TimeoutPerish(p2) && TimeoutPerishInitial(p1) == TimeoutPerishInitial(p2) && JenisItem(p1) == JenisItem(p2));
}