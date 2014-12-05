CC=gcc -Wall -std=c99

all: buttserver buttclient
	chmod u+x mc*

buttserver: common/requests.o server/buttserver.o server/serve.o server/storage.o
	${CC} $^ -lpthread -Icommon -o $@

buttclient: common/requests.o client/buttclient.o
	${CC} $^ -lpthread -Icommon -o $@

%.o: %.c
	${CC} $< -lpthread -Icommon -c -o $@

clean:
	rm -f */*.o buttserver buttclient
	chmod u-x mc*
