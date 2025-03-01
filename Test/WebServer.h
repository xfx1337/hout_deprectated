#ifndef  WEBSERVER_H
#define WEBSERVER_H

#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

#include <iostream>
#include <string>
#include <thread>
#include <sstream>
#include <future>
#include <math.h>

void ServerThread();

#endif