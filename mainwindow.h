#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include "connectionmanager.h"

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
    QTextEdit *chatListTextEdit;
    QTextEdit *messageLineEdit;
    QPushButton *sendButton;
    QPushButton *callButton;
    QWidget *bottomLine;
    QSplitter *chatSplitter;
    QSplitter *messageSplitter;
    ConnectionManager *manager;
};

#endif // MAINWINDOW_H
