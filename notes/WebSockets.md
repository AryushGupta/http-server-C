# WebSocket

## What is WebSocket?

**WebSocket** is a communication protocol that creates a **persistent, two-way connection** between a client (such as a browser) and a server.

Unlike normal HTTP, where the client sends a request and the server sends a response, WebSocket allows **both sides to send messages whenever they want**.

### HTTP vs WebSocket

```text
HTTP

Browser ───── Request ─────> Server
Browser <──── Response ───── Server

Connection/request ends
```

With WebSocket:

```text
Browser  <==========================>  Server
              Persistent connection

        Browser → Server
        Server → Browser
        Browser → Server
        Server → Browser
```

---

## Why Do We Need WebSockets?

WebSockets are useful when an application needs **real-time communication**.

Examples:

- Chat applications
- Live notifications
- Online games
- Live dashboards
- Real-time collaboration
- Live updates

For example, in a chat application:

```text
Browser                     Server

   │                           │
   │──── "Hello" ─────────────>│
   │                           │
   │<──── "Hi" ────────────────│
   │                           │
   │<──── "New message" ──────│
   │                           │
   │──── "Okay" ──────────────>│
   │                           │
```

The server can send a message to the browser **without waiting for another browser request**.

---

## How Does a WebSocket Connection Start?

WebSocket initially uses HTTP to establish the connection.

The browser sends an HTTP request asking the server to upgrade the connection:

```http
GET /chat HTTP/1.1
Host: localhost:8080
Upgrade: websocket
Connection: Upgrade
Sec-WebSocket-Key: ...
Sec-WebSocket-Version: 13
```

The server responds:

```http
HTTP/1.1 101 Switching Protocols
Upgrade: websocket
Connection: Upgrade
Sec-WebSocket-Accept: ...
```

`101 Switching Protocols` means:

> The server agrees to switch from HTTP to WebSocket.

After the upgrade, communication happens using the WebSocket protocol.

```text
HTTP
 │
 │ Upgrade
 ▼
WebSocket
 │
 ├── Browser → Server
 ├── Server → Browser
 ├── Browser → Server
 └── Server → Browser
```

---

## WebSocket and TCP

WebSocket runs **on top of TCP**.

```text
Application
    │
    ▼
WebSocket
    │
    ▼
TCP
    │
    ▼
IP
```

This means WebSocket gets TCP's reliable, ordered byte-stream communication.

For a browser communicating with a C server, the basic architecture can look like:

```text
             TCP connection
Browser <==========================> C Server
             WebSocket

JavaScript                         C
    │                               │
    │──── "Hello Server" ─────────>│
    │                               │
    │<──── "Hello Browser" ─────────│
    │                               │
    │──── "Another message" ───────>│
    │                               │
    │<──── Server response ─────────│
```

---

## WebSocket vs HTTP

| Feature | HTTP | WebSocket |
|---|---|---|
| Communication | Request/Response | Two-way |
| Connection | Usually request-based | Persistent |
| Server can send anytime | No* | Yes |
| Real-time communication | Not ideal | Excellent |
| Common use | Websites, APIs | Chat, live updates |

`*` HTTP can achieve server-initiated-like updates using techniques such as polling or Server-Sent Events.

---

## WebSocket vs WebRTC

These technologies solve different problems.

| Technology | Main Purpose |
|---|---|
| HTTP/HTTPS | Request/response communication |
| WebSocket | Persistent two-way communication |
| WebRTC | Real-time peer-to-peer audio, video and data |
| TCP | Reliable transport protocol |
| UDP | Fast, connectionless transport |
| SSE | Server → browser real-time updates |
| MQTT | Lightweight messaging, commonly used in IoT |
| gRPC | Service-to-service communication |

---

## Simple Mental Model

Think of HTTP like sending letters:

```text
Client ─── Letter ───> Server
Client <── Reply ───── Server
```

WebSocket is more like keeping a phone call open:

```text
Client <================> Server
       Continuous connection
```

Both sides can communicate whenever necessary.

---

## Key Takeaways

- WebSocket provides **persistent, two-way communication**.
- It is useful for **real-time applications**.
- A WebSocket connection starts with an **HTTP upgrade request**.
- `101 Switching Protocols` indicates a successful upgrade.
- WebSocket runs over **TCP**.
- Unlike normal HTTP, the **server can send data to the client at any time**.
- WebSocket is a good choice for building **real-time browser ↔ server applications**.
