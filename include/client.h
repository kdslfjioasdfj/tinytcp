#ifndef TINYTCP_CLIENT_H
#define TINYTCP_CLIENT_H

#include "common.h"
#include "shared.h"
#include <stdbool.h>
#include <stdint.h>

TINYTCP_SHARED_API bool tinytcp_client_connect(tinytcp_common_socket_t socket,
                                               const char *restrict ip_addr,
                                               uint16_t port, int domain);

#endif // TINYTCP_CLIENT_H