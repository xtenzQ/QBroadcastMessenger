#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include "connectionmanager.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QWidget *basicWidget;
    QVBoxLayout *basicLayout;
    QHBoxLayout *chatLayout;
    QHBoxLayout *messageLayout;
    QMenuBar *menuBar;
    QTextEdit *messageTextEdit;
    QListWidget *chatListTextEdit;
    QTextEdit *messageLineEdit;
    QPushButton *sendButton;
    QPushButton *callButton;
    QWidget *bottomLine;
    QSplitter *chatSplitter;
    QSplitter *messageSplitter;
    ConnectionManager *manager;

    QString *messages;
    QString *myMessage;

    void displayMessage(QString *msg);
};

#endif // MAINWINDOW_H
