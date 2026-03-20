#include "client.h"
#include "common.h"
#include <stdint.h>
#include <stdio.h>

/*
  Notes:
  This uses port 8080 and connects to IPv4 "127.0.0.1" (localhost).
  First, it accepts a "length byte."
  Then, it sends a confirmation byte that it received the length.
  Then, it receives the data payload.
  Finally, it prints the data it received.
*/
int main(void) {
  // Initialize TinyTCP
  if (tinytcp_common_startup() != 0)
    // Could not initialize TinyTCP
    return 1;
  tinytcp_common_socket_t sock = tinytcp_common_socket(AF_INET, 0);

  // Obtain an OS socket
  if (sock == TINYTCP_COMMON_INVALID_SOCKET) {
    // Could not obtain socket
    tinytcp_common_cleanup();
    return 2;
  }

  // Connect the socket to localhost
  if (!tinytcp_client_connect(sock, "127.0.0.1", 8080, AF_INET)) {
    // Connection failed
    tinytcp_common_closesocket(sock);
    tinytcp_common_cleanup();
    return 3;
  }

  // Receive length byte
  uint8_t len_byte;
  tinytcp_common_ssize_t recved = tinytcp_common_recv(sock, &len_byte, 1);
  switch (recved) {
  case -1: {
    // Could NOT receive length byte
    tinytcp_common_closesocket(sock);
    tinytcp_common_cleanup();
    return 4;
  }
  case 0: {
    // Peer performed an orderly shutdown
    tinytcp_common_closesocket(sock);
    tinytcp_common_cleanup();
    return 5;
  }
  default:
    break; // Received length byte!
  }

  // Send confirmation byte
  uint8_t confirmation_byte = 0xFF;
  tinytcp_common_ssize_t sent =
      tinytcp_common_send(sock, &confirmation_byte, 1);
  while (sent < 1) {
    if (sent == -1) {
      // Could NOT send confirmation byte
      tinytcp_common_closesocket(sock);
      tinytcp_common_cleanup();
      return 6;
    }
    // This case is rare in blocking TCP sockets: Could not send any bytes but
    // there was no error
    sent = tinytcp_common_send(sock, &confirmation_byte, 1);
  }

  // Receive payload
  uint8_t payload[0xFF] = {0};
  tinytcp_common_ssize_t cur = tinytcp_common_recv(sock, payload, len_byte);
  tinytcp_common_ssize_t total = cur;
  while (total < len_byte) {
    switch (cur) {
    case -1: {
      // Could not receive payload
      tinytcp_common_closesocket(sock);
      tinytcp_common_cleanup();
      return 7;
    }
    case 0: {
      // Peer did orderly shutdown
      tinytcp_common_closesocket(sock);
      tinytcp_common_cleanup();
      return 8;
    }
    default:
      break;
    }
    cur = tinytcp_common_recv(sock, payload + total, len_byte - total);
    total += cur;
  }

  // Now, we print the bytes
  printf("Received %u bytes: 0x", len_byte);
  for (size_t i = 0; i < len_byte; i++)
    printf("%x", payload[i]);
  puts(".");

  tinytcp_common_closesocket(sock);
  tinytcp_common_cleanup();
  return 0;
}
