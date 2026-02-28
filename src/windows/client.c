#include "client.h"
#include "common.h"
#include <ws2tcpip.h>

bool tinytcp_client_connect(tinytcp_common_socket_t socket,
                            const char *restrict ip_addr, uint16_t port,
                            int domain) {
  switch (domain) {
  case AF_INET: {
    struct sockaddr_in addr = {0};
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, ip_addr, &(addr.sin_addr)) <= 0)
      return false;
    return connect(socket, (const struct sockaddr *)&addr, sizeof(addr)) == 0;
  }
  case AF_INET6: {
    struct sockaddr_in6 addr = {0};
    addr.sin6_port = htons(port);
    addr.sin6_family = AF_INET6;
    if (inet_pton(AF_INET6, ip_addr, &(addr.sin6_addr)) <= 0)
      return false;
    return connect(socket, (const struct sockaddr *)&addr, sizeof(addr)) == 0;
  }
  default:
    return false;
  }
}
