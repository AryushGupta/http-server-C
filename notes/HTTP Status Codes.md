# HTTP Status Codes

HTTP status codes are **3-digit numbers** sent by the server to tell the client what happened to its request.

Example:

```http
HTTP/1.1 200 OK
```

Here, `200` is the status code.

## Why Do We Need Them?

They give the client a quick result of the request:

```text
200 → Request worked
404 → Resource not found
500 → Server error
```

The client can understand the result without reading the entire response body.

## Main Categories

| Range | Meaning | Example |
|---|---|---|
| `1xx` | Information | `100` |
| `2xx` | Success | `200 OK` |
| `3xx` | Redirection | `301 Moved Permanently` |
| `4xx` | Client error | `404 Not Found` |
| `5xx` | Server error | `500 Internal Server Error` |

## Important Status Codes

```text
200 → OK
201 → Created
400 → Bad Request
404 → Not Found
500 → Internal Server Error
```

## Example

```http
HTTP/1.1 200 OK
Content-Type: text/plain
Content-Length: 13

Hello, World!
```

Here:

- `200 OK` → tells the client the request was successful.
- Headers → provide information about the response.
- Body → contains the actual data.

> **Simple idea:** Status codes tell the client what happened to its request.
