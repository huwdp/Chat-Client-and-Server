/*
 * INet4Address.h
 *
 *  Created on: 29-Jul-2009
 *      Author: sc-gj
 *
 *
 */

#ifndef INET4ADDRESS_H_
#define INET4ADDRESS_H_

//Comment this in to activate QT methods
//#define MY_QT_FLAG

#include <netinet/in.h> /*Required for sockaddr_in */

/*The forward decleration of QString means
 * we don't need to comment it out to use the header
 * in a non-Qt projected.
 */

#ifdef MY_QT_FLAG
class QString;
#endif

class INet4Address
{
private:

	sockaddr_in address; //declare address structure
    socklen_t lenght;	//unsigned type used for object sizes

public:
	//Constructor
	INet4Address();
	INet4Address(char* address, int port);
	//Overloaded constructor sets wildcard for IP
	INet4Address(int port);
#ifdef MY_QT_FLAG
	//Overloaded for QtString
	INet4Address(QString& address, int port);
#endif
	//To get a sockaddr_in pointer to pass to connect
	sockaddr_in *getSockaddr();

	//The two types of length depending on how we need
	//to pass them
    socklen_t *sALengthRef();
    socklen_t sALengthVal();

	//We may want to print the address and port
	//pass in string lenght so we don't overfill the buffer
	void getSocketAddress(char*, int len);
	int getPort();

	//Debugging function
	void print();

	//Helpful functions for writing Qtbased network
	//projects - you cw will be one of these !
#ifdef MY_QT_FLAG
	static void qStringToCharArray(QString& qstr, char* cstr, int len);
	static void charArrayToQString(char* cstr, QString& qstr);
#endif
	virtual ~INet4Address();
};

#endif /* INET4ADDRESS_H_ */
