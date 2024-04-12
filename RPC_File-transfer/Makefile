rpcgen filetrans.x
gcc -c client.c -o client.o
gcc -c server.c -o server.o
gcc -c filetrans_clnt.c -o filetrans_clnt.o
gcc -c filetrans_xdr.c -o filetrans_xdr.o
gcc -c filetrans_svc.c -o filetrans_svc.o
gcc -o client client.o filetrans_clnt.o filetrans_xdr.o -ltirpc
gcc -o server server.o filetrans_svc.o filetrans_xdr.o -ltirpc
