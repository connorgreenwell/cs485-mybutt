all: buttserver buttclient

buttserver: 
	gcc server/buttserver.c server/serve.c common/csapp.c -lpthread -Icommon -o $@

buttclient: 
	gcc client/buttclient.c common/csapp.c -lpthread -Icommon -o $@

clean:
	rm buttserver
	rm buttclient
