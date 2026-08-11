# HTTP Headers

HTTP headers are **extra information (metadata)** attached to an HTTP request or response.

## Basic Structure

A header looks like:

```http
Name: Value
```

Example:

```http
Host: example.com
Content-Type: application/json
```

## HTTP Message

```text
HTTP Message
│
├── Request/Status Line
├── Headers
├── Empty Line
└── Body (optional)
```

The **body is optional**. It contains the actual data being sent.

## Common Headers

| Header | Purpose |
|---|---|
| `Host` | Tells the server which host is requested |
| `Content-Type` | Tells what type of data is in the body |
| `Content-Length` | Tells the size of the body in bytes |
| `User-Agent` | Gives information about the client |
| `Accept` | Tells the server what type of response the client accepts |

## Example

```http
POST /users HTTP/1.1
Host: localhost:8080
Content-Type: application/json
Content-Length: 25

{"name":"Alex","age":22}
```

Here:

- **Headers** describe the message.
- **Empty line** separates headers from the body.
- **Body** contains the actual data.

> **Simple idea:** Headers describe the HTTP message; the body carries the actual data.
