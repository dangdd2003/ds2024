# TCP File Transfer

- 1-1 File transfer over TCP/IP in CLI, based on provided chat system.
  - One server.
  - One client
  - Using socket

## Run

- Create file `send.txt` (file to send)
- Compile server and client

```bash
gcc server.c -o server.out
gcc client.c -o client.out
```

- Open server

```bash
./server.out
```

- Run client to send `send.txt` file

```bash
./client.out
```

- Data from file `send.txt` will be written to `receive.txt` in server socket
