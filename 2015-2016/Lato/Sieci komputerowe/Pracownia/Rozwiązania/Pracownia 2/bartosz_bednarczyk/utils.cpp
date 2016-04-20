// Bartosz Bednarczyk (273 479)

#include "utils.h"

int getElapsedTime(chrono::steady_clock::time_point &start) {
  chrono::steady_clock::time_point end = chrono::steady_clock::now();
  typedef std::chrono::duration<int,std::milli> millisecs_t;
  millisecs_t duration( chrono::duration_cast<millisecs_t>(end-start) );
  return (int) duration.count();
}


// generates web address in form x.y.z.t from given ip and netmask
string generateWebAddress(string ip, int netmask) {
  for(size_t i = 0; i < ip.size(); i++) {
    if(ip[i] == '.') ip[i] = ' ';
  }

  int octets[4];
  string response = "", temp;
  stringstream stream(ip);
  
  for(size_t i = 0; i < 4; i++) {
    stream >> temp;
    octets[i] = stoi(temp);
    if(netmask > 8) netmask -= 8;
    else {
      octets[i] >>= (8-netmask);
      octets[i] <<= (8-netmask);
      netmask = 0;
    }
    response += to_string(octets[i]);
    if(i != 3) response += ".";
  }

  return response;
}

// generates broadcast in form x.y.z.t from given ip and netmask
string generateBroadcast(string ip, int netmask) {
  for(size_t i = 0; i < ip.size(); i++) {
    if(ip[i] == '.') ip[i] = ' ';
  }

  int octets[4];
  string response = "", temp;
  stringstream stream(ip);
  
  for(size_t i = 0; i < 4; i++) {
    stream >> temp;
    octets[i] = stoi(temp);
  }

  int bitsTODO = 32-netmask;

  for(int i = 3; i >= 0; i--) {
    if(bitsTODO == 0) break;
    else if(bitsTODO >= 8) {
      octets[i] = 255;
      bitsTODO -= 8;
    }
    else {
      for(size_t j = 0; j < (size_t) bitsTODO; j++) {
        octets[i] |= (1 << j);
      }
      bitsTODO = 0;
    }
  }

  return "" + to_string(octets[0]) + "." + to_string(octets[1]) + "." + to_string(octets[2]) + "." + to_string(octets[3]);
}

string toPacket(string ip, char netmask, unsigned int dist) {
  for(size_t i = 0; i < ip.size(); i++) {
    if(ip[i] == '.') ip[i] = ' ';
  }

  stringstream stream(ip);
  string answer(" ", 7);

  for(size_t i = 0; i < 4; i++) {
    string temp;
    stream >> temp;
    answer[i] = stoi(temp);
  }

  answer[4] = netmask;
  answer[5] = dist / 256;
  answer[6] = dist % 256;
  return answer;
}

// (ip, netmask, dist)
tuple<string, int, int> fromPacket(string packet) {
  string ip = "";
  for(size_t i = 0; i < 3; i++) ip += to_string( (packet[i] >= 0 ? packet[i] : 256+packet[i]) ) + ".";
  ip += to_string(packet[3]);
  int netmask = packet[4];
  unsigned int dist = ( (packet[6] >= 0 ? packet[6] : 256+packet[6]) ) + 256 * ( (packet[5] >= 0 ? packet[5] : 256+packet[5]) );
  tuple<string, int, int> answer(ip, netmask, dist);
  return answer;
}