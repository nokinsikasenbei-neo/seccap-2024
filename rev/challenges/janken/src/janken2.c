#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 256

typedef enum
{
    Gu,
    Choki,
    Pa
} janken;

int gen_seed(janken *player_hands)
{
    int seed = 99999;
    for (int i = 0; i < 256; i++){
        seed = seed * player_hands[i % 5];
    }
    // printf("Seed: %d\n", seed);
    return seed;
}

int gen_random()
{
    return rand() % 3;
}

void swap(unsigned char *a, unsigned char *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}

int KSA(char *key, unsigned char *S)
{

    // 配列Sの初期化(S[0]=0, S[1]=1....S[255]=255)
    for (int i = 0; i < N; i++)
        S[i] = i;

    // KSAで初期ストリームを生成
    int j = 0;
    int len = strlen(key);
    for (int i = 0; i < N; i++)
    {
        j = (j + S[i] + key[i % len]) % N;
        swap(&S[i], &S[j]);
    }

    return 0;
}

int PRGA(unsigned char *S, char *text, unsigned char *encrypted_text)
{

    int i = 0;
    int j = 0;
    for (size_t n = 0, len = strlen(text); n < len; n++)
    {
        i = (i + 1) % N;
        j = (j + S[i]) % N;
        swap(&S[i], &S[j]);
        int K = S[(S[i] + S[j]) % N];
        encrypted_text[n] = K ^ text[n];
    }

    return 0;
}

void dec_flag(char *key, char *text, unsigned char *decrypted_text)
{
    // 00201
    // GuGuPaGuChoki
    unsigned char S[N];

    KSA(key, S);
    PRGA(S, text, decrypted_text);
}

void append_to_key(char *key, janken player_choice)
{
    const char *choices[] = {"Gu", "Choki", "Pa"};
    strncat(key, choices[player_choice], strlen(choices[player_choice]));
}

int main()
{
    janken npc;
    int seed = 0;
    char key[256];
    janken player_hands[5];
    
    for (int round = 0; round < 5; round++)
    {
        puts("[0: Gu, 1: Choki, 2: Pa ]");
        printf(">>");
        scanf("%d", &player_hands[round]);
    }

    key[0] = '\0';
    seed = gen_seed(player_hands);
    srand(seed);
    for (int round = 0; round < 5; round++)
    { 
        npc = gen_random();
        switch ((player_hands[round] - npc + 3) % 3)
        {
        case 2:
            append_to_key(key, player_hands[round]);
            continue;
        default:
            puts("Oops. You couldn't beat me lol");
            puts("Play again!");
            return -1;
        }
    }

    puts("You win!");
    char enc[] = {0x59, 0x7b, 0xb6, 0x1a, 0xfa, 0x12, 0x38, 0x17, 0xb0, 0x45, 0x60, 0xae, 0x59, 0x2b, 0x63, 0x13, 0x56, 0x8d, 0x58, 0x2e, 0x28, 0xbe, 0xe0, 0xf7, 0x9a, 0xc5, 0xbc, 0xaf, 0x00};
    unsigned char *decrypted_text = malloc(sizeof(unsigned char) * sizeof(enc));
    dec_flag(key, enc, decrypted_text);
    printf("Flag: %s\n", decrypted_text);

    return 0;
}
