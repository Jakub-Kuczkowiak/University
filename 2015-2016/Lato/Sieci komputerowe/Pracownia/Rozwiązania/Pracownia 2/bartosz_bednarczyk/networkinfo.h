// Bartosz Bednarczyk (273 479)

#ifndef NETWORKINFO_INCLUDED
#define NETWORKINFO_INCLUDED 1

#include "utils.h"

class NetworkInfo
{
  public:
    NetworkInfo(string unparsedData);
    NetworkInfo(string ip, string via, int netmask, int distance, int round);
    NetworkInfo();
    void print();
    string getIP();
    string getVia();
    int getNetmask();
    int getDistance();
    int getRound();
    string getWebAddress();
    string getBroadcast();
    void setVia(string via);
    void setDistance(int distance);
    void setRound(int round);

  private:
    string ip, via, webAddress, broadcast;
    int distance, netmask, round;
};

#endif
