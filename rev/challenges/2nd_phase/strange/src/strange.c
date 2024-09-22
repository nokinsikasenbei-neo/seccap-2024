#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void junk() {
    // junk code
    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    int e = 4;
    int f = 5;
    int g = 6;
    int h = 7;
    int i = 8;
    int j = 9;
    int k = 10;

    int x = a * b * c * d * e * f * g * h * i * j * k;
}

void junk2(unsigned char *flag)
{
    // junk code
    for (int i = 0; i < strlen(flag); i++) {
        flag[i] = flag[i] + 1;
    }

    for (int i = 0; i < strlen(flag); i++) {
        flag[i] = flag[i] - 1;
    }
}

void junk3(char *flag)
{
    // junk code, times and divide by 2
    for (int i = 0; i < strlen(flag); i++) {
        flag[i] = flag[i] ^ 0xA;
    }

    for (int i = 0; i < strlen(flag); i++) {
        flag[i] = flag[i] ^ 0xA;
    }
}

void dec(char *sentence)
{   
    // ceaser for shift -8, including { and }
    for (int i = 0; i < strlen(sentence); i++) {
        sentence[i] = sentence[i] - 8;
    }
}

// generate flag
char *gen_flag() {
    // ['0x4e', '0x54', '0x49', '0x4f', '0x83', '0x3d', '0x3f', '0x3b', '0x7a', '0x3c', '0x76', '0x6f', '0x3b', '0x67', '0x7f', '0x39', '0x3f', '0x70', '0x38', '0x7d', '0x3f', '0x67', '0x3d', '0x81', '0x75', '0x6a', '0x38', '0x74', '0x3d', '0x85']
    junk();
    unsigned char *flag = malloc(sizeof(unsigned char) * 30);
    flag[0] = 0x4e;
    flag[1] = 0x54;
    flag[2] = 0x49;
    flag[3] = 0x4f;
    flag[4] = 0x83;
    flag[5] = 0x3d;
    flag[6] = 0x3f;
    flag[7] = 0x7a;
    flag[8] = 0x3c;
    flag[9] = 0x76;
    flag[10] = 0x6f;
    flag[11] = 0x3b;
    flag[12] = 0x67;
    flag[13] = 0x7f;
    flag[14] = 0x39;
    flag[15] = 0x3f;
    flag[16] = 0x70;
    flag[17] = 0x38;
    flag[18] = 0x7d;
    flag[19] = 0x3f;
    flag[20] = 0x67;
    flag[21] = 0x3d;
    flag[22] = 0x81;    
    flag[23] = 0x75;
    flag[24] = 0x6a;
    flag[25] = 0x38;
    flag[26] = 0x74;
    flag[27] = 0x3d;
    flag[28] = 0x85;
    flag[29] = '\0';
    // printf("%s\n", flag);
    junk2(flag);
    // printf("%s\n", flag);
    dec(flag);
    // printf("%s\n", flag);
    junk3(flag);
    // printf("%s\n", flag);
    return flag;
}

int main(int argc, char **argv) {
    
    if (argc != 2) {
        printf("Usage: %s <password>\n", argv[0]);
        return 1;
    }
    // FLAG{57r4ng3_w17h0u7_5ymb0l5}
    unsigned char *flag;
    flag = gen_flag();
    // printf("%s\n", flag);
    // printf("%d\n", strlen(flag));
    // printf("%d\n", strlen(argv[1]));

    if (argc == 2 && strlen(argv[1]) == strlen(flag) && strncmp(argv[1], flag, strlen(argv[1])) == 0) {
        puts("Correct!");
        printf("It's a flag: %s\n", argv[1]);
        return 0;
    }
    puts("Wrong!");
    return 0;
}