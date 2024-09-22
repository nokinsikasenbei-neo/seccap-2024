#include <stdio.h>
#include <string.h>

// initialize array with 0 times 29
char flag[29];

int main(int argc, char *argv[]) {
    flag[5]  = 0x63;  // 'c'
    flag[0]  = 0x46;  // 'F'
    flag[24] = 0x6e;  // 'n'
    flag[2]  = 0x41;  // 'A'
    flag[27] = 0x7d;  // '}'
    flag[23] = 0x33;  // '3'
    flag[4]  = 0x7b;  // '{'
    flag[14] = 0x31;  // '1'
    flag[12] = 0x5f;  // '_'
    flag[7]  = 0x6d;  // 'm'
    flag[26] = 0x73;  // 's'
    flag[1]  = 0x4c;  // 'L'
    flag[18] = 0x34;  // '4'
    flag[9]  = 0x34;  // '4'
    flag[20] = 0x67;  // 'g'
    flag[6]  = 0x30;  // '0'
    flag[15] = 0x6e;  // 'n'
    flag[13] = 0x6c;  // 'l'
    flag[11] = 0x64;  // 'd'
    flag[8]  = 0x6d;  // 'm'
    flag[17] = 0x5f;  // '_'
    flag[25] = 0x74;  // 't'
    flag[10] = 0x6e;  // 'n'
    flag[3]  = 0x47;  // 'G'
    flag[22] = 0x6d;  // 'm'
    flag[19] = 0x72;  // 'r'
    flag[21] = 0x75;  // 'u'
    flag[16] = 0x33;  // '3'

    if (argc > 1) {
        if (strcmp(flag, argv[1]) == 0) {
            puts("Correct!");
            puts(flag);
        }
        else {
            puts("Wrong...");
        }
    }

    return 0;
}
