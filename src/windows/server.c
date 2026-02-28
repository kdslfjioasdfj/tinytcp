#include "server.h"
#include "common.h"
#include <ws2tcpip.h>

int tinytcp_server_bind(tinytcp_common_socket_t socket,
                        const char *restrict ip_addr, uint16_t port,
                        int domain) {
  switch (domain) {
  case AF_INET: {
    struct sockaddr_in internal_addr = {0};
    if (inet_pton(AF_INET, ip_addr, &(internal_addr.sin_addr)) <= 0)
      return -1;
    internal_addr.sin_port = htons(port);
    internal_addr.sin_family = domain;
    return bind(socket, (const struct sockaddr *)&internal_addr,
                sizeof(internal_addr));
  }
  case AF_INET6: {
    struct sockaddr_in6 internal_addr = {0};
    internal_addr.sin6_port = htons(port);
    internal_addr.sin6_family = domain;
    if (inet_pton(AF_INET6, ip_addr, &(internal_addr.sin6_addr)) <= 0)
      return -1;
    return bind(socket, (const struct sockaddr *)&internal_addr,
                sizeof(internal_addr));
  }
  default:
    return -1;
  }
}

bool tinytcp_server_listen(tinytcp_common_socket_t socket, int backlog) {
  return listen(socket, backlog) == 0;
}

tinytcp_common_socket_t tinytcp_server_accept(tinytcp_common_socket_t socket,
                                              char *restrict out,
                                              tinytcp_common_socklen_t outlen,
                                              uint16_t *restrict port) {
  struct sockaddr_storage storage = {0};
  int storagelen = sizeof(storage); // Windows accept uses int* for length

  tinytcp_common_socket_t client =
      accept(socket, (struct sockaddr *)&storage, &storagelen);

  if (client == TINYTCP_COMMON_INVALID_SOCKET)
    return TINYTCP_COMMON_INVALID_SOCKET;

  switch (storage.ss_family) {
  case AF_INET: {
    struct sockaddr_in *addr = (struct sockaddr_in *)&storage;
    if (out)
      inet_ntop(AF_INET, &(addr->sin_addr), out,
                outlen); // Fix: Pointer to field
    if (port)
      *port = ntohs(addr->sin_port); // Fix: Flip bytes
    break;
  }
  case AF_INET6: {
    struct sockaddr_in6 *addr6 = (struct sockaddr_in6 *)&storage;
    if (out)
      inet_ntop(AF_INET6, &(addr6->sin6_addr), out,
                outlen); // Fix: Pointer to field
    if (port)
      *port = ntohs(addr6->sin6_port); // Fix: Flip bytes
    break;
  }
  default:
    return TINYTCP_COMMON_INVALID_SOCKET;
  }
  return client;
}
