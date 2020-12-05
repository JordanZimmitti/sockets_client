#pragma once
#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <zconf.h>
#include <poll.h>
#include "tools.hpp"
using namespace std;

/**
 * Class For Handling The Sockets
 */
class Socket {

private:

    // Base Socket Variables//
    char host[256] {};
    int  fileDescriptor = -1;
    int  port = 0;
    sockaddr_in info = {0};

public:

    // Constructor//
    explicit Socket(int port);

    // Inline Functions//
    int getfileDescriptor() const;

    // Normal Functions//
    void connect(const char* host, int port);
    ostream& print(ostream& out);
};

// Overload '<<' For Cout To Work//
inline ostream& operator <<(ostream& out, Socket &socket) {
    return socket.print(out);
}