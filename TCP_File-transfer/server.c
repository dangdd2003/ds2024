#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define PORT 5000

// open chat function
void chat(int newsockfd) {
  char buff[1000];
  int n;
  for (;;) {
    bzero(buff, sizeof(buff));
    read(newsockfd, buff, sizeof(buff));
    printf("From client: %s", buff);
    if (strncmp(buff, "exit", 4) == 0) {
      printf("[-] Client stop receiving message!\n");
      break;
    }
    bzero(buff, sizeof(buff));
    printf("[+] Entter message to client: ");
    n = 0;
    while ((buff[n++] = getchar()) != '\n')
      ;
    write(newsockfd, buff, sizeof(buff));
    if (strncmp("exit", buff, 4) == 0) {
      bzero(buff, sizeof(buff));
      printf("[-] Server exit!");
      break;
    }
  }
}

// writing file function
void write_file(int sockfd, char *filename) {
  if (filename == NULL) {
    filename = "received.txt";
  }
  int n;
  char buff[1024];
  FILE *fp = fopen(filename, "w");
  while (1) {
    n = recv(sockfd, buff, sizeof(buff), 0);
    if (n == 0) {
      perror("[+] Writing file");
      close(sockfd);
      break;
    } else {
      fprintf(fp, "%s", buff);
      bzero(buff, sizeof(buff));
    }
  }
  printf("[+] Successfully writing file\n");
  fclose(fp);
}

int main(int argc, char *argv[]) {
  const char *ip = "127.0.0.1";

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
  servaddr.sin_addr.s_addr = inet_addr(ip);
  servaddr.sin_port = htons(5000);

  // bind ip/port to socket
  if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) == -1) {
    perror("[-] Error in binding");
    close(sockfd);
    exit(EXIT_FAILURE);
  } else {
    printf("[+] Successfully binding to socket\n");
  }

  // listen to remote host
  if (listen(sockfd, 10) == -1) {
    perror("[-] Error in starting listening remote host");
    close(sockfd);
    exit(EXIT_FAILURE);
  } else {
    printf("[+] Listening to remote host ... \n");
  }

  // accept the data from client
  socklen_t addr_size = sizeof(newaddr);
  int newsockfd = accept(sockfd, (struct sockaddr *)&newaddr, &addr_size);
  if (newsockfd == -1) {
    perror("[-] Error in receiving data from remote host");
    close(sockfd);
    close(newsockfd);
    exit(EXIT_FAILURE);
  } else {
    printf("[+] Successfully creating connection to client\n");
    printf("==================================================\n");
    // chat(newsockfd);
    write_file(newsockfd, argv[1]);
  }

  close(sockfd);
  close(newsockfd);

  return EXIT_SUCCESS;
}
