#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

int main() {
  struct sockaddr_in serv_addr, client_addr;
  int sockfd, newsockfd;
  socklen_t clientlen;
  char msg[100] = {0};

  sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  bzero((char*)&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr("192.168.211.13");
  serv_addr.sin_port = htons(2345);
  bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
  listen(sockfd, 5);

  for (;;) {
    clientlen = sizeof(client_addr);
    newsockfd = accept(sockfd, (struct sockaddr*)&client_addr, &clientlen);
    pid_t childpid = fork();
    if (childpid == 0) {
      close(sockfd);
      write(newsockfd, "hai\n", 4);
      read(newsockfd, msg, 5);
      cout << msg << endl;
      exit(0); //free the resources
    }
    close(newsockfd);
  }
  return 0;
}
