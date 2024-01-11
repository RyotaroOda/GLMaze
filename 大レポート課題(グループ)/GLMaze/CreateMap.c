#include "CreateMap.h"
#include "Header.h"
#include <stdlib.h>
#include <time.h>

#define size 3
cell newMap[size][size];

int WayToGo(int x, int y, int dir) {
    int dir2 = (dir + 1) % 4;
    int count = 0;
    
    while (count < 4) {
        if (dir2 == 0) {
            if (newMap[y - 1][x].southWall == false && !(y == 0)) { return dir2; }
        }
        if (dir2 == 1) {
            if (newMap[y][x].eastWall == false) { return dir2; }
        }
        if (dir2 == 2) {
            if (newMap[y][x].southWall == false) { return dir2; }
        }
        if (dir2 == 3) {
            if (newMap[y][x - 1].eastWall == false && !(x == 0)) { return dir2; }
        }
        if (dir2 > 0)dir2 = (dir2 - 1) % 4;
        else dir2 = (3 + dir2) % 4;
        count++;
    }

    printf("???\n");
    /*printf("(%d,%d)\n", newMap[y][x].eastWall, newMap[y][x].southWall);*/
    return 0;
}

void bestWay(void)
{
    int i, j;
    int x = 0;
    int y = 0;
    int Xgoal = size - 1;
    int Ygoal = size - 1;

    typedef struct
    {
        int EW;
        int SN;
    }directionCount;
    directionCount DC[size][size];
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            DC[i][j].EW = 0;
            DC[i][j].SN = 0;
        }
    }

    directionType playerDirection = south;
    int pd = playerDirection;
    int count = 0;
    while (x < Xgoal || y < Ygoal) {
        if (count > size * size * size)break;
        int d = WayToGo(x, y, pd);
        pd = d;
        if (d == 0) { DC[y-1][x].SN--; y--; }
        if (d == 1) { DC[y][x].EW++; x++; }
        if (d == 2) { DC[y][x].SN++; y++; }
        if (d == 3) { DC[y][x-1].EW--; x--; }
        /*printf("(%d,%d)\n", x, y);*/
        count++;
    }

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            /*printf("(%d,%d)", DC[i][j].EW, DC[i][j].SN);*/
            if ((DC[i][j].EW % 2) == 0 && (DC[i][j].SN % 2) == 0) { newMap[i][j].correctRoute = false; }
            else { /*printf("(%d,%d)", DC[i][j].EW, DC[i][j].SN);*/ newMap[i][j].correctRoute = true; }
        }
    }
}


void createMap(void) {
    //棒倒し法
    srand((unsigned int)time(NULL));

    int binarySize = size * 2 + 1;
    //0が壁、１が通路
    int binaryMap[binarySize][binarySize];

    directionType d = 100;
    int i, j;
    for (i = 0; i < binarySize; i++) {
        for (j = 0; j < binarySize; j++) {
            binaryMap[i][j] = 1;
        }
    }
    for (i = 0; i < binarySize; i++) {
        for (j = 0; j < binarySize; j++) {
            if (i == 0 || j == 0 || i == binarySize - 1 || j == binarySize - 1) binaryMap[i][j] = 0;//outerWall

            else if (i % 2 == 1 && j % 2 == 1) binaryMap[i][j] = 1;
            else if (i % 2 == 0 && j % 2 == 0) {
                binaryMap[i][j] = 0;
                if (i == 2) d = rand() % ((binaryMap[i][j - 1] == 0) ? 3 : 4);//北を含める
                else if (binaryMap[i][j - 1] == 0) d = rand() % 2;//北・西以外
                else d = rand() % 3;//北以外

                switch (d) {
                case 0://東
                    binaryMap[i + 1][j] = 0;
                    break;
                case 1://南
                    binaryMap[i][j + 1] = 0;
                    break;
                case 2://西
                    binaryMap[i][j - 1] = 0;
                    break;
                case 3://北
                    binaryMap[i - 1][j] = 0;
                    break;
                default:
                    printf("d error!\n");
                    break;
                }
            }
        }
    }

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            newMap[i][j].southWall = (binaryMap[i * 2 + 2][j * 2 + 1] == 0) ? true : false;
            newMap[i][j].eastWall = (binaryMap[i * 2 + 1][j * 2 + 2] == 0) ? true : false;
            newMap[i][j].type = normal;
            newMap[i][j].correctRoute = false;
        }
    }
    newMap[0][0].type = start;
    newMap[size - 1][size - 1].type = goal;
    //TODO: trap

    bestWay();

    //ログ
//    printf("BinaryMap\n");
//    for (i = 0; i < binarySize; i++) {
//        for (j = 0; j < binarySize; j++) {
//            printf("%d, ", binaryMap[i][j]);
//        }
//        printf("\n");
//    }
//    printf("NewMap\n");
//    for (i = 0; i < size; i++) {
//        for (j = 0; j < size; j++) {
//            printf("{%d, %d, %d, %d}, ", newMap[i][j].eastWall, newMap[i][j].southWall, newMap[i][j].type, newMap[i][j].correctRoute);
//        }
//        printf("\n");
//    }
    
    for (i = 0; i < MAPSIZE; i++) {
        for (j = 0; j < MAPSIZE; j++) {
            map[i][j] = newMap[i][j];
        }
    }
}
