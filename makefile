# Charles "Blue" Kent Hartsell III
# ckhartsell@gmail.com

default: tcpclient.c tcpserver_fork.c
	gcc -o tcpclient tcpclient.c
	gcc -o tcpserver tcpserver_fork.c

clean:
	rm tcpclient
	rm tcpserver

runServer:
	./tcpserver 5000

runClient:
	./tcpclient 5000 10.8.0.1 test.txt
