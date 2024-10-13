#include <linux/if_packet.h>
#include <net/if.h>
#include <netinet/ether.h>
#include <netinet/ip.h>
#include <netinet/udp.h>

#include "dgram_inet.h"

unsigned short checksum(void* b, int len) {
  unsigned short* buf = b;
  unsigned int sum = 0;
  unsigned short result;

  for (sum = 0; len > 1; len -= 2) {
    sum += *buf++;
  }
  if (len == 1) {
    sum += *(unsigned char*)buf;
  }
  sum = (sum >> 16) + (sum & 0xFFFF);
  sum += (sum >> 16);
  result = ~sum;
  return result;
}

int main() {
  int sfd;
  struct sockaddr_ll saddr;

  if ((sfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  unsigned char dstmac[6] = {0x08, 0x00, 0x27, 0xfe, 0x26, 0x02};
  unsigned char srcmac[6] = {0xd8, 0x43, 0xae, 0x29, 0x37, 0xaa};

  memset(&saddr, 0, sizeof(saddr));
  saddr.sll_family = AF_PACKET;
  saddr.sll_ifindex = if_nametoindex("enp34s0");
  saddr.sll_halen = ETH_ALEN;
  memcpy(saddr.sll_addr, dstmac, 6);

  while (1) {
    printf("Client: ");
    char buf[BUF_SIZE];
    fgets(buf, BUF_SIZE, stdin);

    char udp_packet[BUF_SIZE];

    /* Skip IP header */
    struct udphdr* udpheader = (struct udphdr*)(udp_packet + 34);
    udpheader->uh_sport = htons(9999);
    udpheader->uh_dport = htons(PORT);
    udpheader->uh_sum = 0;
    udpheader->uh_ulen = htons(sizeof(struct udphdr) + strlen(buf));

    struct iphdr* ipheader = (struct iphdr*)(udp_packet + 14);
    ipheader->version = 4;
    ipheader->ihl = 5;
    ipheader->tos = 0;              // DS
    ipheader->tot_len = htons(29);  // auto
    ipheader->id = 12313;           // auto
    ipheader->frag_off = 0;
    ipheader->ttl = 255;
    ipheader->protocol = IPPROTO_UDP;             // 17
    ipheader->check = 0;                          // auto
    ipheader->saddr = inet_addr("192.168.0.63");  // auto
    ipheader->daddr = inet_addr("192.168.0.16");
    ipheader->check = checksum((unsigned short*)ipheader, 20);  // auto

    struct ether_header* ethheader = (struct ether_header*)udp_packet;
    memcpy(ethheader->ether_dhost, dstmac, 6);
    memcpy(ethheader->ether_shost, srcmac, 6);
    ethheader->ether_type = htons(ETH_P_IP);

    /* Skip header and fill payload */
    strcpy(udp_packet + sizeof(struct udphdr) + sizeof(struct iphdr) +
               sizeof(struct ether_header),
           buf);

    sendto(sfd, udp_packet,
           sizeof(struct ether_header) + sizeof(struct iphdr) +
               sizeof(struct udphdr) + strlen(buf),
           0, (struct sockaddr*)&saddr, sizeof(saddr));

    if (strncmp(buf, "exit", 4) == 0) break;

    while (1) {  // Receiving all udp packets
      memset(udp_packet, 0, BUF_SIZE);
      recvfrom(sfd, udp_packet, BUF_SIZE, 0, NULL, NULL);

      /* Skip IP header (20 bytes) and src port (2 bytes) */
      if (*((u_int16_t*)(udp_packet + 36)) == ntohs(9999)) {
        printf("Server: %s\n", udp_packet + 42);
        break;
      }
    }
  }

  close(sfd);

  exit(EXIT_SUCCESS);
}
