# HTTP Request & Response

HTTP communication is based on a simple idea:

```text
Client → Request → Server
Client ← Response ← Server
```

## Request

A **request** is a message sent by the client to the server asking it to do something.

Example:

```http
GET /users HTTP/1.1
Host: example.com
```

A request can contain:

- **Method** — what the client wants to do
- **Path** — which resource it wants
- **Headers** — extra information
- **Body** — data sent to the server (when needed)

## Response

A **response** is the message sent back by the server.

Example:

```http
HTTP/1.1 200 OK
Content-Type: application/json

{"message": "Hello"}
```

A response can contain:

- **Status code** — tells whether the request succeeded
- **Headers** — information about the response
- **Body** — the actual data

## Simple Example

```text
Browser
   |
   | GET /users
   ↓
Server
   |
   | 200 OK + user data
   ↓
Browser
```

### Key Idea

> **Request = What does the client want?**  
> **Response = What did the server return?**
