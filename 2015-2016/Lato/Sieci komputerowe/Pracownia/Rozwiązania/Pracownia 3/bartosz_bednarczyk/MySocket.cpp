// Bartosz Bednarczyk (273 479)

#include "MySocket.h"

pair<int, string> getStartAndDataFromBuffer(char *buffer, size_t bufferSize) {
  string data = "";
  bool isData = false;

  for(size_t i = 0; i < bufferSize; i++) {
    if(isData) data += buffer[i];
    else if(buffer[i] == '\n') isData = true; 
  }

  string id = "";

  for(size_t i = 5; i < bufferSize; i++) {
    if(buffer[i] == ' ') break;
    else id += buffer[i];
  }

  return {stoi(id)/500, data};
}

MySocket::MySocket(int port, string ip) {
  this->APPLICATION_PORT = port;
  this->APPLICATION_IP = ip;
}

MySocket::~MySocket() {
  close(sockfd);
}

void MySocket::initializeSocket() {
  sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (sockfd < 0) {
    cerr << "Socket creation exception.\n";
    throw new runtime_error("Socket creation exception.");
  }

  bzero (&server_address, sizeof(server_address));
  server_address.sin_family = AF_INET;  
  server_address.sin_port = htons(APPLICATION_PORT);
  inet_pton(AF_INET, APPLICATION_IP.c_str(), &server_address.sin_addr);

  int isConnected = connect(sockfd, (struct sockaddr*) &server_address, sizeof(server_address));

  if (isConnected < 0) {
    cerr << "Sever connecting exception.\n";
    throw new runtime_error("Sever connecting exception.");
  }
}

void MySocket::sendMessage(string message) {
  int sendCheck = sendto(sockfd, message.c_str(), strlen(message.c_str()), 0, (struct sockaddr*)&server_address, sizeof(server_address));
  if(sendCheck < 0) {
    cerr << "Send error.\n";
    throw new runtime_error("Send error.");
  }
}

pair<int, string> MySocket::getMessage() {
  
  // https://support.sas.com/documentation/onlinedoc/sasc/doc700/html/lr2/select.htm
  fd_set fdset; FD_ZERO(&fdset); FD_SET(sockfd, &fdset);
  struct timeval time; time.tv_sec = 0; time.tv_usec = 2000;
  int selectResult = select(sockfd+1, &fdset, NULL, NULL, &time);

  if (selectResult < 0) {
    cerr << "Select error.\n";
    throw new runtime_error("Select error.");
  }
  else if (selectResult == 0) return {-1, ""};

  struct sockaddr_in sender; socklen_t senderSize = sizeof(sender);

  const int bufferSize = 10000;
  char buffer[bufferSize];
  int recvfromResult = recvfrom(sockfd, buffer, bufferSize, 0, (struct sockaddr*)&sender, &senderSize);

  if (recvfromResult < 0) {
    cerr << "Recvfrom error.\n";
    throw new runtime_error("Recvfrom error.");
  }

  char IP[20];
  inet_ntop(AF_INET, &(sender.sin_addr), IP, sizeof(IP));
  if (ntohs(sender.sin_port) != APPLICATION_PORT || string(IP) != APPLICATION_IP) return {-1, ""};
  return getStartAndDataFromBuffer(buffer, (size_t) recvfromResult);
}