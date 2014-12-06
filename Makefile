CC=gcc -Wall -std=gnu99
DUMMIES=mcput.c mcget.c mclist.c mcdel.c mycloud_server.c

all: buttserver buttclient symlinks
	chmod u+x mc*

buttserver: common/requests.o server/buttserver.o server/serve.o server/storage.o
	${CC} $^ -lpthread -Icommon -o $@

buttclient: common/requests.o client/buttclient.o
	${CC} $^ -lpthread -Icommon -o $@

%.o: %.c
	${CC} $< -lpthread -Icommon -c -o $@

symlinks:
	for dummy in ${DUMMIES}; do [[ -e "$$dummy" ]] || ln -s Makefile "$$dummy"; done

clean-symlinks:
	for dummy in ${DUMMIES}; do rm -f $$dummy; done

clean: clean-symlinks
	rm -f */*.o buttserver buttclient
	chmod u-x mc*
