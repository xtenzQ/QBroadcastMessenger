#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // honestly I'm not happy to build UI via code
    // but as long as professor asks for it
    // I have no choice :)

    // Specifying the basic widget
    // we have to do it because this is the thing
    // all the widgets are located in
    basicWidget = new QWidget(this);

    // TITLE
    // Set icon from myresources (check resources.qrc)
    // /myresoucres is the prefix
    // /titleicon.png is the alias of icon titleicon.png located in folder icons
    setWindowIcon(QIcon(QStringLiteral(":/myresources/titleicon.png")));
    setWindowTitle("Qt Broadcasting Messenger");

    // Main LAYOUT
    // This UI is build with QVBoxLayout, QHBoxLayout and
    // two splitters
    // Here's the hierarchy:
    /*
     * basicLayout (QVBoxLayout)
     * - menuBar (QMenuBar)
     *      - ... all the mighty buttons gathered here together :o
     * - messageSplitter (QSplitter)
     *      -chatSplitter (QSplitter)
     *          -messageTextEdit (QTextEdit)
     *          -chatListTextEdit (QTextEdit)
     *      -BottomLine (QWidget)
     *          -messageLineEdit (QTextEdit)
     *          -sendButton (QPushButton)
     *          -callButton (QPushButton)
     */

    // VERTICAL LAYOUT
    basicLayout = new QVBoxLayout;
    basicLayout->setMargin(0);

    // MIDDLE CHAT LAYOUT
    chatLayout = new QHBoxLayout;
    chatLayout->setContentsMargins(5, 0, 5, 0);

    // BOTTOM MESSAGE MANAGER LAYOUT
    messageLayout = new QHBoxLayout;
    messageLayout->setContentsMargins(5, 0, 5, 5);

    // MENU BAR
    menuBar = new QMenuBar;
    menuBar->addMenu(tr("&Connection"));
    // I do like CSS so thanks Qt for given opportunity haha
    menuBar->setStyleSheet("background-color: transparent;");

    // TEXTS
    // The biggest text area in application to display messages
    messageTextEdit = new QTextEdit;
    messageTextEdit->setMinimumWidth(400);
    // since it's message history no one should be able to edit it
    messageTextEdit->setReadOnly(true);
    messageTextEdit->setFocusPolicy(Qt::NoFocus);

    // The list of people joined the chat
    // located on the right side
    chatListTextEdit = new QTextEdit;
    chatListTextEdit->setMinimumWidth(200);
    chatListTextEdit->setFocusPolicy(Qt::NoFocus);

    // The box to type messages
    messageLineEdit = new QTextEdit;
    messageLineEdit->setStyleSheet("min-height: 15px;");
    // the first widget to get focus
    messageLineEdit->setFocusPolicy(Qt::StrongFocus);

    // BUTTONS
    // Button to send messages
    sendButton = new QPushButton;
    sendButton->setIcon(QIcon(QStringLiteral(":/myresources/send.png")));
    sendButton->setStyleSheet("border: 0; background-color: transparent; margin: 0 10;");

    // Button to call
    callButton = new QPushButton;
    callButton->setIcon(QIcon(QStringLiteral(":/myresources/call.png")));
    callButton->setStyleSheet("border: 0; background-color: transparent; margin: 0 10;");

    // BOTTOM widgets:
    // 1. MessageBox
    // 2. Send button
    // 3. Call button
    bottomLine = new QWidget();
    messageLayout->addWidget(messageLineEdit);
    messageLayout->addWidget(sendButton);
    messageLayout->addWidget(callButton);
    bottomLine->setLayout(messageLayout);

    // SPLITTER #1 HORIZONTAL
    // consits of
    // 1. MessageTextBox (on the left)
    // 2. chatListTextBox (on the right)
    chatSplitter = new QSplitter;
    chatSplitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    chatSplitter->addWidget(messageTextEdit);
    chatSplitter->addWidget(chatListTextEdit);

    // SPLITTER #2 VERTICAL
    // consits of
    // 1. chatSplitter on top
    // 2. Bottom widget on bottom
    messageSplitter = new QSplitter;
    // setting vertical orientation because default is horizontal
    messageSplitter->setOrientation(Qt::Vertical);
    messageSplitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    messageSplitter->addWidget(chatSplitter);
    messageSplitter->addWidget(bottomLine);
    // inital sizes (I want for message line to be the smallest here)
    messageSplitter->setSizes(QList<int>() << 500 << 100);

    // adding menuBar to basic layout
    basicLayout->addWidget(menuBar);
    basicLayout->addWidget(messageSplitter);

    // Set layout to basic widget
    basicWidget->setLayout(basicLayout);
    // Set central widget to display everything :D
    setCentralWidget(basicWidget);

    // writing comments is like talking with myself
    // but I hope it will help you

    manager = &ConnectionManager::GetInstance();
}

MainWindow::~MainWindow()
{

}
