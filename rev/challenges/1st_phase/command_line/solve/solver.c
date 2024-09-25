#include <stdio.h>

int main() {
    char flag[30];
    flag[5] = 'c';
    flag[0] = 'F';
    flag[0x18] = 'n';
    flag[2] = 'A';
    flag[0x1b] = '}';
    flag[0x17] = '3';
    flag[4] = '{';
    flag[0xe] = '1';
    flag[0xc] = '_';
    flag[7] = 'm';
    flag[0x1a] = 's';
    flag[1] = 'L';
    flag[0x12] = '4';
    flag[9] = '4';
    flag[0x14] = 'g';
    flag[6] = '0';
    flag[0xf] = 'n';
    flag[0xd] = 'l';
    flag[0xb] = 'd';
    flag[8] = 'm';
    flag[0x11] = '_';
    flag[0x19] = 't';
    flag[10] = 'n';
    flag[3] = 'G';
    flag[0x16] = 'm';
    flag[0x13] = 'r';
    flag[0x15] = 'u';
    flag[0x10] = '3';

    printf("%s\n", flag);

    return 0;
}