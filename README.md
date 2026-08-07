# HTTP Server in C

A lightweight HTTP server built from scratch in C to understand how HTTP works at the socket and protocol level.

## Overview

This project is focused on learning how a web server communicates with clients using TCP sockets and the HTTP protocol.

The server receives HTTP requests, parses the request data, processes the requested path, and sends an appropriate HTTP response back to the client.

## Features

- TCP socket-based client-server communication
- HTTP request handling
- HTTP request line parsing
- HTTP method and path parsing
- HTTP response generation
- Status codes and response headers
- Response body handling
- Basic routing

## Technologies

- C
- TCP/IP
- HTTP
- Socket Programming
- GCC

## How It Works

The basic communication flow is:

Client → TCP Connection → HTTP Request → Server Processing → HTTP Response → Client

Example request:

```http
GET /hello HTTP/1.1
Host: localhost:8080
