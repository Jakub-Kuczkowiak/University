// Bartosz Bednarczyk (273 479)

#ifndef UTILS_INCLUDED
#define UTILS_INCLUDED 1

#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <map>
#include <cassert>
#include <exception>
#include <system_error>
#include <bitset>

// Network stuff
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

using namespace std;

const int WAITING_TIME = 15 * 1000;
const int APPLICATION_PORT = 56969;
const int INFITITY = 10000;
const int ROUNDSLIMITUNREACHABLE = 3;
const int ROUNDSLIMITDELETE = 5;


int getElapsedTime(chrono::steady_clock::time_point &start);
string generateWebAddress(string ip, int netmask);
string generateBroadcast(string ip, int netmask);

tuple<string, int, int> fromPacket(string packet);
string toPacket(string ip, char netmask, unsigned int dist);

#endif