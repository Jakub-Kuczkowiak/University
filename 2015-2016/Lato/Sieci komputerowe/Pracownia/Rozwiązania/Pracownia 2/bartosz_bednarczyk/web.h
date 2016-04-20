// Bartosz Bednarczyk (273 479)

#ifndef WEB_INCLUDED
#define WEB_INCLUDED 1

#include "utils.h"
#include "networkinfo.h"

class Web
{
  public:
    void initializeWebFromIO();
    void printDistanceVector(int roundNumber);
    void sendVectorToAllAdjacentNetworks(int roundNumber);
    void receivePacketAndUpdateVector(int roundNumber);
    void setVia(string via);
    void setDistance(int distance);
    Web();
   ~Web();

  private:
    vector<NetworkInfo> adjacentNetworks;
    vector<int> sockets;
    vector<struct sockaddr_in> addresses;
    map<string, NetworkInfo> distanceVector;
    size_t numberOfNetworks;
    void cleanVector(int roundNumber);
    void initializeSocket(int &sockfd, NetworkInfo &network);
    string vectorToStringOfPackets();
    void updateVector(string senderip, string ip, int netmask, int distance, int roundNumber);
};

#endif