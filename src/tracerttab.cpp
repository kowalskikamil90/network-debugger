#include "tracerttab.h"
#include <QIntValidator>

TracertTab::TracertTab(QWidget *parent) :
  QWidget(parent),
  _vLayout(new QVBoxLayout(this)),
  _ipLayout(new QHBoxLayout(this)),
  _ipLabel(new QLabel(this)),
  _dotLabel1(new QLabel(this)),
  _dotLabel2(new QLabel(this)),
  _dotLabel3(new QLabel(this)),
  _ipEdit1(new QLineEdit(this)),
  _ipEdit2(new QLineEdit(this)),
  _ipEdit3(new QLineEdit(this)),
  _ipEdit4(new QLineEdit(this))
{
    /* IP address - horizontal layout */

    _ipLabel->setText("IP of the host to ping:");
    _dotLabel1->setText(".");
    _dotLabel2->setText(".");
    _dotLabel3->setText(".");
    _ipEdit1->setFixedWidth(35);
    _ipEdit2->setFixedWidth(35);
    _ipEdit3->setFixedWidth(35);
    _ipEdit4->setFixedWidth(35);

    // Limit number of characters to 3
    _ipEdit1->setMaxLength(3);
    _ipEdit2->setMaxLength(3);
    _ipEdit3->setMaxLength(3);
    _ipEdit4->setMaxLength(3);

    // Accept only numbers proper range of numbers
    _ipEdit1->setValidator(new QIntValidator(0, 255, this));
    _ipEdit2->setValidator(new QIntValidator(0, 255, this));
    _ipEdit3->setValidator(new QIntValidator(0, 255, this));
    _ipEdit4->setValidator(new QIntValidator(0, 255, this));

    // Align text to the left
    _ipEdit1->setAlignment(Qt::AlignRight);
    _ipEdit2->setAlignment(Qt::AlignRight);
    _ipEdit3->setAlignment(Qt::AlignRight);
    _ipEdit4->setAlignment(Qt::AlignRight);

    // Set default Ip to loopback address
    _ipEdit1->setText(QString("127"));
    _ipEdit2->setText(QString("0"));
    _ipEdit3->setText(QString("0"));
    _ipEdit4->setText(QString("1"));

    // Add everything to the horizontal layout
    _ipLayout->addWidget(_ipEdit1);
    _ipLayout->addWidget(_dotLabel1);
    _ipLayout->addWidget(_ipEdit2);
    _ipLayout->addWidget(_dotLabel2);
    _ipLayout->addWidget(_ipEdit3);
    _ipLayout->addWidget(_dotLabel3);
    _ipLayout->addWidget(_ipEdit4);
    _ipLayout->addStretch(1);

    /* Main layout for this tab */

    _vLayout->addWidget(_ipLabel);
    _vLayout->addLayout(_ipLayout);
    _vLayout->addStretch(1);
    setLayout(_vLayout);
}

QString TracertTab::getIp()
{
    // Data validation is done by the widget itself
    QString ipAddress;
    ipAddress.append(_ipEdit1->text());
    ipAddress.append(".");
    ipAddress.append(_ipEdit2->text());
    ipAddress.append(".");
    ipAddress.append(_ipEdit3->text());
    ipAddress.append(".");
    ipAddress.append(_ipEdit4->text());

    return ipAddress;
}
