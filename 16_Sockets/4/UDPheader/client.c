#include "dgram_inet.h"
#include <netinet/udp.h>

int main() {
  int sfd;
  struct sockaddr_in saddr;

  if ((sfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP)) < 0) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  memset(&saddr, 0, sizeof(saddr));
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(PORT);
  saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  while (1) {
    char udp_packet[BUF_SIZE];

    /* Header-type pointer to beggining of the packet to fill */
    struct udphdr* header = (struct udphdr*)udp_packet;

    header->uh_sport = htons(9999);
    header->uh_dport = htons(PORT);
    header->uh_sum = 0;

    printf("Client: ");
    char buf[BUF_SIZE];
    fgets(buf, BUF_SIZE, stdin);

    header->uh_ulen = htons(sizeof(struct udphdr) + strlen(buf));

    /* Skip header and fill payload */
    strcpy(udp_packet + sizeof(struct udphdr), buf);

    sendto(sfd, udp_packet, header->uh_ulen, 0, (struct sockaddr*)&saddr,
           sizeof(saddr));

    if (strncmp(buf, "exit", 4) == 0) break;

    while (1) {  // Receiving all udp packets
			memset(udp_packet, 0, BUF_SIZE);
      recvfrom(sfd, udp_packet, BUF_SIZE, 0, NULL, NULL);

      /* Skip IP header (20 bytes) and src port (2 bytes) */
      if (*((u_int16_t*)(udp_packet + 22)) == ntohs(9999)) {
        printf("Server: %s\n", udp_packet + 28);
        break;
      }
    }
  }

  close(sfd);

  exit(EXIT_SUCCESS);
}
