all: server client

server: 
	gcc echoserveri.c echo.c csapp.c -lpthread -o server

client:
	gcc echoclient.c csapp.c -lpthread -o client

clean:
	rm server
	rm client
