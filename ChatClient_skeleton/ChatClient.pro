TEMPLATE = app
TARGET = ChatClient

QT += widgets

QT += core \
    gui
HEADERS += ChatMessage.h \
    Confirm.h \
    Join.h \
    KillClient.h \
    KillServer.h \
    Leave.h \
    Message.h \
    RequestUpdate.h \
    UpdateMessage.h \
    chatclient.h \
    INet4Address.h \
    Connection.h
SOURCES += ChatMessage.cpp \
    Confirm.cpp \
    Join.cpp \
    KillClient.cpp \
    KillServer.cpp \
    Leave.cpp \
    Message.cpp \
    RequestUpdate.cpp \
    UpdateMessage.cpp \
    main.cpp \
    chatclient.cpp \
    INet4Address.cpp \
    Connection.cpp
FORMS += \
    chatclient.ui
RESOURCES += 
