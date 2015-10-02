/********************************************************************************
** Form generated from reading UI file 'chatclient.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATCLIENT_H
#define UI_CHATCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets>

QT_BEGIN_NAMESPACE

class Ui_ChatClientClass
{
public:
    QVBoxLayout *verticalLayout_4;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout_4;
    QPlainTextEdit *chatWindow;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *addresLine;
    QLabel *label_3;
    QLineEdit *portLine;
    QLabel *nick;
    QLineEdit *nicknameLine;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QVBoxLayout *verticalLayout_3;
    QPushButton *joinButton;
    QPushButton *leaveButton;
    QPushButton *sendButton;

    void setupUi(QWidget *ChatClientClass)
    {
        if (ChatClientClass->objectName().isEmpty())
            ChatClientClass->setObjectName(QString::fromUtf8("ChatClientClass"));
        ChatClientClass->resize(511, 421);
        verticalLayout_4 = new QVBoxLayout(ChatClientClass);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        scrollArea = new QScrollArea(ChatClientClass);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy);
        scrollArea->setLineWidth(1);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 489, 299));
        sizePolicy.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy);
        horizontalLayout_4 = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout_4->setSpacing(-1);
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        chatWindow = new QPlainTextEdit(scrollAreaWidgetContents);
        chatWindow->setObjectName(QString::fromUtf8("chatWindow"));
        chatWindow->setFrameShape(QFrame::StyledPanel);
        chatWindow->setFrameShadow(QFrame::Plain);
        chatWindow->setLineWidth(0);
        chatWindow->setReadOnly(true);

        horizontalLayout_4->addWidget(chatWindow);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_4->addWidget(scrollArea);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(ChatClientClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        addresLine = new QLineEdit(ChatClientClass);
        addresLine->setObjectName(QString::fromUtf8("addresLine"));
        addresLine->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(addresLine->sizePolicy().hasHeightForWidth());
        addresLine->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(addresLine);

        label_3 = new QLabel(ChatClientClass);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        portLine = new QLineEdit(ChatClientClass);
        portLine->setObjectName(QString::fromUtf8("portLine"));
        sizePolicy1.setHeightForWidth(portLine->sizePolicy().hasHeightForWidth());
        portLine->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(portLine);

        nick = new QLabel(ChatClientClass);
        nick->setObjectName(QString::fromUtf8("nick"));

        horizontalLayout_2->addWidget(nick);

        nicknameLine = new QLineEdit(ChatClientClass);
        nicknameLine->setObjectName(QString::fromUtf8("nicknameLine"));

        horizontalLayout_2->addWidget(nicknameLine);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(ChatClientClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setScaledContents(true);

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(ChatClientClass);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);


        verticalLayout_2->addLayout(horizontalLayout);


        horizontalLayout_3->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        joinButton = new QPushButton(ChatClientClass);
        joinButton->setObjectName(QString::fromUtf8("joinButton"));

        verticalLayout_3->addWidget(joinButton);

        leaveButton = new QPushButton(ChatClientClass);
        leaveButton->setObjectName(QString::fromUtf8("leaveButton"));

        verticalLayout_3->addWidget(leaveButton);

        sendButton = new QPushButton(ChatClientClass);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));

        verticalLayout_3->addWidget(sendButton);


        horizontalLayout_3->addLayout(verticalLayout_3);


        verticalLayout_4->addLayout(horizontalLayout_3);


        retranslateUi(ChatClientClass);

        QMetaObject::connectSlotsByName(ChatClientClass);
    } // setupUi

    void retranslateUi(QWidget *ChatClientClass)
    {
        ChatClientClass->setWindowTitle(QApplication::translate("ChatClientClass", "ChatClient", 0));
        label_2->setText(QApplication::translate("ChatClientClass", "Server IP", 0));
        label_3->setText(QApplication::translate("ChatClientClass", "Port", 0));
        nick->setText(QApplication::translate("ChatClientClass", "Nickname", 0));
        label->setText(QApplication::translate("ChatClientClass", "Message:", 0));
        joinButton->setText(QApplication::translate("ChatClientClass", "Join", 0));
        leaveButton->setText(QApplication::translate("ChatClientClass", "Leave", 0));
        sendButton->setText(QApplication::translate("ChatClientClass", "Send", 0));
    } // retranslateUi

};

namespace Ui {
    class ChatClientClass: public Ui_ChatClientClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATCLIENT_H
