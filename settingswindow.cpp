#include "settingswindow.h"

SettingsWindow::SettingsWindow(QSettings *settings, QWidget *parent=0): QDialog(parent)
{
    this->settings = settings;

    setModal(true);
    setWindowTitle(tr("Settings"));
    setAttribute(Qt::WA_DeleteOnClose);

    ipLineEdit = new QLineEdit();
    portLineEdit = new QLineEdit();
    broadcastCheckBox = new QCheckBox();
    nickLineEdit = new QLineEdit();
    defaultCheckBox = new QCheckBox();

    // Port validation
    portLineEdit->setValidator(new QIntValidator(1, 65535, this));
    // IP validation
    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QRegExp ipRegex ("^" + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange + "$");
    QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
    ipLineEdit->setValidator(ipValidator);

    okButton = new QPushButton(tr("OK"));
    cancelButton = new QPushButton(tr("Cancel"));

    gridLayout = new QGridLayout();

    gridLayout->addWidget(new QLabel(tr("IP")),0,0);
    gridLayout->addWidget(new QLabel(tr("Port")),1,0);
    gridLayout->addWidget(new QLabel(tr("Nickname")),2,0);
    gridLayout->addWidget(new QLabel(tr("Broadcast enabled")),3,0);
    gridLayout->addWidget(new QLabel(tr("Set default")),4,0);

    gridLayout->addWidget(ipLineEdit,0,1);
    gridLayout->addWidget(portLineEdit,1,1);
    gridLayout->addWidget(nickLineEdit,2,1);
    gridLayout->addWidget(broadcastCheckBox,3,1);
    gridLayout->addWidget(defaultCheckBox,4,1);

    gridLayout->addWidget(okButton,5,0);
    gridLayout->addWidget(cancelButton,5,1);

    setLayout(gridLayout);

    this->adjustSize();

    ipLineEdit->setText(settings->value("network/ip").toString());
    portLineEdit->setText(settings->value("network/port").toString());
    nickLineEdit->setText(settings->value("personal/nickname").toString());

    connect(okButton,SIGNAL(clicked(bool)),this,SLOT(okClicked()));
    connect(cancelButton,SIGNAL(clicked(bool)),this,SLOT(cancelClicked()));
    connect(defaultCheckBox, SIGNAL(clicked(bool)), this, SLOT(defaultClicked(bool)));
    connect(broadcastCheckBox, SIGNAL(clicked(bool)), this, SLOT(broadcastClicked(bool)));
}

void SettingsWindow::okClicked() {
    settings->setValue("network/ip",ipLineEdit->text());
    settings->setValue("network/port", portLineEdit->text());
    settings->setValue("network/broadcast",broadcastCheckBox->isChecked());
    settings->setValue("personal/nickname", nickLineEdit->text());
    settings->sync();
    emit settingsChanged();
    close();
}

void SettingsWindow::cancelClicked() {
    close();
}

void SettingsWindow::defaultClicked(bool checked) {
    if (checked) {
        ipLineEdit->setText("172.27.24.255");
        portLineEdit->setText("14000");
        broadcastCheckBox->setChecked(true);
        nickLineEdit->setText("COMRADE");
    }
    else {
        ipLineEdit->clear();
        portLineEdit->clear();
        broadcastCheckBox->setChecked(false);
        nickLineEdit->clear();
    }
}

void SettingsWindow::broadcastClicked(bool checked) {
    /*if (checked & !(ipLineEdit->text().isEmpty())) {
        QString ip = ipLineEdit->text();
        int pos = 0;
        for(int i = ip.length() - 1; i == 0 ; i--) {
            if (ip[i] == '.') {
                pos = i;
                break;
            }
        }
        //ipLineEdit->setText(QString::number(pos));
        //ip.remove(pos + 1, ip.length() - pos);
        //ipLineEdit->setText(ip);
        //ipLineEdit->setText(ip.replace(pos + 1, 3, "255"));
    }*/
}
