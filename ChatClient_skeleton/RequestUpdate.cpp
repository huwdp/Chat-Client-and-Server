/*
 * RequestUpdate.cpp
 *
 *  Created on: 02-Feb-2010
 *      Author: sc-gj
 */

#include "RequestUpdate.h"

RequestUpdate::RequestUpdate(int lastMessageNo)
{
	this->lastMessageNo = lastMessageNo;
	type = UPDATE;
}

RequestUpdate::RequestUpdate()
{
	type = UPDATE;
	this->lastMessageNo = 0;
}

RequestUpdate::~RequestUpdate()
{
}

int RequestUpdate::encode(char** buffer)
{
	//get size works out the size of
	//the encoded message using
	//xdr functions
	int bytes = getXDRSize();
	int error =0;

	(*buffer)=(char*)malloc(bytes); //allocate some memory.

	//Create the stream
	xdrmem_create(&encodeStream,
				(*buffer),
				bytes,
				XDR_ENCODE
				);

	if(!xdr_int(&encodeStream,&type)) return -1;
	if(!xdr_int(&encodeStream,&lastMessageNo)) return -1;

	//distroy the stream once decoding is complete
	xdr_destroy(&encodeStream);
	return bytes;
}

size_t RequestUpdate::getXDRSize(void)
{

	size_t strLenght; //this will be used as a place holder for the strings lenght
	ulong lenght; //length calculated
	xdrproc_t proc; //pointer to the filter

	proc = (xdrproc_t)xdr_int; //set filter to xdr_int

	//use size of to work out size of encoded data
	//note must pass void* pointer to data
	lenght = xdr_sizeof(proc,(void*)&type) + xdr_sizeof(proc,(void*)&lastMessageNo);

	return lenght;
}

void RequestUpdate::decode(char* buffer, int bufferSize)
{
	//Create the stream
	xdrmem_create(&decodeStream,
				buffer,
				bufferSize,
				XDR_DECODE
				);
	//Use filters to enter the data

	if(xdr_int(&decodeStream,&type))
	{
		if(xdr_int(&decodeStream,&lastMessageNo));
		else
		{
			printf("Error decoding lastMessageNo\n");
		}
	}
	else
	{
		printf("Error decoding type\n");
	}

	xdr_destroy(&decodeStream);
}

int RequestUpdate::getLastMessageNo()
{
	return lastMessageNo;
}
