TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -pthread

SOURCES += \
    ChatMessage.cpp \
    Confirm.cpp \
    INet4Address.cpp \
    Join.cpp \
    KillClient.cpp \
    KillServer.cpp \
    Leave.cpp \
    Message.cpp \
    ServerConn.cpp \
    RequestUpdate.cpp \
    UpdateMessage.cpp \
    main.cpp

HEADERS += \
    ChatMessage.h \
    Confirm.h \
    INet4Address.h \
    Join.h \
    KillClient.h \
    KillServer.h \
    Leave.h \
    Message.h \
    ServerConn.h \
    RequestUpdate.h \
    UpdateMessage.h

