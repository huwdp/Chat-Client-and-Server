/*
 * Message.h
 *
 *  Created on: 02-Feb-2010
 *      Author: sc-gj
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#define JOIN 		0
#define LEAVE 		1
#define MESSAGE 	2
#define UPDATE 		3
#define STERM 		4

#define CONFIRM		5
#define UPDATERESP 	6
#define CTERM		7

#include <stdio.h>
#include <rpc/rpc.h>

class Message
{

protected:
	int type;
	XDR encodeStream;
	XDR decodeStream;

public:
	Message();
	virtual ~Message();

	int getType(void);

	virtual int encode(char**);
	virtual void decode(char*, int);
	virtual size_t getXDRSize();



};

#endif /* MESSAGE_H_ */
