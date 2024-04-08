# TCP File Transfer

- 1-1 File transfer over TCP/IP in CLI, based on provided chat system.
  - One server
  - One client
  - Using socket

## Run

- Create any file (file to send)
- Compile server and client

```bash
gcc server.c -o server.out
gcc client.c -o client.out
```

- Open server

```bash
./server.out {output filename (default "received.txt")}
```

- Run client to send `send.txt` file

```bash
./client.out {input file (default "hello.txt")}
```

- By default, data from file `hello.txt` will be written to `received.txt` in
  server socket
- Maximum for buffer to store txt file is 1024 Byte (1MB)
