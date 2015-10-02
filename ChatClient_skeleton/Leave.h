/*
 * Leave.h
 *
 *  Created on: 02-Feb-2010
 *      Author: sc-gj
 */

#ifndef LEAVE_H_
#define LEAVE_H_

#include "Message.h"

class Leave: public Message
{
private:
	char* nickname;

public:
	Leave();
	virtual ~Leave();
	void setNickname(char*);
	char* getNickname(void);
	int encode(char**);
	void decode(char*, int);
	size_t getXDRSize(void);
};

#endif /* LEAVE_H_ */
