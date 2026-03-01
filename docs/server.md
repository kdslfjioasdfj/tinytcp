# server.h: TCP functions for the server

## Functions:

### tinytcp_server_bind:

Bind a socket to a hardware port.
Signature: `int tinytcp_server_bind(tinytcp_common_socket_t socket, const char *restrict ip_addr, uint16_t port, int domain)`
Parameters:

- `tinytcp_common_socket_t socket`: The socket to bind to a port. Must be valid.
- `const char *restrict ip_addr`: The network card to listen on. Can be either IPv4 or IPv6.
- `uint16_t port`: The port to bind the socket to. Must be accessible with the process's current permissions.
- `int domain`: The domain of the socket. Must match _exactly_ to the value used when creating the socket.
  Windows Return: `0` on success and `-1` on failure.
  POSIX Return: `0` on success and `-1` on failure.

### tinytcp_server_listen:

Listen for clients
Signature: `bool tinytcp_server_listen(tinytcp_common_socket_t socket, int backlog)`
Parameters:

- `tinytcp_common_socket_t socket`: The socket to listen from. Must be successfully bound to a port. Must be valid.
- `int backlog`: The backlog to keep when receiving clients.
  Windows Return: The return value of `listen(socket, backlog)` (which can be found in `<winsock.h>` or `<winsock2.h>`; the one used by **TinyTCP** is in `<winsock2.h>`).
  POSIX Return: The return value of `listen(socket, backlog)` (which can be found in `<sys/socket.h>`).

### tinytcp_server_accept:

Accept a new client
Signature: `tinytcp_common_socket_t tinytcp_server_accept(tinytcp_common_socket_t socket, char *restrict out, tinytcp_common_socklen_t outlen, uint16_t *restrict port)`
Parameters:

- `tinytcp_common_socket_t socket`: The socket to accept from
- `char *restrict out`: The buffer to output the client's IP to. Can be `NULL` if unwanted. It is suggested that this be at least 46 bytes.
- `tinytcp_common_socklen_t outlen`: The length of the buffer. Must be greater than 0. Must be able to contain the full IP address. It is suggested to let this be at least 46.
- `uint16_t *restrict port`: The buffer to output the client's source port. Can be `NULL` if unwanted.
  Windows Return: A new socket to the client on success or `TINYTCP_COMMON_INVALID_SOCKET` (which can be found in `"common.h"`; see [TINYTCP_COMMON_INVALID_SOCKET](./common.md#tinytcp_common_invalid_socket)) on failure.
  POSIX Return: A new socket to the client on success or `TINYTCP_COMMON_INVALID_SOCKET` (which can be found in `"common.h"`; see [TINYTCP_COMMON_INVALID_SOCKET](./common.md#tinytcp_common_invalid_socket)) on failure.
  IMPORTANT: `uint16_t *restrict port` and `char *restrict out` remain unchanged on failure.
