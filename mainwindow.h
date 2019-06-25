#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include "settingswindow.h"
#include "connectionmanager.h"

class ConnectionManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTextEdit *messageTextEdit;
    QListWidget *clientsListWidget;
    QTextEdit *messageLineEdit;
private:
    QWidget *basicWidget;
    QVBoxLayout *basicLayout;
    QHBoxLayout *chatLayout;
    QHBoxLayout *messageLayout;
    QMenuBar *menuBar;
    ConnectionManager *manager;
    QPushButton *sendButton;
    QPushButton *callButton;
    QWidget *bottomLine;
    QSplitter *chatSplitter;
    QSplitter *messageSplitter;
public slots:
    void refreshUserList(QStringList *users);
    void addMessage(QString msg);
    void addMessage(QString msg, QColor color);
private slots:
    void sendButtonClicked();
    void clearMessageBox();
};

#endif // MAINWINDOW_H
