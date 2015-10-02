#include <QTimer>
#include "chatclient.h"
#include "Join.h"
#include "Leave.h"
#include "Confirm.h"
#include "ChatMessage.h"
#include "RequestUpdate.h"
#include "UpdateMessage.h"

#include "INet4Address.h"
#include "Connection.h"



ChatClient::ChatClient(QWidget *parent) : QWidget(parent)
{
	ui.setupUi(this);
	nickAccepted = false;

	//Setup the timer
	timer = new QTimer();
    timer->setInterval(1000);

	//TODO activate this when your ready (i.e. you're ready to write the
	//slot associated with it!
    QWidget::connect(timer,SIGNAL(timeout()),this,SLOT(getMessages()));

	lastMessageNo = 0;

}

ChatClient::~ChatClient()
{
    delete timer;
}

void ChatClient::on_joinButton_clicked()
{
    Join *j;
    Confirm *c;
    INet4Address *servaddr;
    Connection *myConnection;
    char* buffer; //for encoded messages
    int bytesToSend;
    int bytesToReceive;
    int bytesReceived;

    //Get the strings out of the address, port and nickname
    //boxes and convert to strings;
    QString qip = ui.addresLine->text();
    QString qport = ui.portLine->text();
    QString qnick = ui.nicknameLine->text();

    //Create new connection objects
    servaddr = new INet4Address(qip.toLatin1().data(),qport.toInt());
    myConnection = new Connection(servaddr);

    //Connect to server

    if(myConnection->createSocket() < 0)
    {
        printf("Socket Error\n");
        return;
    }

    if(myConnection->connectSocket() < 0)
    {
        printf("Connect Error\n");
        delete(myConnection);
        delete(servaddr);
        return;
    }

    //Make a join message
    j = new Join();
    j->setNickname(qnick.toLatin1().data());

    //Send join message (as bytes)
    bytesToSend = j->encode(&buffer);

    printf("Buffer: %s, Nick: %s ",buffer, j->getNickname());

    myConnection->writeSize(bytesToSend);
    myConnection->writen(buffer,bytesToSend);

    delete(buffer);

    //Read response - take action!
    //Read byte count
    bytesToReceive = myConnection->readSize();
    buffer = new char[bytesToReceive];

    //Read message
    bytesReceived=myConnection->readn(buffer,bytesToReceive);

    if(bytesReceived < bytesToReceive)
        printf("Server response truncated!");

    //Convert to message (confirm)
    c = new Confirm();
    c->decode(buffer,bytesToReceive);
    //Destroy socket
    myConnection->closeSocket();

    //check if nick accepted
    if(c->getResponse()==true)
    {
        nickAccepted = true;
        ui.addresLine->setEnabled(false);
        ui.portLine->setEnabled(false);
        ui.nicknameLine->setEnabled(false);
        ui.joinButton->setEnabled(false);

        //Turn on the timer
        timer->start();
    }
    else
    {
        nickAccepted = false;
        ui.nicknameLine->setText(tr("Rejected!"));
    }


    delete myConnection;
    delete servaddr;
}

void ChatClient::on_leaveButton_clicked()
{
    if(nickAccepted == true) //only respond if they are connected
	{
		Leave *l;
		Confirm *c;
		INet4Address *servaddr;
		Connection *myConnection;
		char* buffer; //for encoded messages
		int bytesToSend;
		int bytesToReceive;

		//Get the strings out of the address, port and nickname
		//boxes and convert to strings;
		QString qip = ui.addresLine->text();
		QString qport = ui.portLine->text();
		QString qnick = ui.nicknameLine->text();

		//TODO Create new connection objects
        servaddr = new INet4Address(qip.toLatin1().data(),qport.toInt());
        myConnection = new Connection(servaddr);

		//TODO Connect to server
        if (myConnection->createSocket() < 0)
        {
            printf("Could not create socket error.");
            return;
        }
        if (myConnection->connectSocket() < 0)
        {
            printf("Could not connect socket error.");
            delete(myConnection);
            delete(servaddr);
            return;
        }

		//TODO Make a leave message
		l = new Leave();
        l->setNickname(qnick.toLatin1().data());

		//TODO Send leave message (as bytes)
        bytesToSend = l->encode(&buffer);

		//TODO Send size of message first
        myConnection->writeSize(bytesToSend);

		//TODO Send message
        myConnection->writen(buffer,bytesToSend);

        //delete(buffer);

		//TODO Read response (confirm) - take action!
        bytesToReceive = myConnection->readSize();

		//TODO Read byte count
        buffer = new char[bytesToReceive];

		//TODO Read message
        myConnection->readn(buffer,bytesToReceive);

		//TODO Close socket
        myConnection->closeSocket();

		//TODO Convert to message (confirm)
        c = new Confirm();

		//TODO Decode message
        c->decode(buffer,bytesToReceive);

		//check if nick removed
		if(c->getResponse()==true)
		{
			nickAccepted = false;
			ui.addresLine->setEnabled(true);
			ui.portLine->setEnabled(true);
			ui.nicknameLine->setEnabled(true);
			ui.joinButton->setEnabled(true);
			ui.nicknameLine->setText(tr(""));

			//Stop timer
            timer->stop();
		}
		else
		{
			nickAccepted = true;
		}


        delete myConnection;
        delete servaddr;
	}
}

void ChatClient::on_sendButton_clicked()
{
    if(nickAccepted == true) //only respond if they are connected
	{
        ChatMessage *cm;
		Confirm *c;
		INet4Address *servaddr;
		Connection *myConnection;
		char* buffer; //for encoded messages
		int bytesToSend;
		int bytesToReceive;

		//Get the strings out of the address, port and nickname
		//boxes and convert to strings;
		QString qmessage = ui.lineEdit->text();
		QString qnick = ui.nicknameLine->text();
		QString qip = ui.addresLine->text();
		QString qport = ui.portLine->text();


        //TODO Create new connection objects
        servaddr = new INet4Address(qip.toLatin1().data(),qport.toInt());
        myConnection = new Connection(servaddr);

        //TODO Connect to server
        if (myConnection->createSocket() < 0)
        {
            printf("Could not create socket error.");
            return;
        }
        if (myConnection->connectSocket() < 0)
        {
            printf("Could not connect socket error.");
            delete(myConnection);
            delete(servaddr);
            return;
        }


		//TODO Make a chat message
        cm = new ChatMessage();
        cm->setSender(qnick.toLatin1().data());             // I forgot this!
        cm->setMessage(qmessage.toLatin1().data());

		//TODO Send chat message (as bytes)
        bytesToSend = cm->encode(&buffer);
        myConnection->writeSize(bytesToSend);
        myConnection->writen(buffer,bytesToSend);           // This was commented out? stupid mistake

		delete(buffer);

		//TODO Read response - take action!
        bytesToReceive = myConnection->readSize();
        buffer = new char[bytesToReceive];

		//TODO Read byte count and message
        myConnection->readn(buffer,bytesToReceive);

		//TODO Destroy socket
        myConnection->closeSocket();

		//TODO Convert to message (confirm)
		c = new Confirm();
        c->decode(buffer,bytesToReceive);

		//check if nick removed
        if (c->getResponse()==true)
		{
			ui.lineEdit->setText(tr(""));
		}

        delete myConnection;
        delete servaddr;
	}
}

/* This method is a slot connected to the timers signal */
void ChatClient::getMessages()
{
	printf("timer went off\n");
	if(nickAccepted == true) //only respond if they are connected
	{
		RequestUpdate *ru;
		UpdateMessage *um;
		INet4Address *servaddr;
		Connection *myConnection;
		char* buffer; //for encoded messages
		int bytesToSend;
		int bytesToReceive;
		int i;
		QString msg;

		//TODO Stop the timer
        timer->stop();


		//Get the strings out of the address, port and nickname
		//boxes and convert to strings;
		QString qmessage = ui.lineEdit->text();
		QString qnick = ui.nicknameLine->text();
		QString qip = ui.addresLine->text();
		QString qport = ui.portLine->text();


		//TODO Create new connection objects
        servaddr = new INet4Address(qip.toLatin1().data(),qport.toInt());
        myConnection = new Connection(servaddr);


		//TODO Connect to server
        if (myConnection->createSocket() < 0)
        {
            printf("Could not create socket error.");
            return;
        }

        if (myConnection->connectSocket() < 0)
        {
            printf("Could not connect socket error.");
            delete(myConnection);
            delete(servaddr);
            return;
        }

		//TODO Make a Request update message
		ru = new RequestUpdate(lastMessageNo);

		//TODO Send join message (as bytes)
        bytesToSend = ru->encode(&buffer);
        myConnection->writeSize(bytesToSend);
        myConnection->writen(buffer,bytesToSend);

		delete(buffer);

		//TODO Read response - take action!



		//TODO Read byte count
        bytesToReceive = myConnection->readSize();

		//TODO allocate buffer
        buffer = new char[bytesToReceive];

		//TODO Read message
        myConnection->readn(buffer,bytesToReceive);

		//TODO Destroy socket
        myConnection->closeSocket();

		//TODO Convert to message
		um = new UpdateMessage();
        um->decode(buffer, bytesToReceive);                      // I think this is how it works!



        //um->addMessage(buffer);



		//Append new messages to a single string
		for(i=0;i<um->getMessageCount();i++)
		{
			msg += QString(um->getMessage(i));
			msg += QString("\n");
		}

		//Append messages to the text box and update last message count
		if(um->getMessageCount() > 0)
		{
			lastMessageNo += um->getMessageCount();
			ui.chatWindow->appendPlainText(msg);
		}


		//Process message
        delete myConnection;
        delete servaddr;

		//TODO Restart the timer
        timer->start();
	}
}
