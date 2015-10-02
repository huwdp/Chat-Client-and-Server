/*
 * Join.h
 *
 *  Created on: 02-Feb-2010
 *      Author: sc-gj
 */

#ifndef JOIN_H_
#define JOIN_H_

#include "Message.h"

class Join : public Message
{

private:
	char* nickname;



public:
	Join();
	Join(char*);
	virtual ~Join();
	void setNickname(char*);
	char* getNickname(void);
	int encode(char**);
	void decode(char*, int);
	size_t getXDRSize(void);

};

#endif /* JOIN_H_ */
