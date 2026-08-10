# HTTP Methods

HTTP methods tell the server **what the client wants to do** with a resource.

The most common methods are:

| Method | Purpose |
|--------|---------|
| `GET` | Read/retrieve data |
| `POST` | Create/send new data |
| `PUT` | Replace/update a resource |
| `PATCH` | Partially update a resource |
| `DELETE` | Delete a resource |

## Examples

### GET

```http
GET /users/42 HTTP/1.1
```

> Give me user 42.

### POST

```http
POST /users HTTP/1.1

{"name": "Bobby"}
```

> Create a new user.

### PUT

```http
PUT /users/42 HTTP/1.1

{"name": "Bob", "age": 30}
```

> Replace/update user 42.

### PATCH

```http
PATCH /users/42 HTTP/1.1

{"age": 30}
```

> Change only part of user 42.

### DELETE

```http
DELETE /users/42 HTTP/1.1
```

> Delete user 42.

## Key Idea

```text
GET     → Read
POST    → Create
PUT     → Replace
PATCH   → Partial update
DELETE  → Delete
```

These methods are part of the **HTTP protocol**. They are not socket functions.
