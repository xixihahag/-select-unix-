#include "unp.h"

void str_cli(FILE* fp, int sockfd){
  int maxfdp1, stdineof;
  fd_set rset;

  FD_ZERO(&rset);

  int n1, n2;
  char buf[MAXLINE];
  for(;;){
    if(stdineof != 1)
      FD_SET(fileno(fp), &rset);
    FD_SET(sockfd, &rset);
    maxfdp1 = max(sockfd, fileno(fp)) + 1;
    select(maxfdp1, &rset, NULL, NULL, NULL);

    if(FD_ISSET(fileno(fp), &rset)){
      if( (n1 = read(fileno(fp), buf, MAXLINE)) == 0){
        stdineof = 1;
        shutdown(sockfd, SHUT_WR);
        FD_CLR(fileno(fp), &rset);
        continue;
      }
      write(sockfd, buf, n1);
    }


    if(FD_ISSET(sockfd, &rset)){
      if( (n2 = read(sockfd, buf, MAXLINE)) == 0){
        if(stdineof == 1)
          return;
        else
          printf("read sockfd error\n");
          //提示出错
      }

      write(fileno(stdout), buf ,n2);
    }

  }

}
