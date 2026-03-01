# common.h: Common TCP functions for both client and server

## Types:

### tinytcp_common_socklen_t:

This type is used to represent socket lengths for POSIX.
On Windows, this is `int`.
On POSIX, this is `socklen_t` (which can be found in `<sys/socket.h>`).
IMPORTANT: This type's size might change dependent on platform.

### tinytcp_common_ssize_t:

This type is used to normalize signed returns on Windows and POSIX.
On Windows, this is `int`.
On POSIX, this is `ssize_t` (which can be found in `<sys/types.h>`).
IMPORTANT: This type's size might change dependent on platform.

### tinytcp_common_socket_t:

This type is used to normalize sockets on Windows and POSIX.
On Windows, this is `SOCKET` (which can be found in `<winsock.h>` or `<winsock2.h>`; the one used by **TinyTCP** is in `<winsock2.h>`).
On POSIX, this is `int`.
IMPORTANT: This type's size might change dependent on platform.

## Macros:

### Platform indicator macros:

#### TINYTCP_CONFIG_WINDOWS:

On Windows, this is `1`.
On POSIX, this is `0`.

#### TINYTCP_CONFIG_POSIX:

On Windows, this is `0`.
On POSIX, this is `1`.

### Constant definiton macros:

#### TINYTCP_COMMON_SSIZE_MAX:

The maximum integer value that can be held by `tinytcp_common_ssize_t` (which can be found in `"common.h"`; see [tinytcp_common_ssize_t](./common.md#tinytcp_common_ssize_t))
On Windows, this is `INT_MAX` (which can be found in `<limits.h>`).
On POSIX, this is `SSIZE_MAX` (which can be found in `<limits.h>`).

#### TINYTCP_COMMON_INVALID_SOCKET:

The constant that represents an invalid `tinytcp_common_socket_t` socket (which can be found in `"common.h"`; see [tinytcp_common_socket_t](./common.md#tinytcp_common_socket_t)).
On Windows, this is `(INVALID_SOCKET)` (which can be found in `<winsock.h>` or `<winsock2.h>`; the one used by **TinyTCP** is in `<winsock2.h>`).
On POSIX, this is `((int)-1)`.

## Functions:

### tinytcp_common_startup:

Initialize **TinyTCP**.
Signature: `int tinytcp_common_startup(void)`
Parameters: **_None_**
Windows Return: This function returns the value of `WSAStartup(MAKEWORD(2, 2), &wsa)` (which can be found in `<winsock.h>` or `<winsock2.h>`; the one used by **TinyTCP** is in `<winsock2.h>`). It initializes `winsock 2.2`.
POSIX Return: This function returns `0` on success or `-1` on failure. It sets the program to ignore `SIGPIPE` by using `signal(SIGPIPE, SIG_IGN)` (which can be found in `<signal.h>`).
IMPORTANT: This function must be called only _once_. Before calling any function in **TinyTCP**, this function must have been run successfully.
IMPORTANT: On POSIX, this function sets the signal handler for `SIGPIPE` to ignore it. This affects non-**TinyTCP** sockets as well. It is process-wide behavior.

### tinytcp_common_cleanup:

Cleanup **TinyTCP**.
Signature: `int tinytcp_common_cleanup(void)`
Parameters: **_None_**
Windows Return: This function returns the value of `WSACleanup()` (which can be found in `<winsock.h>` or `<winsock2.h>`; the one used by **TinyTCP** is in `<winsock2.h>`). It cleans up `winsock 2.2`.
POSIX Return: The return is 0 on success and -1 on failure. It restores handler of `SIGPIPE` from before initialization.
IMPORTANT: This function must be called only _once_.

### tinytcp_common_socket:

Open a new socket.
Signature: `tinytcp_common_socket_t tinytcp_common_socket(int domain, int protocol)`
Parameters:

- `int domain`: The domain of the socket. Must be `AF_INET` (for IPv4; On Windows, it can be found in `<winsock.h>` or `<winsock2.h>`; the one used by **TinyTCP** is in `<winsock2.h>`; On POSIX, it can be found in `<sys/socket.h>`) or `AF_INET6` (for IPv6; On Windows, it can be found in `<winsock2.h>`; On POSIX, it can be found in `<sys/socket.h>`).
- `int protocol`: The protocol to use. Usually 0 (for default TCP protocol).
  Windows Return: A new, valid socket on success or `TINYTCP_COMMON_INVALID_SOCKET` on failure.
  POSIX Return: A new, valid socket on success or `TINYTCP_COMMON_INVALID_SOCKET` on failure.
  IMPORTANT: The type of the socket will always be `SOCK_STREAM` (On Windows, it can be found in `<winsock.h>` or `<winsock2.h>`; the one used by **TinyTCP** is in `<winsock2.h>`; On POSIX, it can be found in `<sys/socket.h>`).

### tinytcp_common_closesocket:

Close a valid socket.
Signature: `bool tinytcp_common_closesocket(tinytcp_common_socket_t socket)`
Parameters:

- `tinytcp_common_socket_t socket`: The socket to close. Must be valid.
  Windows Return: `true` on success, `false` on failure.
  POSIX Return: `true` on success, `false` on failure.

### tinytcp_common_send:

Send bytes via TCP.
Signature: `tinytcp_common_ssize_t tinytcp_common_send(tinytcp_common_socket_t socket, const void *restrict data, size_t len)`
Parameters:

- `tinytcp_common_socket_t socket`: The socket to send bytes to. Must be valid.
- `const void *restrict data`: The data to send. Must be valid. Must not be `NULL`.
- `size_t len`: The amount of bytes to send. Must be less than `TINYTCP_COMMON_SSIZE_MAX` (which can be found in `"common.h"`; see [TINYTCP_COMMON_SSIZE_MAX](./common.md#tinytcp_common_ssize_max)).
  Windows Return: On success, the amount of bytes sent via TCP. On failure, a value that is less than `0`.
  POSIX Return: On success, the amount of bytes sent via TCP. On failure, a value that is less than `0`.
  IMPORTANT: The function may send fewer bytes than requested. The caller must handle partial sends.
  IMPORTANT: On POSIX, the function automatically retries on `EINTR`.

### tinytcp_common_recv:

Receive bytes via TCP.
Signature: `tinytcp_common_ssize_t tinytcp_common_recv(tinytcp_common_socket_t socket, void *restrict buf, size_t len)`
Parameters:

- `tinytcp_common_socket_t socket`: The socket to receive bytes from. Must be valid.
- `void *restrict buf`: The buffer to write bytes to. Must be valid. Must not be `NULL`.
- `size_t len`: The amount of bytes that can be written to the buffer.
  Windows Return: On success, the amount of bytes received via TCP. On failure, a value that is less than `0`.
  POSIX Return: On success, the amount of bytes received via TCP. On failure, a value that is less than `0`. If the peer socket has performed an orderly shutdown, this function returns `0`.
  IMPORTANT: The function may receive fewer bytes than requested. The caller must handle partial reads.
  IMPORTANT: On POSIX, the function automatically retries on `EINTR`.
