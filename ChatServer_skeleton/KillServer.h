/*
 * KillServer.h
 *
 *  Created on: 02-Feb-2010
 *      Author: sc-gj
 */

#ifndef KILLSERVER_H_
#define KILLSERVER_H_

#include "Message.h"

class KillServer: public Message
{
public:
	KillServer();
	virtual ~KillServer();

};

#endif /* KILLSERVER_H_ */
