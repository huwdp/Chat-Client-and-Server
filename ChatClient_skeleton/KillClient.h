/*
 * KillClient.h
 *
 *  Created on: 02-Feb-2010
 *      Author: sc-gj
 */

#ifndef KILLCLIENT_H_
#define KILLCLIENT_H_

#include "Message.h"

class KillClient: public Message
{
public:
	KillClient();
	virtual ~KillClient();

};

#endif /* KILLCLIENT_H_ */
