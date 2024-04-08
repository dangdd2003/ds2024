#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define PORT 5000

// open chat function
void chat(int sockfd) {
  char buff[1000];
  int n;
  for (;;) {
    bzero(buff, sizeof(buff));
    printf("[+] Enter message to server: ");
    n = 0;
    while ((buff[n++] = getchar()) != '\n')
      ;
    write(sockfd, buff, sizeof(buff));
    if (strncmp("exit", buff, 4) == 0) {
      bzero(buff, sizeof(buff));
      printf("[-] Client exit!");
      break;
    }
    read(sockfd, buff, sizeof(buff));
    printf("From server: %s", buff);
    if (strncmp("exit", buff, 4) == 0) {
      bzero(buff, sizeof(buff));
      printf("[-] Server stop receiving message!\n");
      break;
    }
  }
}

// sending file function
void send_file(int sockfd, FILE *file) {
  if (file == NULL) {
    char *filename = "hello.txt";
    FILE *file = fopen(filename, "r");
  }
  int n;
  char buff[1024];
  while (fgets(buff, sizeof(buff), file) != NULL) {
    if (send(sockfd, buff, sizeof(buff), 0) == -1) {
      perror("[-] Error in sending file");
      close(sockfd);
      fclose(file);
      exit(EXIT_FAILURE);
    } else {
      bzero(buff, sizeof(buff));
    }
  }
  printf("[+] Successfully sending file to server\n");
  fclose(file);
}

int main(int argc, char *argv[]) {
  const char *IP = "127.0.0.1";

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  // initialize socket
  struct sockaddr_in servaddr, newaddr;
  if (sockfd == -1) {
    perror("[-] Error in creating socket");
    exit(EXIT_FAILURE);
  } else {
    printf("[+] Successfully creating socket\n");
  }
  bzero(&servaddr, sizeof(servaddr));

  // assign IP, PORT to socket
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr(IP);
  servaddr.sin_port = htons(PORT);

  // connect to remote host
  if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
    perror("[-] Error in connecting to host");
    close(sockfd);
    exit(EXIT_FAILURE);
  } else {
    printf("[+] Successfully creating connection to server\n");
    printf("==================================================\n");
    // chat(sockfd);
    send_file(sockfd, fopen(argv[1], "r"));
  }

  close(sockfd);

  return EXIT_SUCCESS;
}
