My(Butt)Cloud: Server & Client
==============================

Server
------
`usage: ./buttserver <port> <secret_key>`

Client
------
`usage: ./buttclient <req_type> <host> <port> <secret> [<file>]`

There are 4 request types:

- "put"
- "del", also aliased as "rm"
- "get"
- "list"

Also included are four shell scripts that conform to the naming
specified in the project spec. Each corresponds with a request type.

The client will only print to stdin for three reasons:

1. The client has made a get request, and a file with the provided
   name has been found.
2. The client has made a list request.
3. If an error is encountered on the server, the uninformative message
   "ERROR" is printed out by the client.
