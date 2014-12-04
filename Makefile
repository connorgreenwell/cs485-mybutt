all: buttserver buttclient

buttserver: server/buttserver.c server/serve.c
	gcc $^ -lpthread -Icommon -o $@

buttclient: client/buttclient.c
	gcc $^ -lpthread -Icommon -o $@

clean:
	rm buttserver
	rm buttclient
