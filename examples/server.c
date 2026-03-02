#include "server.h"
#include "common.h"
#include <stddef.h>
#include <stdint.h>

/*
  Notes:
  This sets up a minimal server on "127.0.0.1" (localhost) at port 8080.
  Upon receiving its first client, it sends a "length byte."
  Then, it waits for a "confirmation byte."
  Finally, it sends the payload.
*/
int main(void) {
  if (tinytcp_common_startup() != 0)
    return 1;

  tinytcp_common_socket_t sock = tinytcp_common_socket(AF_INET, 0);
  if (sock == TINYTCP_COMMON_INVALID_SOCKET) {
    // Could not obtain valid socket
    tinytcp_common_cleanup();
    return 2;
  }

  if (tinytcp_server_bind(sock, "127.0.0.1", 8080, AF_INET) != 0) {
    // Could not bind socket
    tinytcp_common_closesocket(sock);
    tinytcp_common_cleanup();
    return 3;
  }

  if (!tinytcp_server_listen(sock, 3)) {
    // Could not start listening on the socket
    tinytcp_common_closesocket(sock);
    tinytcp_common_cleanup();
    return 4;
  }

  tinytcp_common_socket_t client = tinytcp_server_accept(sock, NULL, 0, NULL);
  if (client == TINYTCP_COMMON_INVALID_SOCKET) {
    // Could not accept a client
    tinytcp_common_closesocket(sock);
    tinytcp_common_cleanup();
    return 5;
  }

  uint8_t len_byte = 16;
  uint8_t payload[16];
  for (size_t i = 0; i < len_byte; i++)
    payload[i] = (uint8_t)i;

  if (tinytcp_common_send(client, &len_byte, 1) != 1) {
    // Could not send length byte
    tinytcp_common_closesocket(client);
    tinytcp_common_closesocket(sock);
    tinytcp_common_cleanup();
    return 6;
  }

  uint8_t confirm_byte;
  tinytcp_common_ssize_t recved = tinytcp_common_recv(client, &confirm_byte, 1);

  if (recved == -1) {
    // Could not receive confirmation byte
    tinytcp_common_closesocket(client);
    tinytcp_common_closesocket(sock);
    tinytcp_common_cleanup();
    return 7;
  }

  if (recved == 0) {
    // Peer performed orderly shutdown
    tinytcp_common_closesocket(client);
    tinytcp_common_closesocket(sock);
    tinytcp_common_cleanup();
    return 8;
  }

  if (recved != 1) {
    // Could not receive confirmation byte
    tinytcp_common_closesocket(client);
    tinytcp_common_closesocket(sock);
    tinytcp_common_cleanup();
    return 9;
  }

  tinytcp_common_ssize_t total = 0;

  while (total < len_byte) {
    tinytcp_common_ssize_t cur =
        tinytcp_common_send(client, payload + total, len_byte - total);

    if (cur == -1) {
      // Could not send payload
      tinytcp_common_closesocket(client);
      tinytcp_common_closesocket(sock);
      tinytcp_common_cleanup();
      return 10;
    }

    total += cur;
  }

  tinytcp_common_closesocket(client);
  tinytcp_common_closesocket(sock);
  tinytcp_common_cleanup();
  return 0;
}