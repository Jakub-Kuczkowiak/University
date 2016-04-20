// Bartosz Bednarczyk (273 479)

#include "utils.h"
#include "web.h"
using namespace std;

int main()
{
  try {
    Web web;
    web.initializeWebFromIO();
    cout << "ROUND 0\n";
    web.printDistanceVector(0);
    int roundNumber = 0;
    while(++roundNumber) {
      cout << "ROUND " << roundNumber << "\n";
      web.sendVectorToAllAdjacentNetworks(roundNumber);
      chrono::steady_clock::time_point start = chrono::steady_clock::now();
      while( getElapsedTime(start) < WAITING_TIME  ) {
        web.receivePacketAndUpdateVector(roundNumber);
      }
      web.printDistanceVector(roundNumber);
    }
  }
  catch(...) {
    cerr << "Program terminated due to exception.\n";
    return -1;
  }

  return 0;
}
