// Bartosz Bednarczyk (273 479)

#include "networkinfo.h"

string NetworkInfo::getIP() {
  return this->ip;
}

string NetworkInfo::getVia() {
  return this->via;
}

void NetworkInfo::setVia(string via) {
  this->via = via;
}

int NetworkInfo::getNetmask() {
  return this->netmask;
}

int NetworkInfo::getDistance() {
  return this->distance;
}

void NetworkInfo::setDistance(int distance) {
  this->distance = distance;
}

string NetworkInfo::getWebAddress() {
  return this->webAddress;
}

string NetworkInfo::getBroadcast() {
  return this->broadcast;
}

int NetworkInfo::getRound() {
  return this->round;
}

void NetworkInfo::setRound(int round) {
  this->round = round;
}

NetworkInfo::NetworkInfo(string ip, string via, int netmask, int distance, int round) {
  this->ip = ip;
  this->via = via;
  this->netmask = netmask;
  this->distance = distance;
  this->webAddress = generateWebAddress(ip, netmask);
  this->broadcast = generateBroadcast(ip, netmask);
  this->round = round;
}

void NetworkInfo::print() {
  cout << "----------------------------------\n";
  cout << "IP = " << this->ip << "\n";
  cout << "VIA = " << this->via << "\n";
  cout << "NETMASK = " << this->netmask << "\n";
  cout << "DISTANCE = " << this->distance << "\n";
}

NetworkInfo::NetworkInfo() {
  this->ip = this->via = "";
  this->netmask = this->distance = this->round = 0;
}

// example : "10.0.1.1 netmask /8 distance 3"
// asumption : unparsedData is valid

NetworkInfo::NetworkInfo(string unparsedData) {
  stringstream aStringStream(unparsedData);
  vector<string> splitData(5);
  for(size_t i = 0; i < 5; i++) {
    aStringStream >> splitData[i];
  }
  splitData[2].erase(0,1);
  this->ip = splitData[0];
  this->netmask = stoi(splitData[2]);
  this->via = "connected directly";
  this->distance = stoi(splitData[4]);
  this->webAddress = generateWebAddress(ip, netmask);
  this->broadcast = generateBroadcast(ip, netmask);
  this->round = 0;
}

