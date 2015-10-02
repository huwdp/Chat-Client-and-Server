/*
 * Message.cpp
 *
 *  Created on: 02-Feb-2010
 *      Author: sc-gj
 */

#include "Message.h"

Message::Message()
{

}

Message::~Message()
{

}

int Message::getType(void)
{
	return type;
}

int Message::encode(char** buffer)
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

	if(!xdr_int(&encodeStream,&type)) return -1;

	//distroy the stream once decoding is complete
	xdr_destroy(&encodeStream);
	return bytes;
}

void Message::decode(char* buffer, int bufferSize)
{
	//Create the stream
	xdrmem_create(&decodeStream,
				buffer,
				bufferSize,
				XDR_DECODE
				);
	//Use filters to enter the data

	if(xdr_int(&decodeStream,&type));
	else
	{
		printf("error decoding type");
	}

	xdr_destroy(&decodeStream);

}

size_t Message::getXDRSize(void)
{
	ulong lenght; //length calculated
	xdrproc_t proc; //pointer to the filter

	proc = (xdrproc_t)xdr_int; //set filter to xdr_int

	//use size of to work out size of encoded data
	//note must pass void* pointer to data
	lenght = xdr_sizeof(proc,(void*)&type);

	return lenght;
}
