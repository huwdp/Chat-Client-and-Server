#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QtGui>
#include "ui_chatclient.h"
#include "INet4Address.h"
#include "Connection.h"

class ChatClient : public QWidget
{
    Q_OBJECT

private:
    Ui::ChatClientClass ui;
	bool nickAccepted;
	QTimer *timer;
	int lastMessageNo;

public:
    ChatClient(QWidget *parent = 0);
    ~ChatClient();

public slots:
	void on_joinButton_clicked();
	void on_leaveButton_clicked();
	void on_sendButton_clicked();
	void getMessages();
};

#endif // CHATCLIENT_H
