#include <stdio.h>
#include "../mesin/configmachine.h"
#include "../mesin/charmachine.h"
#include "../list_biasa/dynamiclist.h"
#include "../matriks/adjmat.h"
#include "../matriks/map.h"
#include "../pesanan/pesanan.h"
#include "../pesanan/queuepesanan.h"

// basically command newgame
int main()
{
    /* KAMUS LOKAL */
    int mrow, mcol, px, py, N;
    int timeIn, timeoutPerish;
    char pickUpCC, dropOffCC;
    // ADT BUATAN
    JenisItem itemType;
    Location HQ, pickUpLoc, dropOffLoc;
    Pesanan currentPesanan;
    QueuePesanan qPesanan;
    DynamicList locList;
    AdjMatrix adjMat;
    Map map;

    /* ALGORITMA */
    // HARUS 1 FOLDER DENGAN CONFIG.TXT
    start("config.txt");

    // BACA MAP
    mrow = readInt();
    mcol = readInt();
    CreateMap(&map, mrow, mcol);

    // BACA HEADQUARTER
    px = readInt();
    py = readInt();
    CreateLocation(&HQ, px, py, '8');
    setBuilding(&map, HQ);

    startReadLoc();
    CreateDynamicList(&locList, readLocCounter);
    insertLoc(&locList, HQ);
    while (!endReadLoc)
    {
        // displayLoc(currentLoc);
        insertLoc(&locList, currentLoc);
        setBuilding(&map, currentLoc);
        advReadLoc();
    }

    // DISPLAY SEMUA BANGUNAN
    printf("\nBanyaknya bangunan: %d\n", countBuilding(locList));
    displayLocList(locList);
    printf("\n");

    // DISPLAY INITIAL MAP
    printf("\n=== MAP AWAL MOBITA ===\n");
    displayMap(map);
    printf("\n=== INPUT ADJ MATRIX ===\n");

    // READ ADJ MATRIX
    N = countBuilding(locList);
    CreateAdjMatrix(&adjMat, N);
    readAdjMatrix(&adjMat, N);

    printf("\n=== ADJ MATRIKS YANG DIMASUKKAN ===\n");
    displayAdjMatrix(adjMat);

    printf("\n=== DISPLAY ACCESSIBLE LOC DARI HQ ===\n");
    Location locHQ;
    CreateLocation(&locHQ, 1, 1, '8');
    displayAccLoc(adjMat, locList, locHQ);

    // printf("\n=====\n");
    // setLocationColor(&map, &locList, locHQ, R);
    // displayMap(map);

    CreateQueue(&qPesanan);
    ignoreWhiteSpace();
    N = readInt();
    while (N != 0)
    {
        ignoreWhiteSpace();
        timeIn = readInt();
        ignoreWhiteSpace();
        pickUpCC = currentChar;
        adv();
        ignoreWhiteSpace();
        dropOffCC = currentChar;
        adv();
        ignoreWhiteSpace();
        itemType = charToJenisItem(currentChar);
        adv();

        pickUpLoc = getLoc(locList, pickUpCC);
        dropOffLoc = getLoc(locList, dropOffCC);
        if (itemType == PERISHABLE)
        {
            timeoutPerish = readInt();
            CreatePesananPerish(&currentPesanan, itemType, pickUpLoc, dropOffLoc, timeIn, timeoutPerish);
            N -= 1;
            enqueue(&qPesanan, currentPesanan);
        }
        else
        {
            CreatePesanan(&currentPesanan, itemType, pickUpLoc, dropOffLoc, timeIn);
            N -= 1;
            enqueue(&qPesanan, currentPesanan);
        }
    }

    printf("\n=== DISPLAY PESANAN ===\n");
    sortQueue(&qPesanan);
    displayQueue(qPesanan);

    dealocate(&locList);
    end();
    return 0;
}