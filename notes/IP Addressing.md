# IP Address

**IP = Internet Protocol**

An **IP address** is a numerical address given to a device on a network. It helps identify where data should be sent and where it came from.

## Why Do We Need IP Addresses?

When one device sends data to another, the network needs to know the destination.

```text
┌─────────────────────────────────┐
│ Source IP:      192.168.1.10    │
│ Destination IP: 192.168.1.20    │
│ Data:           Hello           │
└─────────────────────────────────┘
```

Think of an IP address like a **postal address for a device**.

## Types of IP Addresses

### 1. IPv4

IPv4 uses **32 bits** and is written as four decimal numbers.

```text
192.168.1.10
```

Each part ranges from `0` to `255`.

```text
192 . 168 . 1 . 10
 ↑      ↑    ↑    ↑
       8 bits each
       = 32 bits
```

IPv4 has approximately:

```text
2³² ≈ 4.3 billion
```

possible addresses.

### 2. IPv6

IPv6 uses **128 bits** and provides a much larger address space.

Example:

```text
2001:0db8:85a3:0000:0000:8a2e:0370:7334
```

IPv6 was introduced mainly because IPv4 addresses are limited.

```text
IPv4 → 32 bits
IPv6 → 128 bits
```

## Public and Private IP

### Private IP

Used inside a **local network**, such as a home or office.

Examples:

```text
192.168.1.10
192.168.1.20
10.0.0.5
```

Example:

```text
             Router
          192.168.1.1
          /    |    \
         /     |     \
       PC    Phone   Laptop
      .1.10   .1.20   .1.30
```

Private IP addresses are not directly reachable from the public Internet.

### Public IP

Used to communicate with devices over the **Internet**.

```text
Your Computer
      ↓
    Router
      ↓
  Public IP
      ↓
   Internet
```

Your Internet Service Provider (ISP) generally provides your network with a public IP.

## Static and Dynamic IP

### Static IP

A **static IP** generally remains the same.

```text
Server
   ↓
203.0.113.10
```

Useful for servers and devices that need a consistent address.

### Dynamic IP

A **dynamic IP** can change over time.

```text
Today    → 49.x.x.x
Tomorrow → 103.x.x.x
```

Dynamic IPs are commonly assigned automatically by a network or ISP.

## Quick Summary

| Type | Meaning |
|---|---|
| **IPv4** | 32-bit IP address |
| **IPv6** | 128-bit IP address |
| **Private IP** | Used inside local networks |
| **Public IP** | Used on the Internet |
| **Static IP** | Usually stays the same |
| **Dynamic IP** | Can change over time |

## Key Idea

```text
IP Address
    ↓
Identifies the network destination
    ↓
Helps deliver data to the correct device
```

> **IP address = Address of a device/network interface**
