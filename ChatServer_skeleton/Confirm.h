/*
 * Confirm.h
 *
 *  Created on: 02-Feb-2010
 *      Author: sc-gj
 */

#ifndef CONFIRM_H_
#define CONFIRM_H_

#include "Message.h"

class Confirm: public Message
{
private:
	bool response;

public:
	Confirm(bool response);
	Confirm();
	virtual ~Confirm();
	bool getResponse();
	void setResponse(bool);
	int encode(char**);
	void decode(char*, int);
	size_t getXDRSize(void);
};

#endif /* CONFIRM_H_ */
