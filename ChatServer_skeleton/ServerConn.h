/*
 * Connection.h
 *
 *  Created on: 03-Aug-2009
 *      Author: sc-gj
 */

#ifndef SERVERCONN_H_
#define SERVERCONN_H_

#include	<netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include	<arpa/inet.h>	/* inet(3) functions */
/*Note other includes are now in .cpp file */

#include "INet4Address.h"

class ServerConn
{
private:
	//file descriptor of socket created in createSocket
	int sockfd;
	//address object used to create connection
	INet4Address* address;

public:
	//Cannot create a connection without an
	//address (aggregation).
	ServerConn(INet4Address*);

	void setAddress(INet4Address*);
	INet4Address *getAddress(void);

	//creates the socket descriptor (using info from address)
	//returns the descriptor which can be used to check for
	//errors
	int createSocket(void);

	//binds the socket to the given address
	int bindSocket(void);

	//sets the socket into the listening state
	int listenOnSocket(int backlog);

	//blocks until a client connection is available
	//from the completed connections queue
	int acceptFromSocket(INet4Address*);

	//closes the socket note returns the return value
	//of close to check for errors.
    int closeSocket(void);
    int closeSocket(int sockfd);

	//The functions we looked at earlier in method form
	//the difference is the use of a class wide socket
	//descriptor
	ssize_t readn(void *buff, size_t buffLength);
	ssize_t writen(void *buff, size_t buffLenght);

	//The client will use a different socket descriptor and so
	//we need some read and write functions not connected to the class
	static ssize_t readn(int sockfd, void *buff, size_t buffLength);
	static ssize_t writen(int sockfd, void *buff, size_t buffLenght);

	bool writeSize(int size);
	int readSize();

	static bool writeSize(int socfd, int size);
	static int readSize(int sockfd);

    virtual ~ServerConn();
};

#endif /* CONNECTION_H_ */
