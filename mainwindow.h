#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include "settingswindow.h"
#include "connectionmanager.h"

#ifdef Q_OS_WIN32
#define _WIN32_IE 0x0400
#include <shlobj.h>
#undef _WIN32_IE
#endif

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
    QPushButton *callButton;
    QSettings *settings;

    // nickname
    QString nickname = "xtenzQ";
    // port
    quint16 port = 14000;
    // response time to ping
    const int responseTime = 2000;
    QString destinationIP = "127.0.0.1";
private:
    QWidget *basicWidget;
    QVBoxLayout *basicLayout;
    QHBoxLayout *chatLayout;
    QHBoxLayout *messageLayout;
    QTabWidget *tabWidget;
    QMenuBar *menuBar;
    ConnectionManager *manager;
    QPushButton *sendButton;
    bool started;
    QWidget *bottomLine;
    QSplitter *chatSplitter;
    QSplitter *messageSplitter;
public slots:
    void refreshUserList(QStringList *users);
    void addMessage(QString msg);
    void addMessage(QString msg, QColor color);
private slots:
    void sendButtonClicked();
    void openSettingsWindow();
    void clearMessageBox();
    void openSettings();
    void loadSettings();
    void call();
};

#endif // MAINWINDOW_H
