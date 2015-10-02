/*
 * UpdateMessage.cpp
 *
 *  Created on: 02-Feb-2010
 *      Author: sc-gj
 */

#include "UpdateMessage.h"
#include <string.h>

UpdateMessage::UpdateMessage()
{
	type = UPDATERESP;
	messageCount = 0;
}

UpdateMessage::~UpdateMessage()
{
	int i;
	if(messageCount > 0)
	{
		for(i=messageCount-1; i>-1; i--)
		{
			delete(messages.at(i));
			messages.pop_back();
		}
		messages.clear();
	}
}

void UpdateMessage::addMessage(char* message)
{
	char* copy = new char[strlen(message)+1];
	strcpy(copy,message);
	copy[strlen(message)] = 0;
	messages.push_back(copy);
	messageCount++;
}

char* UpdateMessage::getMessage(int index)
{
	return messages.at(index);
}

int UpdateMessage::getMessageCount()
{
	return messageCount;
}

int UpdateMessage::encode(char** buffer)
{
	//get size works out the size of
	//the encoded message using
	//xdr functions
	int bytes = getXDRSize();
	int i;
	char* msg;
	int stringLenght;

	(*buffer)=(char*)malloc(bytes); //allocate some memory.

	//Create the stream
	xdrmem_create(&encodeStream,
				(*buffer),
				bytes,
				XDR_ENCODE
				);

	if(!xdr_int(&encodeStream,&type)) return -1;
	if(!xdr_int(&encodeStream,&messageCount)) return -1;

	for(i=0;i<messageCount;i++)
	{
		msg = messages.at(i);
		stringLenght = strlen(msg) + 1;
		if(!xdr_int(&encodeStream,&stringLenght)) return -1;
		if(!xdr_string(&encodeStream,&msg,stringLenght))return -1;
	}

	//distroy the stream once decoding is complete
	xdr_destroy(&encodeStream);
	return bytes;
}

size_t UpdateMessage::getXDRSize(void)
{

	int strLenght; //this will be used as a place holder for the strings lenght
	ulong lenght; //length calculated
	xdrproc_t proc; //pointer to the filter
	int i;

	proc = (xdrproc_t)xdr_int; //set filter to xdr_int

	//use size of to work out size of encoded data
	//note must pass void* pointer to data
	lenght = xdr_sizeof(proc,(void*)&type);
	lenght = lenght + xdr_sizeof(proc,(void*)&messageCount);
	lenght = lenght + (messageCount*xdr_sizeof(proc,(void*)&strLenght));

	proc = (xdrproc_t)xdr_string;  // set filter to xdr_string

	for(i=0;i<messageCount;i++)
	{
		lenght = lenght + xdr_sizeof(proc,(void*)&messages.at(i));
	}

	return lenght;
}

void UpdateMessage::decode(char* buffer, int bufferSize)
{
	int stringSize;
	int i;
	char* msg;

	//Create the stream
	xdrmem_create(&decodeStream,
				buffer,
				bufferSize,
				XDR_DECODE
				);
	//Use filters to enter the data

	if(xdr_int(&decodeStream,&type))
	{
		if(xdr_int(&decodeStream,&messageCount))
		{
			for(i=0;i<messageCount;i++)
			{
				if(xdr_int(&decodeStream,&stringSize))
				{
					msg = new char[stringSize];
					if(xdr_string(&decodeStream,&msg, stringSize))
					{
						messages.push_back(msg);
					}
					else
					{
						printf("error decoding message %d\n",i);
					}
				}
				else
				{
					printf("error decoding message size\n");
				}
			}
		}
		else
		{
			printf("error decoding number of messages\n");
		}
	}
	else
	{
		printf("error decoding message type");
	}
	xdr_destroy(&decodeStream);
}
