/*
 * INet4Address.cpp
 *
 *  Created on: 29-Jul-2009
 *      Author: sc-gj
 *
 *      Skeleton for students
 */

#include "INet4Address.h"
#include <arpa/inet.h> /*Required for inet_pton */
#include <string.h> 	/*Required for memset */
#include <stdio.h>

#ifdef MY_QT_FLAG
	#include <QString> //Required for QtString
#endif

INet4Address::INet4Address()
{

}

INet4Address::INet4Address(char* add, int port)
{
	//set memory
	memset(&address, 0, sizeof(address));
	//set sin_family and sin_port (network byte order)
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	//set sin_addr (hint inet_pton)
	inet_pton(AF_INET,add,&address.sin_addr);
	//set lenght (within class)
	lenght = sizeof(address);
}

INet4Address::INet4Address(int port)
{
	//set memory
	memset(&address, 0, sizeof(address));
	//set sin_family and sin_port (network byte order)
	address.sin_family = AF_INET;
	address.sin_port = htons(port);

	/*
	 * Note how we set the add	return bind(sockfd,(sockaddr *)address->getSockaddr(),address->sALengthVal());
	 * ress of the listening machine to a wildcard
	 * we can set it to any address that is connected to an interface
	 * on the computer (e.g. if we had two network cards with
	 * different IP addresses).
	 *
	 */
	address.sin_addr.s_addr = htonl(INADDR_ANY);

	//set lenght (within class)
	lenght = sizeof(address);
}

#ifdef MY_QT_FLAG
INet4Address::INet4Address(QString& qAdd, int port)
{
	//as above but with QString conversion
	char* addStr;
	addStr = new char[qAdd.size()+1];
	qStringToCharArray(qAdd, addStr,qAdd.size()+1);
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	inet_pton(AF_INET,addStr,&address.sin_addr);
	lenght = sizeof(address);
	delete(addStr);
}
#endif

INet4Address::~INet4Address()
{
	// TODO Auto-generaddrated destructor stub
	// TODO check for malloc/new memory
}



sockaddr_in *INet4Address::getSockaddr()
{
	//return pointer to structure
	return &address;
}

socklen_t *INet4Address::sALengthRef()
{
	//return pointer to length of structure
	return &lenght;
}

socklen_t INet4Address::sALengthVal()
{
	//return value length of structure
	return lenght;
}

void INet4Address::getSocketAddress(char* cstr, int len)
{
	//return the address as a string
	inet_ntop(AF_INET, &address.sin_addr, cstr, len);
}

int INet4Address::getPort()
{
	//return the port remember
	//convert to host byte order
	return ntohs(address.sin_port);
}

void INet4Address::print()
{
	char buff[256];
	printf("INet4Address:- %s, port %d\n",
			inet_ntop(AF_INET,
			&address.sin_addr,
			buff,
			sizeof(buff)),
			ntohs(address.sin_port));
}

#ifdef MY_QT_FLAG
void INet4Address::qStringToCharArray(QString& qstr, char* cstr, int len)
{
	//return char array version of QString
	//use strncpy and observe the length of the string
	//remember to take the /0 into account
	if(cstr)
		strncpy(cstr,qstr.toAscii().data(), len-1);
}

void INet4Address::charArrayToQString(char* cstr, QString& qstr)
{
	//return new QString
	qstr = QString(cstr);
}
#endif
