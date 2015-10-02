/*
 * RequestUpdate.h
 *
 *  Created on: 02-Feb-2010
 *      Author: sc-gj
 */

#ifndef REQUESTUPDATE_H_
#define REQUESTUPDATE_H_

#include "Message.h"

class RequestUpdate: public Message
{
private:
	//Need to send the last message number so we're not re-sending all
	//the messages sent since the server started.
	int lastMessageNo;

public:
	RequestUpdate(int lastMessageNo);
	RequestUpdate();
	virtual ~RequestUpdate();
	int getLastMessageNo();
	int encode(char**);
	void decode(char*, int);
	size_t getXDRSize(void);
};

#endif /* REQUESTUPDATE_H_ */
