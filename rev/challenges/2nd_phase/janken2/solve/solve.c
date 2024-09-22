#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    // シードを計算してみる
    // 一回でもパーを出した場合
    int seed = 99999;
    int player_hands[5] = {1,1,1,1,2};
    for (int i = 0; i<256; i++){
        seed = seed * player_hands[i % 5];
    }
    // seed = 0
    printf("If you play Pa even once, seed is %d\n", seed);

    // 一回でもグーを出した場合、シードは0
    // つまり、シードの取りうる値は、0か99999(全部の手がチョキのとき)
    
    // seedが99999の場合の相手の手を計算してみる
    srand(99999);
    printf("if seed is 99999\n");
    for (int round=0; round<5; round++){
        int npc = rand() % 3;
        switch (npc) {
            case 0:
                printf("Round %d: Gu\n", round);
                break;
            case 1:
                printf("Round %d: Choki\n", round);
                break;
            case 2:
                printf("Round %d: Pa\n", round);
                break;
            default:
                break;
        }
    }

    // Round 0: Pa
    // Round 1: Choki
    // Round 2: Choki
    // Round 3: Choki
    // Round 4: Gu
    // となるので、全部の手がチョキでは勝てない。
    // つまり、seedが0の場合の相手に勝てばいい。
    srand(0);
    printf("if seed is 0\n");
    for (int round=0; round<5; round++){
        int npc = rand() % 3;
        switch (npc) {
            case 0:
                printf("Round %d: Gu\n", round);
                break;
            case 1:
                printf("Round %d: Choki\n", round);
                break;
            case 2:
                printf("Round %d: Pa\n", round);
                break;
            default:
                break;
        }
    }
    // Round 0: Choki
    // Round 1: Choki
    // Round 2: Gu
    // Round 3: Choki
    // Round 4: Pa
    // となるので、グー、グー、パー、グー、チョキーを出せば勝てる



}