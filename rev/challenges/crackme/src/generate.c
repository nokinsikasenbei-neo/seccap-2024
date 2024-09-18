#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    const char key[] = "SecCap A 2024";
    size_t len = strlen(argv[1]);
    for (int i = 0; i<len; i++) {
        argv[1][i] ^= key[i % (sizeof(key)-1)];
    }
    
    printf("FLAG: ");
    for (int i = 0; i < len; i++) {
        printf("\\x%02x", (unsigned char)argv[1][i]);
    }
    printf("\n");
}