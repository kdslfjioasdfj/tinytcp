#include "common.h"

int tinytcp_common_startup(void) {
  WSADATA internal_wsa;
  return WSAStartup(MAKEWORD(2, 2), &internal_wsa);
}

int tinytcp_common_cleanup(void) { return WSACleanup(); }

tinytcp_common_socket_t tinytcp_common_socket(int domain, int protocol) {
  return socket(domain, SOCK_STREAM, protocol);
}

bool tinytcp_common_closesocket(tinytcp_common_socket_t socket) {
  return closesocket(socket) != SOCKET_ERROR;
}

tinytcp_common_ssize_t tinytcp_common_send(tinytcp_common_socket_t socket,
                                           const void *restrict data,
                                           size_t len) {
  return send(socket, (const char *)data, len, 0);
}

tinytcp_common_ssize_t tinytcp_common_recv(tinytcp_common_socket_t socket,
                                           void *restrict buf, size_t len) {
  return recv(socket, (char *)buf, len, 0);
}
