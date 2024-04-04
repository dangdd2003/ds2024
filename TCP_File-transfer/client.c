#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define SIZE 1024

// read and send file to socket buffer
void send_file(FILE *fp, int sockfd) {
  int n;
  char data[SIZE] = {0};

  while (fgets(data, SIZE, fp) != NULL) {
    if (send(sockfd, data, sizeof(data), 0) == -1) {
      perror("[-]Error in sending file");
      exit(1);
    }
    bzero(data, SIZE);
  }
}

int main(int argc, char **argv) {
  char *ip = "127.0.0.1";
  int port = 5000;
  int e;

  int sockfd;
  struct sockaddr_in server_addr;
  FILE *fp;
  char *filename = "send.txt";

  // init socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    perror("[-]Error in socket");
    exit(1);
  }
  printf("[+]Server socket created successfully.\n");

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  // bind socket - connect to server
  e = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (e == -1) {
    perror("[-]Error in socket");
    exit(1);
  }
  printf("[+]Connected to Server.\n");

  // open file
  fp = fopen(argv[1], "r");
  if (fp == NULL) {
    perror("[-]Error in reading file");
    exit(1);
  }

  // send file
  send_file(fp, sockfd);
  printf("[+]File data sent successfully.\n");

  // close the connection
  printf("[+]Closing the connection.\n");
  fclose(fp);
  close(sockfd);

  return 0;
}
