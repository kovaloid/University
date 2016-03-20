all:
	gcc -o client1 Client1_fifomsg.c
	gcc -o client2 Client2_fifomsg.c
	gcc -o client3 Client3_fifomsg.c
	gcc -o server Server_fifomsg.c
rm:
	rm server
	rm client1
	rm client2
	rm client3
rm_fifo:
	rm /tmp/fifo.1.in
	rm /tmp/fifo.1.out
	rm /tmp/fifo.2.in
	rm /tmp/fifo.2.out
	rm /tmp/fifo.3.in
	rm /tmp/fifo.3.out
