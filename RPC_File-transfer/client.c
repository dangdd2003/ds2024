#include "file.h"
#include <rpc/clnt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("\n\n error: insufficient arguments!!!");
    exit(EXIT_FAILURE);
  }

  // get host and open connection
  char *host = argv[1];
  CLIENT *cl;
  cl = clnt_create(host, FILETRANSFER_PROG, FILETRANSFER_VERS, "tcp");
  if (cl == NULL) {
    clnt_pcreateerror(host);
    exit(EXIT_FAILURE);
  }

  // get filename
  char *filename = argv[2];
  FILE *file;
  file = fopen(filename, "r");

  buffer buff;
  buff.name = strcat(filename, "sv");

  int data;
  int *result;
  long total_byte;

  while (1) {
    data = fread(buff.data, 1, BLOCK, file);
    total_byte += data;
    buff.numbytes = data;
    result = filetransfer_proc_1(&buff, cl);

    if (result == NULL) {
      clnt_perror(cl, host);
      exit(EXIT_FAILURE);
    }

    if (data < BLOCK)
      break;
  }
  fclose(file);

  printf("File sent: %s\n", buff.name);
  printf("Byte sent: %ld\n", total_byte);

  return EXIT_SUCCESS;
}
