#ifndef TINYTCP_SERVER_H
#define TINYTCP_SERVER_H

#include "common.h"
#include "shared.h"
#include <stdint.h>

TINYTCP_SHARED_API int tinytcp_server_bind(tinytcp_common_socket_t socket,
                                           const char *restrict ip_addr,
                                           uint16_t port, int domain);

TINYTCP_SHARED_API bool tinytcp_server_listen(tinytcp_common_socket_t socket,
                                              int backlog);

TINYTCP_SHARED_API tinytcp_common_socket_t
tinytcp_server_accept(tinytcp_common_socket_t socket, char *restrict out,
                      tinytcp_common_socklen_t outlen, uint16_t *restrict port);

#endif // TINYTCP_SERVER_H
