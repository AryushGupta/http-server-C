TCP vs HTTP

Understanding the difference between TCP and HTTP is important when learning networking, web servers, APIs, and HTTP server development in C.

TCP = how data is reliably transported.HTTP = how the data is structured and what it means.

1. The Big Picture

Browser
   |
   | HTTP
   v
HTTP Server
   |
   | TCP
   v
Network

A simplified networking stack:

┌──────────────────────┐
│        HTTP          │  ← Application protocol
├──────────────────────┤
│        TCP           │  ← Transport protocol
├──────────────────────┤
│        IP            │  ← Network protocol
├──────────────────────┤
│ Ethernet / Wi-Fi     │  ← Network access
└──────────────────────┘

HTTP sits on top of TCP in traditional HTTP/1.1 and HTTP/2 communication.

2. What Is TCP?

TCP = Transmission Control Protocol

TCP provides reliable communication between two programs over a network.

It provides features such as:

Reliable delivery

Ordered data

Error detection

Retransmission of lost data

Flow control

Connection management

TCP does not understand HTTP methods such as GET or POST.

3. What Is HTTP?

HTTP = Hypertext Transfer Protocol

HTTP defines how clients and servers communicate at the application level.

Example request:

GET /index.html HTTP/1.1
Host: example.com

Example response:

HTTP/1.1 200 OK
Content-Type: text/html

<html>
    <body>
        Hello!
    </body>
</html>

HTTP defines:

GET

POST

PUT

DELETE

Headers

Status codes

Request format

Response format

4. TCP Doesn't Know About HTTP

Suppose an HTTP server receives:

GET /hello HTTP/1.1
Host: localhost

TCP does not know that this is an HTTP request.

From TCP's perspective, it is simply a sequence of bytes.

HTTP
   ↓
Sequence of bytes
   ↓
TCP transports those bytes
   ↓
Network

Your HTTP server code is responsible for interpreting those bytes as an HTTP request.

5. Analogy

Think about sending a package.

TCP is the delivery system.

It handles:

Make sure this package gets from A to B reliably.

HTTP is the message inside the package.

It says:

Please give me /index.html.

┌─────────────────────────────┐
│ HTTP                        │
│                             │
│ GET /index.html HTTP/1.1    │
│ Host: example.com           │
└─────────────────────────────┘
              ↓
         TCP transports it
              ↓
           Network

6. TCP Connection

TCP is connection-oriented.

A TCP connection is established using the three-way handshake:

Client                         Server

   | -------- SYN ------------> |
   |                            |
   | <------ SYN + ACK -------- |
   |                            |
   | -------- ACK ------------> |
   |                            |
   |      Connection ready      |

After the connection is established, application data can be exchanged.

7. HTTP Request Over TCP

Suppose you visit:

http://localhost:8080/

Your browser connects to a server listening on port 8080.

Browser
   |
   | 1. Establish TCP connection
   v
TCP Server
   |
   | 2. Send HTTP request
   v
HTTP Server
   |
   | 3. Parse request
   v
HTTP Response
   |
   | 4. Send response through TCP
   v
Browser

The HTTP request might look like:

GET / HTTP/1.1
Host: localhost:8080
Connection: close

Your C program receives this as bytes through a TCP socket.

8. How This Relates to a C HTTP Server

At the C level, you will commonly use:

socket()
bind()
listen()
accept()
recv()
send()
close()

For example:

int client_fd = accept(server_fd, ...);

recv(client_fd, buffer, sizeof(buffer), 0);

After recv() gives you data, you might see:

GET / HTTP/1.1
Host: localhost:8080
...

Now your HTTP logic begins.

You need to parse:

GET
/
HTTP/1.1

Then create a response:

HTTP/1.1 200 OK
Content-Type: text/plain
Content-Length: 12

Hello World!

And send it through the TCP socket:

send(client_fd, response, response_length, 0);

The project can therefore be viewed as:

             YOUR C PROGRAM
                   |
        ┌──────────┴──────────┐
        |                     |
   TCP/Sockets            HTTP Logic
        |                     |
   socket()               Parse request
   bind()                 GET / POST
   listen()               Headers
   accept()               Status codes
   recv()                 Response
   send()

9. TCP vs HTTP

TCP

HTTP

Transport protocol

Application protocol

Transports bytes

Defines meaning/structure of data

Reliable

Defines requests/responses

Connection-oriented

Uses application-level request/response

Doesn't understand GET or POST

Defines GET, POST, etc.

Uses ports

Uses URLs, methods, headers, status codes

Lower in the network stack

Higher in the network stack

10. HTTP/1.1, HTTP/2, and HTTP/3

A useful modern detail:

HTTP/1.1 → TCP
HTTP/2   → TCP
HTTP/3   → QUIC → UDP

HTTP/3 uses QUIC, which runs over UDP rather than TCP.

For a first C HTTP server, TCP + HTTP/1.1 is an excellent starting point.

11. Mental Model

                 APPLICATION
              ┌───────────────┐
              │     HTTP      │
              │ GET /         │
              │ POST /data    │
              └───────┬───────┘
                      │
                 TRANSPORT
              ┌───────▼───────┐
              │      TCP      │
              │ Reliable data │
              │  connection   │
              └───────┬───────┘
                      │
                  NETWORK
              ┌───────▼───────┐
              │      IP       │
              └───────────────┘

Key Takeaway

TCP moves the bytes reliably; HTTP tells you what those bytes mean.
