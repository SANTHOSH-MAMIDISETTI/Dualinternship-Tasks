#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<cstring>

using namespace std;

int main() {
  int sockfd;
  struct sockaddr_in serv_addr;
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr("192.168.211.116");
  // serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  serv_addr.sin_port = htons(2345);
  sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
  char data[100] = {0};
  read(sockfd, data, 3);
  cout << data << endl;
  write(sockfd, "hello", 5);
  close(sockfd);
  return 0;
}
