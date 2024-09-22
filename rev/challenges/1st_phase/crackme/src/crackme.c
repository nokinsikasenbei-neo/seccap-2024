#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <password>\n", argv[0]);
    return 1;
  }

  // flag : FLAG{You_have_learned_xor_decryption}
  const char enc[] = "\x15\x29\x22\x04\x1a\x29\x4f\x34\x7f\x5a\x51\x44\x51\x0c\x09\x06\x22\x13\x1e\x45\x25\x7f\x4a\x5f\x40\x6b\x37\x00\x00\x31\x18\x00\x54\x28\x4f\x5c\x4d";
  const char key[] = "SecCap A 2024";
  size_t len = strlen(argv[1]);
  for (int i = 0; i < len; i++) {
    argv[1][i] ^= key[i % (sizeof(key)-1)];
  }

  // ((A | B) - (A & B))
  // for (int i = 0; i < len; i++) {
  //   argv[1][i] = (argv[1][i] | key[i%(sizeof(key)-1)]) - (argv[1][i] & key[i%(sizeof(key)-1)]);
  // }

  if (memcmp(argv[1], enc, sizeof(enc)) == 0) {
    puts("Correct!");
    printf("FLAG: %s\n", argv[1]);
  } else {
    puts("Wrong...");
  }

  return 0;
}