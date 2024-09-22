#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// enc
char enc[] = {0xa4,0x48,0x71,0x28,0x57,0x76,0x2b,0x82,0x5c,0x42,0xa6,0x40,0x60,0x00};
// FLAG{345y_vm}
// add 0x5e F 005e -> ffffffa4
// sub 0x04 L 0104
// xor 0x30 A 0230
// sub 0x1f G 011f
// sub 0x24 { 0124
// add 0x43 3 0043
// xor 0x1f 4 021f
// add 0x4d 5 004d -> ffffff82
// sub 0x1d y 011d
// xor 0x1d _ 021d
// add 0x30 v 0030 -> ffffffa6
// sub 0x2d m 012d
// xor 0x1d } 021d


int check(const char* input) {
    FILE *file = fopen("bin", "rb");
    if (file == NULL) {
        perror("cannot read 'bin'");
        return -1;
    }

    unsigned char result[256];
    strncpy(result, input, 256);

    int index = 0;
    unsigned char bytes[2];

    if (strlen(input) != strlen(enc))
    {
        printf("Wrong...\n");
        return 1;
    }

    while (1) {
        size_t bytesRead = fread(&bytes, sizeof(unsigned char), 2, file);
        if (bytesRead != 2) {
            if (feof(file)) {
                break;
            } else {
                perror("error : cannot read file correctly");
                return -1;
            }
        }   
        // printf("bytes[0]: %d, bytes[1]: %d\n", bytes[0], bytes[1]);
        if (bytes[0] % 4 == 0) {
            // puts("add");
            result[index] += bytes[1];  // add
        } else if (bytes[0] % 4 == 1) {
            // puts("sub");
            result[index] -= bytes[1];  // sub
        } else if (bytes[0] % 4 == 2) {
            // puts("xor");
            result[index] ^= bytes[1];  // XOR
        }
        else {
            return -1;
        }
        index = (index + 1);
    }

    fclose(file);

    if (strcmp(result, enc) == 0) {
        printf("Correct!\nFLAG: %s\n", input);
        return 0;
    } else {
        printf("Wrong...\n");
        return 1;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <password>\n", argv[0]);
        return 1;
    }

    return check(argv[1]);
}
