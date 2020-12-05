#include "Socket.h"

/***********************************************************************************************/

/**
 * Primary Constructor For The Socket
 * @param [port]            - The socket port number
 * @param [numberOfClients] - The max number of clients that are allowed to connect
 */
Socket::Socket(int port) {
    this->port = port;

    // Creates The Socket//
    fileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (fileDescriptor < 0) {
        fatal("Socket: Can't create socket");
    }

    // Sets The Socket Info//
    info.sin_family = AF_INET;
    info.sin_port = htons(port);
    info.sin_addr.s_addr = INADDR_ANY;

    // Gets The Hostname//
    gethostname(host, 256);
}

/**
 * Function That Connects A Client To The Server
 * @param [socketHost] - The host of the server
 * @param [socketPort] - The port of the server
 */
void Socket::connect(const char* socketHost, int socketPort) {

    // Gets The Remote Host//
    struct hostent *remoteHost = gethostbyname(socketHost);
    if (remoteHost == nullptr) {
        cout << "Socket: unknown host [" << host << "]" << endl;
        exit(1);
    }

    // Copies The Info About The Host And Port//
    memmove(&info.sin_addr, remoteHost->h_addr_list[0], remoteHost->h_length);
    info.sin_port = htons(socketPort);

    // Shows That The Client Socket Is Attempting To Connect To Ther Server Socket//
    cout << "Ready to connect socket [" << fileDescriptor << "] to [" << host << "]" << endl;

    // Attempts To Connect To The Server Socket//
    int status = ::connect( fileDescriptor, (sockaddr*)&info, sizeof info );
    if (status < 0) {
        cout << "Socket: The connection [" << host << "] was refused" << endl;
        exit(1);
    }

    // Shows That The Connection Was Established Successfully//
    cout << "Socket: connection established to [" << host << "]" << endl;
}

/***********************************************************************************************/

/**
 * Function That Gets The File Descriptor
 * @return Returns the file descriptor
 */
int Socket::getfileDescriptor() const {
    return fileDescriptor;
}

/**
 * Prints The Socket Info
 * @param [out] - The output stream
 * @return The socket info
 */
ostream &Socket::print(ostream& out) {
    out << "{" << endl;
    out << "  sin_addr.s_addr = " << inet_ntoa(info.sin_addr) << endl;
    out << "  sin_port = " << ntohs(info.sin_port) << endl;
    out << "}" << endl;
    return out;
}

/***********************************************************************************************/