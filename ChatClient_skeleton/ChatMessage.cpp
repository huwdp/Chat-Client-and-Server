/*
 * ChatMessage.cpp
 *
 *  Created on: 02-Feb-2010
 *      Author: sc-gj
 */

#include "ChatMessage.h"
#include <string.h>
#include <QDebug>

ChatMessage::ChatMessage()
{
	type = MESSAGE;
}

ChatMessage::ChatMessage(char* message, char* sender)
{
	type = MESSAGE;
	setMessage(message);
	setSender(sender);
}

ChatMessage::~ChatMessage()
{
	delete(sender);
	delete(message);
}

void ChatMessage::setMessage(char* str)
{
	message = new char[strlen(str)+1];
	strcpy(message,str);
}

char* ChatMessage::getMessage(void)
{
	return message;
}

void ChatMessage::setSender(char* str)
{
	sender = new char[strlen(str)+1];
	strcpy(sender,str);
}

char* ChatMessage::getSender(void)
{
	return sender;
}

int ChatMessage::encode(char** buffer)
{
	//get size works out the size of
	//the encoded message using
	//xdr functions
	int bytes = getXDRSize();
	int error =0;
	int stringLenght;
	char *str;

	(*buffer)=(char*)malloc(bytes); //allocate some memory.

	//Create the stream
	xdrmem_create(&encodeStream,
				(*buffer),
				bytes,
				XDR_ENCODE
				);

	if(!xdr_int(&encodeStream,&type)) return -1;

	stringLenght = strlen(sender) + 1;
	str = sender;
    if(!xdr_int(&encodeStream,&stringLenght))
    {
        qDebug() << "String length encode error 1!";
        return -1;
    }
    if(!xdr_string(&encodeStream,&str,stringLenght))
    {
        qDebug() << "String encode error 1!";
        return -1;
    }
    stringLenght = strlen(message) + 1;
    str = message;
    if(!xdr_int(&encodeStream,&stringLenght))
    {
        qDebug() << "String length encode error 2!";
        return -1;
    }
    if(!xdr_string(&encodeStream,&str,stringLenght))
    {
        qDebug() << "String encode error 2!";
        return -1;
    }

	//distroy the stream once decoding is complete
	xdr_destroy(&encodeStream);
	return bytes;
}

size_t ChatMessage::getXDRSize(void)
{

	size_t strLenght; //this will be used as a place holder for the strings lenght
	ulong lenght; //length calculated
	xdrproc_t proc; //pointer to the filter

	proc = (xdrproc_t)xdr_int; //set filter to xdr_int

	//use size of to work out size of encoded data
	//note must pass void* pointer to data
	lenght = xdr_sizeof(proc,(void*)&type) + (2*xdr_sizeof(proc,(void*)&strLenght));

	proc = (xdrproc_t)xdr_string;  // set filter to xdr_string

	lenght = lenght + xdr_sizeof(proc,&sender);
	lenght = lenght + xdr_sizeof(proc,&message);

	return lenght;
}

void ChatMessage::decode(char* buffer, int bufferSize)
{
	int stringSize;
	char* str;
	char* str2;

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
			str = new char[stringSize];
			if(xdr_string(&decodeStream,&str, stringSize))
			{
				setSender(str);

				if(xdr_int(&decodeStream,&stringSize))
				{

					str2 = new char[stringSize];
					if(xdr_string(&decodeStream,&str2, stringSize))
					{
						setMessage(str2);
					}
					else
					{
						printf("Error decoding message\n");
					}
					delete(str2);
				}
				else
				{
					printf("Error decoding message size\n");
				}
				delete(str);
			}
			else
			{
				delete(str);
				printf("Error decoding sender\n");
			}
		}
		else
		{
			printf("Error decoding sender size\n");
		}
	}
	else
	{
		printf("Error decoding type\n");
	}

	xdr_destroy(&decodeStream);
}

