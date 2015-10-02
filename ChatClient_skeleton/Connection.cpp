/*
 * Connection.cpp
 *
 *  Created on: 03-Aug-2009
 *      Author: sc-gj
 */

#include 	<stdio.h>
#include 	<stdlib.h>
#include	<sys/types.h>	/* basic system data types */
#include	<sys/socket.h>	/* basic socket definitions */
#include  	<string.h>		/* for memset functions */
#include 	<unistd.h>		/* for read and write functions*/
#include 	<errno.h>  //for checking errorno :-)

#include "Connection.h"

Connection::Connection(INet4Address *addr)
{
	setAddress(addr);

}

Connection::~Connection()
{
	if(sockfd)
		close(sockfd);
}

void Connection::setAddress(INet4Address *addr)
{
	address = addr;
}

INet4Address *Connection::getAddress(void)
{
	return address;
}

int Connection::createSocket(void)
{
	sockfd = socket(address->getSockaddr()->sin_family,SOCK_STREAM,0);
	return sockfd;
}

int Connection::connectSocket(void)
{
	return connect(sockfd, (sockaddr *)address->getSockaddr(), address->sALengthVal());
}

int Connection::closeSocket(void)
{
	return close(sockfd);
}

ssize_t Connection::readn(void *vptr, size_t bytesToRead)
{
	//keep track of how much we are
	//reading and how much we have
	//left to read
	size_t nleft;
	ssize_t nread;

	//as we're dealing in reading and writing
	//bytes convert everything to strings
	char *ptr;
	ptr = (char*)vptr;

	//we are at the start all the bytes are
	//left to be read
	nleft = bytesToRead;

	while(nleft >0) //keep reading until we've filled buffer
	{
		if( (nread = read(sockfd,ptr,nleft)) < 0)
		{
			/* Read returned and error find out what's gone wrong */
			if(errno == EINTR) //host delivery failure
				nread =0;  //reset count and go
						   //back around the loop
			else
				return -1;	//return error code
		}
		else
		{
			if(nread == 0)
			{
				break; //reached EOF
			}
			else //read success
			{
				//change read pointer
				nleft -= nread;
				//move string pointer along buffer
				ptr += nread;
			}
		}
	}
	//calculate how much we read
	return bytesToRead-nleft;
}

ssize_t Connection::writen(void *vptr, size_t bytesToWrite)
{
	//keeping track of how  much we have
	//written and how must left to write
	size_t nleft;
	ssize_t nwritten;

	//convert the buffer to a string
	//use this to move along the buffer
	const char *ptr;
	ptr = (char*)vptr;


	nleft = bytesToWrite;

	while(nleft >0) //while we're not finished
	{
		if( (nwritten = write(sockfd,ptr,nleft)) <= 0)
		{
			//if we got an error find out what has gone wrong
			if(nwritten < 0 && errno == EINTR)
			{
				//EINTR indicates an interrupt stopped our read
				//in this case we just retry
				nwritten = 0;
			}
			else
			{
				//error reported by write drop out with an
				//error code
				return -1;
			}
		}
		else //read successful (0 or more bytes read)
		{
			//decrement bytes left
			nleft -= nwritten;
			//more pointer along buffer
			//Fortunately nwritten is in bytes
			ptr += nwritten;
		}
	}
	//if we get here without returning with an error
	//we have written all the bytes we set out to read
	return bytesToWrite;
}

bool Connection::writeSize(int size)
{
	int i = htonl (size);
	send (sockfd, &i, sizeof(i), 0);
}

int Connection::readSize()
{
	int i;
	recv (sockfd, &i, sizeof(i), 0);
	return ntohl(i);
}
