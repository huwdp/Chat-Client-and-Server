/*
 * Join.cpp
 *
 *  Created on: 02-Feb-2010
 *      Author: sc-gj
 */

#include "Join.h"
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <rpc/rpc.h>

Join::Join()
{
	type = JOIN;
}

Join::Join(char* nick)
{
	type = JOIN;
	setNickname(nick);
}


Join::~Join()
{
	delete(nickname);
}

void Join::setNickname(char* nick)
{
	nickname = new char[strlen(nick)+1];
	strcpy(nickname,nick);
}

char* Join::getNickname(void)
{
	return nickname;
}

int Join::encode(char** buffer)
{
	//get size works out the size of
	//the encoded message using
	//xdr functions
	int bytes = getXDRSize();


	(*buffer)=(char*)malloc(bytes); //allocate some memory.

	//Create the stream
	xdrmem_create(&encodeStream,
				(*buffer),
				bytes,
				XDR_ENCODE
				);

	int strLength = strlen(nickname) + 1;

	if(!xdr_int(&encodeStream,&type)) return -1;
	if(!xdr_int(&encodeStream,&strLength)) return -1;
	if(!xdr_string(&encodeStream,&nickname,strLength)) return -1;

	//distroy the stream once decoding is complete
	xdr_destroy(&encodeStream);
	return bytes;
}

size_t Join::getXDRSize(void)
{

	int strLenght; //this will be used as a place holder for the strings lenght
	ulong lenght; //length calculated
	xdrproc_t proc; //pointer to the filter

	proc = (xdrproc_t)xdr_int; //set filter to xdr_int

	//use size of to work out size of encoded data
	//note must pass void* pointer to data
	lenght = xdr_sizeof(proc,(void*)&type) + xdr_sizeof(proc,(void*)&strLenght);

	proc = (xdrproc_t)xdr_string;  // set filter to xdr_string

//	lenght = strlen(nickname);
	lenght = lenght + xdr_sizeof(proc,&nickname);

	return lenght;
}

void Join::decode(char* buffer, int bufferSize)
{
	int stringSize;
	char* nick;
	//Create the stream
	xdrmem_create(&decodeStream,
				buffer,
				bufferSize,
				XDR_DECODE
				);
	//Use filters to enter the data

	if(xdr_int(&decodeStream,&type))
	{
		if(xdr_int(&decodeStream,&stringSize))
		{

			nick = new char[stringSize];

			if(xdr_string(&decodeStream,&nick, stringSize))
			{
				setNickname(nick);
			}
			else
			{
				printf("Error decoding nickname");
			}

			delete(nick);
		}
		else
		{
			printf("Error decoding nickname size");
		}
	}
	else
	{
		printf("Error decoding type");
	}

	xdr_destroy(&decodeStream);
}
