#include "unp.h"

int main(int argc, char const *argv[]) {
  int listenfd;
  struct sockaddr_in servaddr;

  listenfd = socket(AF_INET, SOCK_STREAM, 0);

  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(SERV_PORT);
  inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

  connect(listenfd, (SA*)&servaddr, sizeof(servaddr));

  str_cli(stdin, listenfd);

  return 0;
}
