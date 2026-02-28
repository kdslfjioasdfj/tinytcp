#ifndef TINYTCP_COMMON_H
#define TINYTCP_COMMON_H

#include "shared.h"
#include <limits.h>
#include <stdbool.h>

#ifdef _WIN32
// Windows code here

// Platform-specific headers
#include <winsock2.h>

// Platform indicator macros
#define TINYTCP_CONFIG_WINDOWS 1
#define TINYTCP_CONFIG_POSIX 0

// Platform-specific types
typedef int tinytcp_common_socklen_t;
typedef int tinytcp_common_ssize_t;
typedef SOCKET tinytcp_common_socket_t;

// Platform-specific constants
#define TINYTCP_COMMON_SSIZE_MAX ((int)INT_MAX)
#define TINYTCP_COMMON_INVALID_SOCKET (INVALID_SOCKET)
#else
// POSIX code here

// Platform-specific headers
#include <sys/socket.h>
#include <sys/types.h>

// Platform indicator macros
#define TINYTCP_CONFIG_WINDOWS 0
#define TINYTCP_CONFIG_POSIX 1

// Platform-specific types
typedef socklen_t tinytcp_common_socklen_t;
typedef ssize_t tinytcp_common_ssize_t;
typedef int tinytcp_common_socket_t;

// Platform-specific constants
#define TINYTCP_COMMON_SSIZE_MAX ((ssize_t)SSIZE_MAX)
#define TINYTCP_COMMON_INVALID_SOCKET ((int)-1)
#endif // _WIN32

TINYTCP_SHARED_API int tinytcp_common_startup(void);

TINYTCP_SHARED_API int tinytcp_common_cleanup(void);

TINYTCP_SHARED_API tinytcp_common_socket_t tinytcp_common_socket(int domain,
                                                                 int protocol);

TINYTCP_SHARED_API bool
tinytcp_common_closesocket(tinytcp_common_socket_t socket);

TINYTCP_SHARED_API tinytcp_common_ssize_t tinytcp_common_send(
    tinytcp_common_socket_t socket, const void *restrict data, size_t len);

TINYTCP_SHARED_API tinytcp_common_ssize_t tinytcp_common_recv(
    tinytcp_common_socket_t socket, void *restrict buf, size_t len);

#endif // TINYTCP_COMMON_H
