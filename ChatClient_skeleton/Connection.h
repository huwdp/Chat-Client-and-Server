/*
 * Connection.h
 *
 *  Created on: 03-Aug-2009
 *      Author: sc-gj
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_

#include	<netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include	<arpa/inet.h>	/* inet(3) functions */
/*Note other includes are now in .cpp file */

#include "INet4Address.h"

class Connection
{
private:
	//file descriptor of socket created in createSocket
	int sockfd;
	//address object used to create connection
	INet4Address* address;

public:
	//Cannot create a connection without an
	//address (aggregation).
	Connection(INet4Address*);

	void setAddress(INet4Address*);
	INet4Address *getAddress(void);

	//creates the socket descriptor (using info from address)
	//returns the descriptor which can be used to check for
	//errors
	int createSocket(void);

	//connects the socket using the socket descriptor and the
	//address information
	int connectSocket(void);

	//closes the socket note returns the return value
	//of close to check for errors.
	int closeSocket(void);

	//The functions we looked at earlier in method form
	//the difference is the use of a class wide socket
	//descriptor
	ssize_t readn(void *buff, size_t buffLength);
	ssize_t writen(void *buff, size_t buffLenght);

	bool writeSize(int size);
	int readSize();

	virtual ~Connection();
};

#endif /* CONNECTION_H_ */
