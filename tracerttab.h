#ifndef TRACERTTAB_H
#define TRACERTTAB_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QString>

class TracertTab : public QWidget
{
    Q_OBJECT
public:
    explicit TracertTab(QWidget *parent = nullptr);
    QString getIp();

signals:

public slots:

private:
    QVBoxLayout *vLayout;
    QHBoxLayout *ipLayout;
    QLabel *ipLabel;
    QLabel *dotLabel1;
    QLabel *dotLabel2;
    QLabel *dotLabel3;
    QLineEdit *ipEdit1;
    QLineEdit *ipEdit2;
    QLineEdit *ipEdit3;
    QLineEdit *ipEdit4;
};

#endif // TRACERTTAB_H
