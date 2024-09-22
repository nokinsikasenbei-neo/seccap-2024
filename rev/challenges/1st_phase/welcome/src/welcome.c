#include <stdio.h>
#include <string.h>

char pass[7] = {'S', 'e', 'c', 'C', 'a', 'p', 'A'};

int main(void) {
  char input[50];
  printf("What is the name of this class? > ");
  scanf("%s", input);

  if (strlen(input) != 7) {
    puts("Incorrect");
    return 1;
  }

  for (int i = 0; i < sizeof(pass); i++) {
    if (input[i] != pass[i]) {
      puts("Incorrect");
      return 1;
    }
  }
  printf("Correct!\nFLAG: FLAG{Welcome_to_SecCap_A_2024}\n");
  return 0;
}