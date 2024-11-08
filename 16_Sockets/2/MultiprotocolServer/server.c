#include "udp_tcp.h"

/* Only for one client */

int main() {
  int tcp_sock, udp_sock;
  struct sockaddr_in server_addr, client_addr;
  char buffer[BUF_SIZE];
  socklen_t addr_len = sizeof(client_addr);

  // Создание TCP сокета
  tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (tcp_sock < 0) {
    perror("TCP socket creation failed");
    exit(EXIT_FAILURE);
  }

  // Создание UDP сокета
  udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (udp_sock < 0) {
    perror("UDP socket creation failed");
    close(tcp_sock);
    exit(EXIT_FAILURE);
  }

  // Настройка адреса
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);

  // Привязка TCP сокета
  if (bind(tcp_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
      0) {
    perror("TCP bind failed");
    close(tcp_sock);
    close(udp_sock);
    exit(EXIT_FAILURE);
  }

  // Привязка UDP сокета
  if (bind(udp_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
      0) {
    perror("UDP bind failed");
    close(tcp_sock);
    close(udp_sock);
    exit(EXIT_FAILURE);
  }

  // Прослушивание TCP соединений
  listen(tcp_sock, 10);

  struct pollfd fds[MAX_EVENTS];
  fds[0].fd = tcp_sock;
  fds[0].events = POLLIN;
  fds[1].fd = udp_sock;
  fds[1].events = POLLIN;

  while (1) {
    int poll_count = poll(fds, 2, -1);
    if (poll_count < 0) {
      perror("poll failed");
      break;
    }

    // Проверка TCP соединений
    if (fds[0].revents & POLLIN) {
      int new_sock =
          accept(tcp_sock, (struct sockaddr *)&client_addr, &addr_len);
      if (new_sock < 0) {
        perror("accept failed");
        continue;
      }
      while (1) {
        int bytes_received = recv(new_sock, buffer, BUF_SIZE, 0);
        if (bytes_received < 0 || strcmp(buffer, "exit") == 0)
          break;
        buffer[bytes_received] = '\0';
        for (int i = 0; i < bytes_received; ++i)
          buffer[i] = toupper(buffer[i]);
        send(new_sock, buffer, bytes_received, 0);
      }
      close(new_sock);
    }

    // Проверка UDP соединений
    if (fds[1].revents & POLLIN) {
      while (1) {
        int bytes_received =
            recvfrom(udp_sock, buffer, BUF_SIZE, 0,
                     (struct sockaddr *)&client_addr, &addr_len);
        if (bytes_received < 0 || strcmp(buffer, "exit") == 0)
          break;
        buffer[bytes_received] = '\0';
        for (int i = 0; i < bytes_received; ++i)
          buffer[i] = toupper(buffer[i]);
        sendto(udp_sock, buffer, bytes_received, 0,
               (struct sockaddr *)&client_addr, addr_len);
      }
    }
  }

  close(tcp_sock);
  close(udp_sock);
  return 0;
}
