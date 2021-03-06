#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "utilities/boolean.h"
#include "utilities/pcolor.h"
#include "mesin/charmachine.h"
#include "mesin/wordmachine.h"
#include "mesin/configmachine.h"
#include "point/location.h"
#include "list_linked/linked_list_to_do.h"
#include "list_linked/linked_list_in_progress.h"
#include "list_biasa/gadgetlist.h"
#include "list_biasa/dynamiclist.h"
#include "matriks/adjmat.h"
#include "matriks/map.h"
#include "tas/stack.h"
#include "pesanan/pesanan.h"
#include "pesanan/queuepesanan.h"
#include "point/location.h"
#include "point/point.h"
#include "mobita/mobita.h"
#include "list_linked/node.h"

int getCmd(int range)
{
    printf("\nEnter Command: ");
    int ret;
    int res = scanf("%d", &ret);
    if(res == 0){
        char inputstr[1024];
        scanf("%1023[^\n]", inputstr);  // Membuang input string yang tidak valid
        printf("Command tidak valid\n");
        return getCmd(range);
    } else if (ret > range || ret < 1)
    {
        printf("Command tidak valid\n");
        return getCmd(range);
    }
    return ret;
}

void printCmd(Mobita *m)
{
    printf("\nWaktu sekarang adalah %d\n", globalTime);
    printf("Lokasi: ");
    displayLoc(LOCATION(*m));
    printf("\n");
    printf("Command List\n");
    printf("1. Move\n");
    printf("2. Pick Up\n");
    printf("3. Drop Off\n");
    printf("4. To Do List\n");
    printf("5. In Progress List\n");
    printf("6. Map\n");
    printf("7. Shop\n");
    printf("8. Inventory\n");
    printf("9. Balance\n");
    printf("10. Return\n");
    printf("11. Help\n");
    printf("12. Save\n");
    printf("13. Exit\n");
}

void UpdatePesanan(Mobita *m)
{
    int cnt = 0;
    int vipcnt = 0;
    while (!isQueueEmpty(daftarPesanan) && HEADQUEUE(daftarPesanan).waktuIn <= globalTime)
    {
        Pesanan k;
        dequeue(&daftarPesanan, &k);
        insertLastToDo(&TODO(*m), k);
        updateLocationColor(m, LokasiPickUp(k));
        cnt++;
        if (JenisItem(k) == VIP)
            vipcnt++;
    }
    if (cnt > 0)
        printf("\n%sAnda mendapatkan %d pesanan baru!", BLUE, cnt);
    if (vipcnt > 0)
        printf("\n%sAda %d pesanan VIP baru", RED, vipcnt);
    printf("%s", DEFAULT);
}

boolean notDone(Mobita m)
{
    return !(isQueueEmpty(daftarPesanan) && isToDoEmpty(TODO(m)) && isInProgressEmpty(INPROGRESS(m)));
}

int main()
{
    Mobita m;
    CreateMobita(&m);
    printf("Selamat datang di permainan Mobilita!\n");
    printf("1. New Game\n");
    printf("2. Load Game\n");
    printf("3. Exit\n");
    int cmd = getCmd(3);
    switch (cmd)
    {
    case 1:
        CommandNewGame(&m);
        break;
    case 2:
        if (!CommandLoad(&m))
        {
            printf("GAME ERROR\n");
            return 0;
        }
        break;
    case 3:
        return 0;
    }
    while (cmd != 13 && notDone(m))
    {
        UpdatePesanan(&m);
        printCmd(&m);
        cmd = getCmd(13);
        switch (cmd)
        {
        case 1:
            CommandMove(&m);
            break;
        case 2:
            CommandPickup(&m);
            break;
        case 3:
            CommandDropoff(&m);
            break;
        case 4:
            CommandToDo(&m);
            break;
        case 5:
            CommandInProgress(&m);
            break;
        case 6:
            CommandMap(&m);
            break;
        case 7:
            CommandBuy(&m);
            break;
        case 8:
            CommandInventory(&m);
            break;
        case 9:
            CommandBalance(&m);
            break;
        case 10:
            CommandReturn(&m);
            break;
        case 11:
            CommandHelp();
            break;
        case 12:
            CommandSave(&m);
            break;
        default:
            break;
        }
    }
    if (notDone(m))
        printf("Thank You For Playing\n");
    else
    {
        // end screen
        printf("Selamat, anda telah menyelesaikan permainan!\n");
        printf("Orders delivered: %d \n", delivered);
        printf("Time spent: %d \n", globalTime);
    }
    return 0;
}
