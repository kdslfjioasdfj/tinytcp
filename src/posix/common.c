#include "common.h"
#include <errno.h>
#include <signal.h>
#include <unistd.h>

void (*old_handler)(int) = NULL;

int tinytcp_common_startup(void) {
  old_handler = signal(SIGPIPE, SIG_IGN);
  if (old_handler == SIG_ERR)
    return -1;
  return 0;
}

int tinytcp_common_cleanup(void) {
  if (signal(SIGPIPE, old_handler) == SIG_ERR)
    return -1;
  return 0;
}

tinytcp_common_socket_t tinytcp_common_socket(int domain, int protocol) {
  return socket(domain, SOCK_STREAM, protocol);
}

bool tinytcp_common_closesocket(tinytcp_common_socket_t socket) {
  return close(socket) == 0;
}

tinytcp_common_ssize_t tinytcp_common_send(tinytcp_common_socket_t socket,
                                           const void *restrict data,
                                           size_t len) {
  tinytcp_common_ssize_t ret;
  for (;;) {
    ret = send(socket, data, len, 0);
    if (ret == -1 && errno == EINTR)
      continue;
    break;
  }
  return ret;
}

tinytcp_common_ssize_t tinytcp_common_recv(tinytcp_common_socket_t socket,
                                           void *restrict buf, size_t len) {
  tinytcp_common_ssize_t ret;
  for (;;) {
    ret = recv(socket, buf, len, 0);
    if (ret == -1 && errno == EINTR)
      continue;
    break;
  }
  return ret;
}
