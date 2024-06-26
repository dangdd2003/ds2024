
# RPC File Transfer

- 1-1 File transfer using RPC in CLI
    - One server
    - One client

## Requirement

- rpcgen - generate RPC function
- rpcbind - map rpc generic addresses with RPC program
- gcc, GNU make - C compiler

## Implementation

- Start
```bash
make
```
- Run
    - Prepare rpc env (with root)
    ```bash
    rpcbind start # start rpcbind
    rpcinfo # check rpc status
    ```
    - Start rpc in one line
    ```bash
    ./server & ./client {host} {file}
    ```

- Run in deamon
    - Open a shell
    ```bash
    ./server
    ```
    - Open second shell
    ```bash\
    ./client {host} {file}
    ```
- Stop (find and kill the process)
```bash
ps -ef | grep server
kill {PID of ./server}
```
- Clean
```bash
make clean
```
