// Bartosz Bednarczyk (273 479)
#include "web.h"

Web::Web() {
}

Web::~Web() {
  for(size_t i = 0; i < sockets.size(); i++) close(sockets[i]);
}

void Web::initializeWebFromIO() {
  cin >> numberOfNetworks; cin.ignore();
  sockets.resize(numberOfNetworks);
  adjacentNetworks.resize(numberOfNetworks);

  for(size_t i = 0; i < numberOfNetworks; i++) {
    string unparsedData; getline(cin, unparsedData);
    NetworkInfo aNetworkInfo(unparsedData);
    adjacentNetworks[i] = aNetworkInfo;
    initializeSocket(sockets[i], adjacentNetworks[i]);
    distanceVector[aNetworkInfo.getWebAddress()] = aNetworkInfo;
  }
}

void Web::initializeSocket(int &sockfd, NetworkInfo &network) {
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) {
    cerr << "Socket creation exception.\n";
    throw new runtime_error("Socket creation exception.");
  }

  struct sockaddr_in server_address;
  bzero (&server_address, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(APPLICATION_PORT);
  inet_pton(AF_INET, generateBroadcast(network.getIP(), network.getNetmask()).c_str(), &server_address.sin_addr);
  int broadcastPermission = 1;
  setsockopt (sockfd, SOL_SOCKET, SO_BROADCAST, (void *)&broadcastPermission, sizeof(broadcastPermission));

  // cout << "IP = " << network.getIP() << " NETMASK = " << network.getNetmask() << " BROADCAST = " << generateBroadcast(network.getIP(), network.getNetmask()) << "\n";

  if (bind (sockfd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
    cerr << "Bind error : " << strerror(errno) << "\n";
    throw new runtime_error("Bind error."); 
  }

  addresses.push_back(server_address);
}

// Example :
//10.0.0.0/8 unreachable
//192.168.2.0/24 distance 4 via 192.168.5.5
// 192.168.5.0/24 distance 2 connected directly

void Web::printDistanceVector(int roundNumber) {
  for(auto it = distanceVector.begin(); it!=distanceVector.end(); ++it) {
    if(it->second.getVia() == "unreachable" || abs(it->second.getRound() - roundNumber) >= ROUNDSLIMITDELETE ) {
      continue;
    }
    else if(it->second.getVia() == "unreachable" || abs(it->second.getRound() - roundNumber) >= ROUNDSLIMITUNREACHABLE ) {
      cout << it->second.getWebAddress() << "/" << it->second.getNetmask() << " unreachable, received at round " << it->second.getRound() << ".\n";
    }
    else {
      cout << it->second.getWebAddress() << "/" << it->second.getNetmask() << ", distance ";
      cout << it->second.getDistance() << ", " << it->second.getVia() << ", received at round " << it->second.getRound() << ".\n";
    }
  }

  cleanVector(roundNumber);
}

void Web::cleanVector(int roundNumber) {
    vector<string> toDelete;
    for(auto it = distanceVector.begin(); it!=distanceVector.end(); ++it) {
      if(it->second.getVia() == "unreachable" || abs(it->second.getRound() - roundNumber) >= ROUNDSLIMITDELETE ) {
        toDelete.push_back(it->second.getWebAddress());
      }
      else if(it->second.getVia() == "unreachable" || abs(it->second.getRound() - roundNumber) >= ROUNDSLIMITUNREACHABLE ) {
        it->second.setDistance(INFITITY);
      }
    }

    for(size_t i = 0; i < toDelete.size(); i++) {
      distanceVector.erase(toDelete[i]);
    }
}

string Web::vectorToStringOfPackets() {
  string response = "";
  for(auto it = distanceVector.begin(); it!=distanceVector.end(); ++it) {
    response += toPacket(it->second.getWebAddress(), it->second.getNetmask(), it->second.getDistance());
  }
  return response;
}

void Web::sendVectorToAllAdjacentNetworks(int roundNumber) {
  string message = vectorToStringOfPackets();

  for(size_t i = 0; i < adjacentNetworks.size(); i++) {
    if (sendto(sockets[i], message.c_str(), message.size(), 0, (struct sockaddr*) &addresses[i], sizeof(addresses[i])) != (int) message.size()) {
      NetworkInfo currentNetworkInfo = distanceVector[adjacentNetworks[i].getWebAddress()];
      NetworkInfo updatedNetworkInfo = NetworkInfo(currentNetworkInfo.getIP(), "unreachable", currentNetworkInfo.getNetmask(), INFITITY, roundNumber);
      distanceVector[adjacentNetworks[i].getWebAddress()] = updatedNetworkInfo;
    }
    else {
      auto iter = distanceVector.find(adjacentNetworks[i].getWebAddress());

      if(iter == distanceVector.end() || distanceVector[adjacentNetworks[i].getWebAddress()].getDistance() >= adjacentNetworks[i].getDistance()) {
        distanceVector[adjacentNetworks[i].getWebAddress()] = adjacentNetworks[i];
        distanceVector[adjacentNetworks[i].getWebAddress()].setRound(roundNumber);
      }
    }
  }
}

void Web::receivePacketAndUpdateVector(int roundNumber) {
  for(size_t i = 0; i < adjacentNetworks.size(); i++) {
    struct sockaddr_in sender; 
    socklen_t sender_len = sizeof(sender);
    char buffer[IP_MAXPACKET+1];
    ssize_t datagram_len = recvfrom (sockets[i], buffer, IP_MAXPACKET, MSG_DONTWAIT , (struct sockaddr*)&sender, &sender_len);
    if (datagram_len < 0) continue;

    char sender_ip[20];
    inet_ntop(AF_INET, &(sender.sin_addr), sender_ip, sizeof(sender_ip));

    for(int j = 0; j < datagram_len; j += 7) {
      string str_packet = "";
      for(size_t k = 0; k < 7; k++) str_packet += buffer[j+k];
      tuple<string, int, int> packet = fromPacket(str_packet);
      //cout << "GET : IP = " << get<0>(packet) << " NETMASK = " << get<1>(packet) << " DIST = " << get<2>(packet) << "\n";
      updateVector(string(sender_ip), get<0>(packet), get<1>(packet), get<2>(packet), roundNumber);
    }
  }
}

void Web::updateVector(string senderip, string ip, int netmask, int distance, int roundNumber)  {
  auto it = distanceVector.find( generateWebAddress(ip, netmask) );
  auto iter = distanceVector.end();
  int senderNetmask = 32;

  for(size_t i = 0; i < adjacentNetworks.size(); i++) {
    if(senderip == adjacentNetworks[i].getIP()) {
      distanceVector[ generateWebAddress(senderip, adjacentNetworks[i].getNetmask()) ].setRound(roundNumber);
      return;
    }
  }

  while(iter == distanceVector.end()) {
    iter = distanceVector.find( generateWebAddress(senderip, senderNetmask) );
    senderNetmask--;
  }

  int senderDistance = iter->second.getDistance();
  
  if(it != distanceVector.end()) {

    if(it->second.getDistance() >= (distance + senderDistance)) {
      it->second.setRound(roundNumber);
    }
    
    if(it->second.getDistance() > (distance + senderDistance)) {
      it->second.setDistance(distance + senderDistance);
      it->second.setVia("via " + senderip);
    }
  }
  else {
    NetworkInfo n(ip, "via " + senderip, netmask, distance + senderDistance, roundNumber);
    distanceVector.erase(generateWebAddress(ip, netmask));
    distanceVector[generateWebAddress(ip, netmask)] = n;
  }

}