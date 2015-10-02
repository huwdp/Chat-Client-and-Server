/*
 * ChatMessage.h
 *
 *  Created on: 02-Feb-2010
 *      Author: sc-gj
 */

#ifndef CHATMESSAGE_H_
#define CHATMESSAGE_H_

#include "Message.h"

class ChatMessage: public Message
{
private:
	char *message;
	char *sender;

public:
	ChatMessage();
	ChatMessage(char* message, char* sender);
	virtual ~ChatMessage();

	void setMessage(char*);
	char* getMessage(void);

	void setSender(char*);
	char* getSender(void);

	int encode(char**);
	void decode(char*, int);
	size_t getXDRSize(void);
};

#endif /* CHATMESSAGE_H_ */
