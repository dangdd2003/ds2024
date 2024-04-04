#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>
#define SIZE 1024

// read and write file from socket buffer
void write_file(int sockfd, char *filename) {
  if (filename == NULL) {
    filename = "recieve.txt";
  }
  int n;
  FILE *fp;
  char buffer[SIZE];

  fp = fopen(filename, "w");
  while (1) {
    n = recv(sockfd, buffer, SIZE, 0);
    if (n <= 0) {
      break;
      return;
    }
    fprintf(fp, "%s", buffer);
    bzero(buffer, SIZE);
  }
  return;
}

int main(int argc, char **argv) {
  char *ip = "127.0.0.1";
  int port = 5000;
  int e;

  int sockfd, new_sock;
  struct sockaddr_in server_addr, new_addr;
  socklen_t addr_size;
  char buffer[SIZE];

  // inti socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    perror("[-]Error in socket");
    exit(1);
  }
  printf("[+]Server socket created successfully.\n");

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  // bind socket - open server
  e = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (e < 0) {
    perror("[-]Error in bind");
    exit(1);
  }
  printf("[+]Binding successfull.\n");

  // listen to the socket
  if (listen(sockfd, 10) == 0) {
    printf("[+]Listening....\n");
  } else {
    perror("[-]Error in listenning.");
    exit(1);
  }

  // write file
  addr_size = sizeof(new_addr);
  new_sock = accept(sockfd, (struct sockaddr *)&new_addr, &addr_size);
  write_file(new_sock, argv[1]);
  printf("[+]Data written in the file successfully.\n");

  // close the connection
  printf("[+]Closing the connection.\n");
  close(sockfd);
  close(new_sock);

  return EXIT_SUCCESS;
}
