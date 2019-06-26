# 📨 QBroadcastMessenger
Messenger which uses broadcasting to send messages.
The application is developed as university project at [Irkutsk National Research Techincal University](http://www.istu.edu/eng/).

**Contributors**: 👨‍🎓 @[xtenzQ](https://github.com/xtenzQ), 👨‍🎓 @[Exterminant](https://github.com/Exterminant)

## Contents

1. [IDEs and plugins used](#ides-and-plugins-used)
2. [Installation](#installation)
3. [Message structure](#message-structure)
4. [Settings](#settings)

## IDEs and plugins used
- **Qt Creator Community Edition 4.9.1** - [Download](https://www.qt.io/download)
- **Qt 5.12.4 MinGW**
- **EMIPLIB** - [GitHub](https://github.com/j0r1/EMIPLIB) / [Author](https://github.com/j0r1)

## Installation

To run application you need `EMIPLIB` library (for calls), which can be build with `CMAKE` or you can use prebuild libraries (I will put link later).
Put `libs` in `C:/` folder (or anywhere you want but don't forget to change path) and then add to your `.pro`-file following strokes:
```Cpp
INCLUDEPATH += C:\libs\jrtplib\include
INCLUDEPATH += C:\libs\jthread\include
INCLUDEPATH += C:\libs\emiplib\include\emiplib

LIBS += -L"C:\libs\jrtplib\lib" -ljrtp
LIBS += -L"C:\libs\jthread\lib" -ljthread
LIBS += -L"C:\libs\emiplib\lib" -lemiplib
LIBS += -lws2_32
```

## Message structure

**QBroadcastMessenger** uses the custom message structure described below:
- When you first appear in the net app sends **CONNECT** message (`sayHi()` method in `ConnectionManager` class) of the given form: ```EVMp_CONNECT_%username_length%_%username%```
- To notify other apps of you staying connected in the network app sends **ALIVE** message (`ping()` method in `ConnectionManager` class) of the given form: `EVMp_ALIVE_%username_length%_%username%`
- To send message to all the clients in the network app sends **SENDMESSAGE** message (`sendMessage()` method in `ConnectionManager` class) of the given form: `EVMp_SENDMESSAGE_%message_length%_%message%`

## Settings
Settings file is stored in `%APP_DATA%/QBroadcastMessenger` folder. File has the following structure:
```
[network]
ip=172.27.24.255
port=14000
broadcast=true

[personal]
nickname="Tsukasa"
```

## Architecture
