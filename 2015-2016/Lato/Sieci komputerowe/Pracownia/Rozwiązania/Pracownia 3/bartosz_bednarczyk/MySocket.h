  // Bartosz Bednarczyk 273 479

#ifndef MYSOCKET_INCLUDED
#define MYSOCKET_INCLUDED 1

#include "utils.h"

class MySocket
{
  public:

  MySocket(int port, string ip);
  ~MySocket();
  void initializeSocket();
  void sendMessage(string message);
  pair<int, string> getMessage();

  private:
    int sockfd;
    int APPLICATION_PORT;
    string APPLICATION_IP;
    struct sockaddr_in server_address;
};

#endif