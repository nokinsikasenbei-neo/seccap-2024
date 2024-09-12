#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <ctype.h>

#define BUFFER_SIZE 1024
#define TABLE_SIZE 55

unsigned char k[] = {0x76,0x69,0x67,0x65,0x6e,0x65,0x72,0x65};

const char table[TABLE_SIZE] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz{}_";

// flagの中身はすべて小文字です。
int get_index(char c) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i] == c) {
            return i;
        }
    }
    return -1;
}

void encrypt(char *data, size_t data_len, const char *key, size_t key_len) {
    for (int i = 0, j = 0; i < data_len; i++, j++) {
        if (j >= key_len) {
            j = 0;
        }
        int data_index = get_index(data[i]);
        int key_index = get_index(key[j]);

        if (data_index != -1 && key_index != -1) {
            int shift = (data_index + key_index) % TABLE_SIZE;
            data[i] = table[shift];
        }
    }
}

int main() {
  // IPアドレスの入力
  char ipAddress[16];
  printf("Enter IP address: ");
  if (fgets(ipAddress, sizeof(ipAddress), stdin) == NULL) {
    perror("Failed to read IP address");
    return 1;
  }
  // 改行文字の削除
  size_t len = strlen(ipAddress);
  if (len > 0 && ipAddress[len - 1] == '\n') {
    ipAddress[len - 1] = '\0';
  }

  // ファイルの読み込み
  FILE *file = fopen("/tmp/flag", "r");
  if (file == NULL) {
    perror("Failed to open file");
    return 1;
  }

  // ファイル内容の取得
  char buffer[BUFFER_SIZE];
  size_t bytesRead = fread(buffer, 1, BUFFER_SIZE, file);
  fclose(file);

  // RC4キーと暗号化処理の初期化
  const char *key = k;
  size_t keyLen = strlen(key);

  // バッファの内容をRC4で暗号化
  encrypt((unsigned char *)buffer, bytesRead, (const unsigned char *)key,
          keyLen);

  // ソケットの作成
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    perror("Failed to create socket");
    return 1;
  }

  // 送信先のアドレスとポートの設定
  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(5000);
  if (inet_pton(AF_INET, ipAddress, &(serverAddr.sin_addr)) <= 0) {
    perror("Invalid address/Address not supported");
    return 1;
  }

  // サーバに接続
  if (connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) ==
      -1) {
    perror("Failed to connect to server");
    return 1;
  }

  // データの送信
  ssize_t bytesSent = send(sockfd, buffer, bytesRead, 0);
  if (bytesSent == -1) {
    perror("Failed to send data");
    return 1;
  }

  printf("Data sent successfully\n");

  // ソケットのクローズ
  close(sockfd);

  return 0;
}