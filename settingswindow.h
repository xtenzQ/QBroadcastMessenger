#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QtWidgets>
#include <QWidget>

class SettingsWindow : public QDialog
{
        Q_OBJECT
public:
    SettingsWindow(QSettings *settings, QWidget *parent);
private:
    QLineEdit *ipLineEdit;
    QCheckBox *broadcastCheckBox;
    QLineEdit *nickLineEdit;
    QLineEdit *portLineEdit;
    QSettings *settings;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QCheckBox *defaultCheckBox;
    QGridLayout *gridLayout;

private slots:
    void okClicked();
    void cancelClicked();
    //void defaultClicked();

};

#endif // SETTINGSWINDOW_H
