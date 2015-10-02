/*
 * UpdateMessage.h
 *
 *  Created on: 02-Feb-2010
 *      Author: sc-gj
 */

#ifndef UPDATEMESSAGE_H_
#define UPDATEMESSAGE_H_

#include "Message.h"
#include <vector>

using std::vector;

class UpdateMessage: public Message {

private:
	vector <char*> messages;
	int messageCount;

public:
	UpdateMessage();
	virtual ~UpdateMessage();

	void addMessage(char*);
	char* getMessage(int index);
	int getMessageCount();

	int encode(char**);
	void decode(char*, int);
	size_t getXDRSize(void);
};

#endif /* UPDATEMESSAGE_H_ */
