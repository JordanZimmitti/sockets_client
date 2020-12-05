#include <zconf.h>
#include "Kid.h"

/***********************************************************************************************/

/**
 * Primary Constructor For Kid
 * @param [client] - The server for communication between the other clients
 * @param [name]   - The Name of the child
 */
Kid::Kid(int* client, char* name) {
    this->mom  = client;
    this->name = name;
    srand(time(nullptr));
}

/**
 * Function That Starts The Musical Chairs Game
 */
void Kid::run() {

    // Opens The Input And Output Streams//
    kidToMom = fdopen(*mom, "w");
    momToKid = fdopen(*mom, "r");

    // While The Kid Is Playing The Game//
    for(;;) {
        if (isAlive) doCommand();
        else return;
    }
}

/**
 * Function That Handles The Command Coming In From The Server
 */
void Kid::doCommand() {

    // Gets The Command From The Server//
    char command[5];
    fscanf(momToKid, "%5s", command);

    // Completes An Action Based On The Received Command//
    if      (strcmp("HELLO", command) == 0) doHello();
    if      (strcmp("GETUP", command) == 0) doGetup();
    else if (strcmp("SIT__", command) == 0) doSit();
    else if (strcmp("ACK__", command) == 0) doAck();
    else if (strcmp("NACK_", command) == 0) doNack();
    else if (strcmp("PRIZE", command) == 0) doPrize();
    else if (strcmp("QUIT_", command) == 0) doQuit();
}

/***********************************************************************************************/

/**
 * Function That Shows That A Child Picked A Seat Successfully
 */
void Kid::doAck() {

    // Gets The Message From Mom//
    char output[50];
    int  chairNumber;
    fscanf(momToKid, "%46[^\n] %i", output, &chairNumber);

    // Shows That You Are Sitting In A Seat//
    cout << "\n" << output << " " << chairNumber << "'" << endl;
    cout << name << " is waiting for the next round to start..." << endl;
}

/**
 * Function That Gets The Players To Start Marching Around The Chairs
 */
void Kid::doGetup() {

    // Gets The Message From Mom//
    char output[60];
    int  currentNumberOfChairs;
    fscanf(momToKid, "%60[^\n] %i", output, &currentNumberOfChairs);

    // Shows Mom's Message//
    cout << "\n" << "Round " << ++round << endl;
    cout << "---------------------------------------------------------------------------------" << endl;
    cout << "\n" << output << currentNumberOfChairs << "'" << endl;

    // Sets The Current Number Of Chairs In-Play For The Round//
    numberOfChairs = currentNumberOfChairs;
}

/**
 * Function That Gets Mom's Introduction Message
 */
void Kid::doHello() {

    // Gets The Hello Message From Mom//
    char output[73];
    fscanf(momToKid, "%73[^\n]", output);

    // Shows Mom's Message//
    cout << output << endl;

    // Kid Says Hi To Mom And Tells Her Their Name//
    fprintf(kidToMom, "%s\n%s\n", "Hello mom my name is: ", name.c_str());
    fflush(kidToMom);

    // Shows That The Kid Introduced Himself//
    cout << name << " said hi to mom" << endl;
}

/**
 * Function That Gets The Players New Attempted Chair Number
 */
void Kid::doNack() {

    // Gets The Message From Mom//
    char output[35];
    char openChairs[BUFSIZ];
    int  currentChair;
    fscanf(momToKid, "%35[^\n] %1024[^\n] %i", output, openChairs, &currentChair);

    // Shows Mom's Message//
    cout << output << " " << currentChair << endl;

    // Gets The Chairs That Are Still Open//
    string str = openChairs;
    int size = str.size();

    // Picks A New Chair To Sit In//
    int newAttempt = (rand() % size) + 0;
    for (int index = 0; index < size; index++) {
        if (index != newAttempt) continue;

        // Converts The Character To An Int//
        char numberChar = str[index];
        int chair = atoi(&numberChar);

        // Sends The Attempted Seat To Mom//
        fprintf(kidToMom, "%s\n%s\n%i\n", name.c_str(), "is attempting to pick seat", chair);
        fflush(kidToMom);
    }
}

/**
 * Function That Shows The User That They Won Musical Chairs
 */
void Kid::doPrize() {

    // Gets The Message From Mom//
    char output[68];
    fscanf(momToKid, "%68[^\n]", output);
    isAlive = false;

    // Shows That The Player Won The Game//
    cout << "\n" << output << endl;
}

/**
 * Function That Shows The User That They Lost Musical Chairs
 */
void Kid::doQuit() {

    // Gets The Message From Mom//
    char output[68];
    fscanf(momToKid, "%68[^\n]", output);

    // Shows That The Player Lost The Game//
    cout << "\n" << output << endl;
    isAlive = false;
}

/**
 * Function That Picks A Seat Once Mom Stops Playing The Music
 */
void Kid::doSit() {

    // Gets The Message From Mom//
    char output[50];
    fscanf(momToKid, "%50[^\n]", output);

    // Shows Mom's Message//
    cout << "\n" << output << endl;

    // Gets The Response Time Of The Child//
    int responseTime = rand() % 30000 + 5000;
    usleep(responseTime);

    // Gets An Attempted Seat Number To Sit In//
    int attemptedChair = (rand() % numberOfChairs) + 0;

    // Shows What Seat The Child Picked//
    cout << name << " is attempting to pick seat " << attemptedChair << endl;

    // Sends The Attempted Seat To Mom//
    fprintf(kidToMom, "%s\n%s\n%i\n", name.c_str(), "is attempting to pick seat", attemptedChair);
    fflush(kidToMom);
}

/***********************************************************************************************/