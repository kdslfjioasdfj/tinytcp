# client.h: TCP functions for the client

## Functions:
### tinytcp_client_connect:
Try to connect to a server
Signature: `bool tinytcp_client_connect(tinytcp_common_socket_t socket, const char *restrict ip_addr, uint16_t port, int domain)`
Parameters:
- `tinytcp_common_socket_t socket`: The socket to use for the connection
- `const char *restrict ip_addr`: The IP address to try to connect to
- `uint16_t port`: The port to try to connect with
- `int domain`: The domain to connect with. Must match the domain used when `tinytcp_common_socket_t socket` was opened.
Windows Return: `true` for success and `false` for failure.
POSIX Return: `true` for success and `false` for failure.