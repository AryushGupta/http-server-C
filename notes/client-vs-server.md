Client vs Server

Understanding client vs server is fundamental to learning HTTP, networking, APIs, web applications, and backend development.

1. The Basic Idea

Think of a restaurant:

You → Client

Waiter → Communication/request

Kitchen → Server

Food → Response

You ask:

"Give me a burger."

The kitchen prepares it and sends it back.

This is similar to what happens on the internet:

CLIENT  ──────── Request ────────>  SERVER
CLIENT  <─────── Response ─────── SERVER

2. What Is a Client?

A client is a program or device that asks for something from another program.

Examples:

Web browsers such as Chrome or Firefox

Mobile applications

Python programs

C programs

Postman

Frontend JavaScript code

The client generally initiates communication by sending a request.

3. What Is a Server?

A server is a program that waits for requests and provides something in response.

Examples:

Web servers

API servers

Database servers

File servers

A server is not necessarily a special type of computer.

A normal computer can run a program that behaves as a server:

while (1) {
    wait_for_connection();

    receive_request();

    send_response();
}

The important idea is that the program listens for requests and responds to them.

4. Client and Server Are Roles

"Client" and "server" describe roles, not necessarily different machines.

For example:

Computer A
    |
    | HTTP request
    v
Computer B
    |
    | HTTP response
    v
Computer A

Computer A is acting as the client and Computer B is acting as the server.

However, a program can also act as both.

For example:

Browser
    |
    | request
    v
Backend Server
    |
    | request
    v
Database Server

Here:

Browser → Client

Backend → Server and Client

Database → Server

The backend is a server to the browser but a client to the database.

5. What Happens When You Visit a Website?

Suppose you visit:

https://example.com

Step 1 — Browser Creates a Request

The browser might create an HTTP request such as:

GET / HTTP/1.1
Host: example.com

This means:

"Server, please give me the / resource."

Step 2 — Request Travels Through the Network

Browser
   |
   | HTTP request
   v
Internet
   |
   v
Server

Step 3 — Server Receives the Request

The server sees something like:

GET /

It decides what it needs to do.

For example, it might find:

index.html

Step 4 — Server Sends a Response

The server might respond with:

HTTP/1.1 200 OK
Content-Type: text/html

<html>
    <body>
        Hello!
    </body>
</html>

Step 5 — Browser Processes the Response

The browser receives the HTML and renders it as a webpage.

SERVER
   |
   | HTML
   v
BROWSER
   |
   v
Web page

6. Client vs Server

Client

Server

Makes requests

Receives requests

Usually initiates communication

Usually waits for communication

Requests resources/services

Provides resources/services

Browser is an example

Web server is an example

Postman is an example

API server is an example

Usually interacts with the user

Usually works in the background

Remember: client and server are roles, not permanent identities.

7. Where Does HTTP Fit In?

HTTP (Hypertext Transfer Protocol) is a protocol used for communication between clients and servers.

The basic model is:

Client
   |
   | HTTP
   |
   v
Server

HTTP defines methods such as:

GET
POST
PUT
DELETE

It also defines response status codes such as:

200 OK
404 Not Found
500 Internal Server Error

When building an HTTP server in C, the goal is to create a program that can understand HTTP requests and produce appropriate HTTP responses.

8. Example: Searching on YouTube

Suppose you search YouTube for:

cats

Your browser or YouTube app acts as the client.

It might send a request similar to:

GET /search?q=cats

The server receives the request, processes the search, and sends a response.

YouTube Client
      |
      | GET /search?q=cats
      v
YouTube Server
      |
      | Process search
      v
YouTube Server
      |
      | HTTP response
      v
YouTube Client

The client then displays the search results.

9. Key Idea

The simplest definition to remember is:

Client = asks for something.

Server = waits for requests and provides something.

And:

HTTP = a set of rules for how they communicate.

The overall process looks like:

CLIENT
  |
  | HTTP Request
  | "Give me X"
  v
SERVER
  |
  | HTTP Response
  | "Here is X"
  v
CLIENT

10. Connection to a C HTTP Server

When building an HTTP server in C, this concept becomes practical.

The server will eventually perform operations such as:

Socket
   ↓
Bind
   ↓
Listen
   ↓
Accept
   ↓
Receive HTTP Request
   ↓
Parse Request
   ↓
Create HTTP Response
   ↓
Send Response

This is the foundation for understanding how web servers work at a lower level.
