#include "Socket.h"
#include "Kid.h"
using namespace std;

int main(int argc, char* argv[]) {

    // Gets The Information Needed To Play Musical Chairs//
    char* host = argv[1];
    char* port = argv[2];
    char* name = argv[3];

    // Creates A Client Socket And Connects To The Server//
    Socket client(atoi(port));
    client.connect(host, atoi(port));
    int mom = client.getfileDescriptor();

    // Shows The Host And Port That The Client Connected To//
    cout <<"\nNew client on " << client << endl;

    // Starts The Musical Chairs Game//
    Kid kid(&mom, name);
    kid.run();

    // Ends Program//
    return 0;
}