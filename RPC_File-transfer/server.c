#include "file.h"
#include "stdio.h"
#include <rpc/rpc.h>
#include <rpc/svc.h>
#include <stdio.h>

int *filetransfer_proc_1_svc(buffer *recvbuff, struct svc_req *req) {
  FILE *file;
  static int write_bytes;

  file = fopen(recvbuff->name, "a");
  if (file == NULL) {
    write_bytes = -1;
    return &write_bytes;
  }

  write_bytes = fwrite(recvbuff->data, 1, recvbuff->numbytes, file);
  fclose(file);
  return &write_bytes;
}
