#include <netinet/ip.h>
#include <netinet/udp.h>

#include "dgram_inet.h"

int main() {
  int sfd;
  struct sockaddr_in saddr;
  int flag = 1;

  if ((sfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP)) < 0) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  if (setsockopt(sfd, IPPROTO_IP, IP_HDRINCL, &flag, sizeof(flag)) < 0) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }

  memset(&saddr, 0, sizeof(saddr));
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(PORT);
  saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  while (1) {
    char udp_packet[BUF_SIZE];

    struct iphdr* ipheader = (struct iphdr*)udp_packet;
    ipheader->version = 4;
    ipheader->ihl = 5;
    ipheader->tos = 0; // DS
    ipheader->tot_len = 0; // auto
    ipheader->id = 0; // auto
    ipheader->frag_off = 0;
    ipheader->ttl = 255;
    ipheader->protocol = IPPROTO_UDP; // 17
    ipheader->check = 0; // auto
    ipheader->saddr = 0; // auto
    ipheader->daddr = inet_addr("127.0.0.1");

    /* Skip IP header */
    struct udphdr* header = (struct udphdr*)(udp_packet + 20);

    header->uh_sport = htons(9999);
    header->uh_dport = htons(PORT);
    header->uh_sum = 0;

    printf("Client: ");
    char buf[BUF_SIZE];
    fgets(buf, BUF_SIZE, stdin);

    header->uh_ulen = htons(sizeof(struct udphdr) + strlen(buf));

    /* Skip header and fill payload */
    strcpy(udp_packet + sizeof(struct udphdr) + sizeof(struct iphdr), buf);

    sendto(sfd, udp_packet, header->uh_ulen + sizeof(struct iphdr), 0,
           (struct sockaddr*)&saddr, sizeof(saddr));

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
