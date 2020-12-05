#pragma once
#include <iostream>
#include <string>
#include <sys/poll.h>
using namespace std;

/**
 * Function That Handles The Kid Clients
 */
class Kid {

private:
    bool    isAlive = true;
    int     numberOfChairs = 0;
    int     round = 0;
    string  name;
    FILE*   kidToMom {};
    FILE*   momToKid {};
    int*    mom;

    // Normal Private Functions//
    void doAck();
    void doCommand();
    void doGetup();
    void doHello();
    void doNack();
    void doPrize();
    void doQuit();
    void doSit();

public:

    // Constructor//
    Kid(int* server, char* name);

    // Normal Public Functions//
    void run();
};