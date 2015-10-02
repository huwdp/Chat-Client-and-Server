/*
 * main.cpp
 *
 *  TODO change this :-)
 *  Created on: 2-Sept-2009
 *      Author: sc-gj
 */

#define MAXLINE 256

//needed for kill signal
#include <signal.h>
#include <pthread.h>        /* for posix threads */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>      /* basic system data types */
#include <sys/socket.h>     /* basic socket definitions */
#include <netinet/in.h>     /* sockaddr_in{} and other Internet defns */
#include <arpa/inet.h>      /* inet(3) functions */
#include <string.h>         /* for memset functions */
#include <unistd.h>         /* for read and write functions*/
#include <errno.h>          /* for checking errorno */
#include <time.h>           /* for time and time formatting functions */
#include <vector>           /*for SDL vector */

//alias vector
using std::vector;

#include "INet4Address.h"
#include "ServerConn.h"
#include "Message.h"
#include "Join.h"
#include "Leave.h"
#include "Confirm.h"
#include "ChatMessage.h"
#include "UpdateMessage.h"
#include "RequestUpdate.h"

//Shared variables
//Message list stores strings in the form nickname: message
vector <char*> messageList;
//Store the Join message objects in a list for each joined user
vector <Join*> users;

//Mutex for message list (these will be utalised by a threaded solution).
pthread_mutex_t messageListMutex = PTHREAD_MUTEX_INITIALIZER;
//Mutex user list
pthread_mutex_t userListMutex = PTHREAD_MUTEX_INITIALIZER;


//Threads (for threaded solution).
void *clientHandler(void* iptr);

//Functions - these take a buffer, create the right
//sort of object process the request and return the right sort of
//response.
void handleJoinMessage(char* inBuffer, int size, char** outBuffer, int *outsize);
void handleLeaveMessage(char* inBuffer, int size, char** outBuffer, int *outsize);
void handleNewMessage(char* inBuffer, int size, char** outBuffer, int *outsize);
void handleUpdateRequest(char* inBuffer, int size, char** outBuffer, int *outsize);

//Server Connection (moved globally, needed for client thread)
ServerConn *serverConnection;

int main(void)
{
    //Listening address
    INet4Address *listeningAddress;

    //Socket file descriptor
    //Text buffer - for IP of client machine
    char buff[256];
    //for new threads
    //pthread_t statusTid; //status thread - reports no of clients
    //pthread_t clientHandlerTid; //handles client communication
    //pthread_t ioThreadTid;

    //Address object for client address
    INet4Address *clientAddress = new INet4Address();

    //Create listening address object
    listeningAddress = new INet4Address(50018);

    //Create server socket
    serverConnection = new ServerConn(listeningAddress);

    //Set up the socket
    //ServerConnection->
    if (serverConnection->createSocket() <0)
    {
        printf("socket Error\n");
        exit(1);
    }

    //Bind server socket
    if (serverConnection->bindSocket() < 0)
    {
        printf("Bind Error");
        serverConnection->closeSocket();
        exit(1);
    }

    //Start sever listening
    if (serverConnection->listenOnSocket(5) < 0)
    {
        printf("Listen Error \n");
        serverConnection->closeSocket();
        exit(1);
    }

    while(true)
    {
        // Start the IO stop thread
        int clientSock;
        if ((clientSock = serverConnection->acceptFromSocket(clientAddress)) < 0)
        {
            printf("Accept error\n");
            printf("%s\n", strerror(errno));
            serverConnection->closeSocket();
            exit(1);
        }
        else
        {
            clientAddress->getSocketAddress(buff, sizeof(buff));
            //Handle client | Create Client Thread | Fork Process
            printf("Got Client\n");
            printf("Connection from %s, port %d\n", buff, clientAddress->getPort());

            //ClientHandler(clientSock);
            pthread_t tid;
            int* iptr = new int[1];
            *iptr = clientSock;
            int retVal = pthread_create(&tid, NULL, clientHandler, iptr);
            if (retVal != 0)
            {
                printf("Pthread creation error\n");
                exit(1);
            }
        }
    }
    serverConnection->closeSocket();
}

/*
 * If using threads to handle the each client the outline below
 * may be useful.
 */
void* clientHandler(void* iptr)
{
    char* returnMessage;
    char *incomingMessage;; //Max size of incomming message
    Message *m = new Message();
    int incMessageSize;
    int retMessageSize;
    int type;

    //Recover client sock (from args)
    int clientSock = *(int*)iptr;

    //Get thread ID and detach thread from the parent
    pthread_t myTid = pthread_self();
    pthread_detach(myTid);

    //Recover message
    //Read size first
    //Read message as bytes
    incMessageSize = serverConnection->readSize(clientSock);
    incomingMessage = new char[incMessageSize];

    int readLen = serverConnection->readn(clientSock, incomingMessage, incMessageSize);

    //Decode as a message - do this first as a message
    //and re-decode later to get specific object.
    m->decode(incomingMessage,incMessageSize);

    type = m->getType();
    //Write a function to process each message :-)
    //Work out what to do (big switch on message number)
    switch(type)
    {
        case JOIN:
            printf("Join message received - by thread %d\n",(int)myTid);
            handleJoinMessage(incomingMessage,incMessageSize,&returnMessage,&retMessageSize);
            break;
        case LEAVE:
            printf("Leave message received - by thread %d\n",(int)myTid);
            handleLeaveMessage(incomingMessage,incMessageSize,&returnMessage,&retMessageSize);
            break;
        case MESSAGE:
            printf("Chat message received - by thread %d\n",(int)myTid);
            handleNewMessage(incomingMessage,incMessageSize,&returnMessage, &retMessageSize);
            break;
        case UPDATE:
            printf("Update request received - by thread %d\n",(int)myTid);
            handleUpdateRequest(incomingMessage,incMessageSize,&returnMessage, &retMessageSize);
            break;
    };

    delete(incomingMessage);

    //Respond with message (NB send message size first)
    serverConnection->writeSize(clientSock, retMessageSize);

    serverConnection->writen(clientSock, returnMessage, retMessageSize);

    //Deallocate memory (byte buffer)
    delete(returnMessage);
    delete m;

    //Close socket
    serverConnection->closeSocket(clientSock);
    //End thread
    pthread_exit(0);
    return NULL;
}


void handleJoinMessage(char* inBuffer, int size, char** outBuffer, int *outSize)
{
    //Create a Join message
    Join *j = new Join();
    //Decode buffer into join message
    j->decode(inBuffer, size);
    printf("Nickname: %s\n", j->getNickname());
    //Search the users list for nickname
    //If the name exits do not add
    bool accept = true;
    pthread_mutex_lock(&userListMutex);
    for(vector<Join*>::iterator it = users.begin(); it != users.end(); ++it)
    {
        Join *user = *(it);
        if (strcmp(j->getNickname(), user->getNickname()) == 0)
        {
            //Exact match
            accept = false;
        }
    }
    pthread_mutex_unlock(&userListMutex);
    if (accept)
    {
        users.push_back(j);
    }
    else
    {
        delete j;
    }
    //Respond with confirm message
    Confirm *c = new Confirm();

    c->setResponse(accept);
    //Encode the message into the outbuffer and
    //Set the outsize
    (*outSize)=c->encode(outBuffer);
    delete c;
}

void handleLeaveMessage(char* inBuffer, int size, char** outBuffer, int *outSize)
{
    //Create a Leave message
    Leave *l = new Leave();
    //Decode leave message
    l->decode(inBuffer, size);
    //Search the users list for nickname
    bool deleted = false;

    pthread_mutex_lock(&userListMutex);
    for(vector<Join*>::iterator it = users.begin(); it != users.end(); ++it)
    {
        Join *user = *(it);
        //Remove nickname if it exists
        if (strcmp(l->getNickname(), user->getNickname()) == 0)
        {
            users.erase(it);
            deleted = true;
            break; //Erasing messes up iteration, so may as well just break out
        }
    }
    pthread_mutex_unlock(&userListMutex);

    //Create appropriate confirm message
    Confirm *c = new Confirm();
    c->setResponse(deleted);
    //Encode this message and return
    (*outSize)=c->encode(outBuffer);
    delete l;
    delete c;
}


void handleNewMessage(char* inBuffer, int size, char** outBuffer, int *outSize)
{
    //Create a Chat Message
    ChatMessage *m = new ChatMessage();
    //Decode Chat Message
    m->decode(inBuffer, size);
    //Search the users list for nickname
    bool found = false;

    pthread_mutex_lock(&userListMutex);
    for(vector<Join*>::iterator it = users.begin(); it != users.end(); ++it)
    {
        Join *user = (*it);
        //Remove nickname if it exists
        if (strcmp(m->getSender(), user->getNickname()) == 0)
        {
            found = true;
        }
    }
    pthread_mutex_unlock(&userListMutex);

    //If the name exists add the name and message to the messages list
    if (found)
    {
        char* message = new char[strlen(m->getSender()) + 2 + strlen(m->getMessage()) + 1]; //sender + ": " + message + null
        sprintf(message, "%s: %s", m->getSender(), m->getMessage()); //easier than dealing with strcpy

        pthread_mutex_lock(&messageListMutex);
        messageList.push_back(message);
        pthread_mutex_unlock(&messageListMutex);
    }

    //Create appropriate confirm message
    Confirm *c = new Confirm();
    c->setResponse(found);
    //Encode this message and return
    (*outSize)=c->encode(outBuffer);

    delete m;
    delete c;
}

/*NOTE to those using threading make sure that only one thread at a time is
 * using the message list (this includes encoding it).
 */
void handleUpdateRequest(char* inBuffer, int size, char** outBuffer, int *outSize)
{
    int i = 0;
    int lastMessageNo = 0;

    //Create a Request Update Message
    RequestUpdate *u = new RequestUpdate();

    //Decode Request Update Message
    u->decode(inBuffer, size);

    lastMessageNo = u->getLastMessageNo();
    //Create appropriate update message
    UpdateMessage *um = new UpdateMessage();

    //Add messages from the last
    pthread_mutex_lock(&messageListMutex);
    for (vector<char *>::iterator it = messageList.begin(); it != messageList.end(); ++it)
    {
        if (i >= lastMessageNo)
        {
            um->addMessage(*(it));
        }
        i++;
    }
    pthread_mutex_unlock(&messageListMutex);

    //Encode this message and return
    (*outSize)=um->encode(outBuffer);

    delete u;
    delete um;
}

