/*
 * Confirm.cpp
 *
 *  Created on: 02-Feb-2010
 *      Author: sc-gj
 */

#include "Confirm.h"

Confirm::Confirm()
{
	type = CONFIRM;
}

Confirm::Confirm(bool resp)
{
	type = CONFIRM;
	response = resp;
}

Confirm::~Confirm()
{
}

bool Confirm::getResponse()
{
	return response;
}

void Confirm::setResponse(bool resp)
{
	response = resp;
}

int Confirm::encode(char** buffer)
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

	int resp;
	if(response) resp = 0;
	else resp = 1;

	if(!xdr_int(&encodeStream,&type)) return -1;
	if(!xdr_int(&encodeStream,&resp)) return -1;


	//distroy the stream once decoding is complete
	xdr_destroy(&encodeStream);
	return bytes;
}

size_t Confirm::getXDRSize(void)
{

	int resp; //this will be used as a place holder response
	ulong lenght; //length calculated
	xdrproc_t proc; //pointer to the filter

	proc = (xdrproc_t)xdr_int; //set filter to xdr_int

	//use size of to work out size of encoded data
	//note must pass void* pointer to data
	lenght = xdr_sizeof(proc,(void*)&type) + xdr_sizeof(proc,(void*)&resp);

	return lenght;
}

void Confirm::decode(char* buffer, int bufferSize)
{
	int resp;
	//Create the stream
	xdrmem_create(&decodeStream,
				buffer,
				bufferSize,
				XDR_DECODE
				);
	//Use filters to enter the data

	if(xdr_int(&decodeStream,&type))
	{
		if(xdr_int(&decodeStream,&resp))
		{
			if(resp == 0)
				response = true;
			else
				response = false;
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
