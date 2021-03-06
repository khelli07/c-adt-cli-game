#include <stdio.h>
#include "pesanan.h"
#include "../point/location.h"

int main(){
    int xpick, ypick, xdrop, ydrop;
    char cpick, cdrop;
    Location pick, drop;
    scanf("%d %d %d %d", &xpick, &ypick, &xdrop, &ydrop);
    scanf(" %c %c", &cpick, &cdrop);
    CreateLocation(&pick, xpick, ypick, cpick);
    CreateLocation(&drop, xdrop, ydrop, cdrop);

    int waktuIn;
    scanf(" %d", &waktuIn);

    char jenis;
    JenisItem jenisItem;
    scanf(" %c", &jenis);
    switch (jenis)
    {
    case 'N':
        jenisItem = NORMAL;
        break;
    case 'H':
        jenisItem = HEAVY;
        break;
    case 'P':
        jenisItem = PERISHABLE;
        break;
    case 'V':
        jenisItem = VIP;
        break;
    default:
        jenisItem = UNKNOWN;
        break;
    }
    Pesanan p;
    if(jenisItem == PERISHABLE){
        int timeout;
        scanf(" %d", &timeout);
        CreatePesananPerish(&p, jenisItem, pick, drop, waktuIn, timeout);
    } else{
        CreatePesanan(&p, jenisItem, pick, drop, waktuIn);
    }
    displayPesanan(p);
}